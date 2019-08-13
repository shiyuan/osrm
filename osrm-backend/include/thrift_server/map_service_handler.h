#ifndef OSRM_MAP_SERVICE_HANDLER_H
#define OSRM_MAP_SERVICE_HANDLER_H

#include "MapService.h"
#include "server/service_handler.hpp"
#include "osrm/osrm.hpp"
#include "CTPL/ctpl.h"
#include <future>
#include <cstdio>
#include <iostream>

namespace osrm
{
namespace thrift_server
{

class MapServiceHandler : virtual public map_service::MapServiceIf {
public:
    MapServiceHandler() {}
    virtual ~MapServiceHandler() {}

    void setRouteHandler(std::shared_ptr<osrm::server::ServiceHandler> &route_handler) {
        route_handler_ = route_handler;
    }

    int32_t ping();

    void pointToPointRoute(map_service::PointToPointResponse& _return,
                           const map_service::PointToPointRequest& request);
    void batchPointToPointRoute(std::vector<map_service::PointToPointResponse> & _return,
                                const std::vector<map_service::PointToPointRequest> & requests);



private:
    std::shared_ptr<osrm::server::ServiceHandler> route_handler_;
};
}
}

#endif //OSRM_MAP_SERVICE_HANDLER_H

