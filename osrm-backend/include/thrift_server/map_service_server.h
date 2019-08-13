#ifndef OSRM_MAP_SERVICE_SERVER_H
#define OSRM_MAP_SERVICE_SERVER_H

#include "MapService.h"
#include "map_service_handler.h"

#include <thrift/transport/TServerSocket.h>
#include <thrift/server/TThreadPoolServer.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/concurrency/ThreadManager.h>
#include <thrift/concurrency/PosixThreadFactory.h>
#include <thrift/transport/TBufferTransports.h>

#include <boost/shared_ptr.hpp>
#include <thread>

using apache::thrift::concurrency::ThreadManager;
using apache::thrift::concurrency::PosixThreadFactory;
using apache::thrift::server::TThreadPoolServer;

namespace osrm
{
namespace thrift_server
{
using osrm::server::ServiceHandler;
class MapServiceServer {
public:
    MapServiceServer() {}
    ~MapServiceServer() {}

    int32_t ping();
    void StartServer(const int32_t &port,
                     std::shared_ptr<ServiceHandler> route_handler);
    void StopServer();

protected:
    TThreadPoolServer *server_;
    boost::shared_ptr<ThreadManager> manager_;
};
}
}


#endif //OSRM_MAP_SERVICE_SERVER_H

