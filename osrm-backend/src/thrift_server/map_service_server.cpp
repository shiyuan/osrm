#include "thrift_server/map_service_server.h"

#define THREAD_STACK_SIZE 64   // MB

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

namespace osrm
{
namespace thrift_server
{
void MapServiceServer::StartServer(const int32_t &port,
                                   std::shared_ptr<ServiceHandler> route_handler)
{
    const auto thread_num = std::thread::hardware_concurrency() + 1;
    boost::shared_ptr<MapServiceHandler> handler(new MapServiceHandler());
    handler->setRouteHandler(route_handler);
    boost::shared_ptr<TProcessor> processor(new map_service::MapServiceProcessor(handler));
    boost::shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
    boost::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
    boost::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());
    boost::shared_ptr<ThreadManager> thread_manager = ThreadManager::newSimpleThreadManager(thread_num);
    boost::shared_ptr<PosixThreadFactory> thread_factory = boost::shared_ptr<PosixThreadFactory>(
            new PosixThreadFactory(apache::thrift::concurrency::PosixThreadFactory::ROUND_ROBIN,
                                   apache::thrift::concurrency::PosixThreadFactory::NORMAL,
                                   THREAD_STACK_SIZE));
    thread_manager->threadFactory(thread_factory);
    thread_manager->start();
    manager_ = thread_manager;
    server_ = new TThreadPoolServer(processor, serverTransport, transportFactory, protocolFactory, thread_manager);

    try {
        server_->serve();
    } catch (TException &tx) {
        thread_manager->stop();
        exit(1);
    }
    return;
}

void MapServiceServer::StopServer()
{
    server_->stop();
    if (NULL != server_) {
        delete server_;
        server_ = NULL;
    }
    manager_->stop();
    std::cout << "thrift server stopped" << std::endl;
    return;
}

}
}

