#include <server/api/parameters_parser.hpp>
#include <engine/api/route_parameters.hpp>
#include <util/json_container.hpp>
#include <util/timing_util.hpp>
#include <util/simple_logger.hpp>
#include <util/coordinate_calculation.hpp>
#include "thrift_server/map_service_handler.h"

using map_service::PointToPointRequest;
using map_service::PointToPointResponse;
using map_service::ret_code;

namespace osrm
{
namespace thrift_server
{
int32_t MapServiceHandler::ping()
{
    util::SimpleLogger().Write() << "ha ?";
    return 0;
}

osrm::util::Coordinate toCoordinate(const map_service::Point &point) {
    return {osrm::util::FloatLongitude{point.lng},
            osrm::util::FloatLatitude{point.lat}};
}

void constructCoordinates(std::vector<osrm::util::Coordinate> &coordinates,
                          const PointToPointRequest &request) {
    coordinates.reserve(2);
    coordinates.emplace_back(toCoordinate(request.source));
    coordinates.emplace_back(toCoordinate(request.target));
}

void constructP2PRouteParams(RouteParameters &params,
                             const PointToPointRequest &request)
{
    constructCoordinates(params.coordinates, request);
    params.steps = request.step_flag;
    params.alternatives = false;
    params.annotations = params.steps;
}

void parseP2PRouteJsonResult(PointToPointResponse &_return,
                             const PointToPointRequest &request,
                             const osrm::json::Object &result)
{
    const auto routes = result.values.at("routes").get<osrm::util::json::Array>().values;
    const auto first_route = routes.front().get<osrm::json::Object>();

    const auto distance = first_route.values.at("distance").get<osrm::json::Number>().value;
    const auto duration = first_route.values.at("duration").get<osrm::json::Number>().value;
    std::vector<map_service::Step> steps;
    std::vector<map_service::Point> projections;
    if (request.step_flag) {
        auto way_points = result.values.at("waypoints").get<osrm::json::Array>().values;
        for (auto iter = way_points.begin(); iter != way_points.end(); ++iter) {
            const auto &json_point = (*iter).get<osrm::json::Object>();
            const auto &location = json_point.values.at("location").get<osrm::json::Array>().values;
            map_service::Point p;
            p.__set_lng(location.front().get<osrm::json::Number>().value);
            p.__set_lat(location.back().get<osrm::json::Number>().value);
            projections.push_back(p);
        }

        const auto json_details = first_route.values.at("legs").get<osrm::json::Array>().values.front()
                .get<osrm::util::json::Object>().values.at("annotation").get<osrm::json::Object>().values.at(
                        "segment_details")
                .get<osrm::util::json::Array>().values;
        steps.reserve(json_details.size());
        for (auto iter = json_details.begin(); iter != json_details.end(); ++iter) {
            const auto &json_detail = (*iter).get<util::json::Object>();
            // OSMNodeID convert may cause overflow, because thrift doesn't support uint64_t
            auto source_node = static_cast<std::int64_t>(json_detail.values.at(
                    "source").get<osrm::json::Number>().value);
            auto target_node = static_cast<std::int64_t>(json_detail.values.at(
                    "target").get<osrm::json::Number>().value);
            auto &seg_distance = json_detail.values.at("distance").get<osrm::json::Number>().value;
            auto &seg_duration = json_detail.values.at("duration").get<osrm::json::Number>().value;
            auto &seg_mode = json_detail.values.at("mode").get<osrm::json::String>().value;

            auto step = map_service::Step();
            step.__set_source_node(source_node);
            step.__set_target_node(target_node);
            step.__set_distance(seg_distance);
            step.__set_duration(seg_duration);
            step.__set_mode(seg_mode);
            steps.push_back(step);
        }
        _return.__set_steps(steps);
        _return.__set_projections(projections);
    }
    _return.__set_code(ret_code::success);
    _return.__set_distance(distance);
    _return.__set_duration(duration);
}

void buildPointToPointDegradeResult(PointToPointResponse &_return, const PointToPointRequest &request) {
    _return.__set_code(ret_code::degrade);

    auto source = toCoordinate(request.source);
    auto target = toCoordinate(request.target);
    auto distance = util::coordinate_calculation::haversineDistance(source, target);
    auto duration = distance / (15 / 3.6);
    _return.__set_distance(distance);
    _return.__set_duration(duration);
}

void MapServiceHandler::pointToPointRoute(PointToPointResponse &_return, const PointToPointRequest &request)
{
    RouteParameters params;
    constructP2PRouteParams(params, request);

    osrm::json::Object result;
//    TIMER_START(QUERY);
    osrm::engine::Status status = route_handler_->getRouteMachine().Route(params, result);
//    TIMER_STOP(QUERY);
//    util::SimpleLogger().Write() << "Query cost " << TIMER_SEC(QUERY) << "s";

    if (osrm::engine::Status::Ok == status)
    {
        try
        {
            parseP2PRouteJsonResult(_return, request, result);
        }
        catch (std::exception &e)
        {
            util::SimpleLogger().Write(logWARNING) << "Fail to parse route response, " << e.what();
            buildPointToPointDegradeResult(_return, request);
        }
    }
    else
    {
        _return.__set_code(ret_code::fail);
    }
}

ctpl::thread_pool worker_pool(std::thread::hardware_concurrency() + 1);

PointToPointResponse doP2PRoute(int id, const PointToPointRequest &request,
                                MapServiceHandler* handler)
{
    map_service::PointToPointResponse response;
    handler->pointToPointRoute(response, request);
    return response;
}

void MapServiceHandler::batchPointToPointRoute(std::vector<PointToPointResponse> & _return,
                                               const std::vector<PointToPointRequest> & requests)
{
    std::vector<std::future<PointToPointResponse>> futures;
    futures.reserve(requests.size());
    for (size_t i = 0; i < requests.size(); ++i) {
        futures.emplace_back(worker_pool.push(doP2PRoute, requests[i], this));
    }
    _return.reserve(futures.size());
    for (size_t i = 0; i < futures.size(); ++i) {
        _return.emplace_back(futures[i].get());
    }
}

}
}

