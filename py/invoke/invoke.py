import sys, os

gen_py_path = os.path.dirname(__file__) + '/gen-py'
sys.path.append(gen_py_path)

from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol
from contextlib import contextmanager

from map_service import MapService
from map_service.ttypes import *

class Invoker(object):
    def __init__(self, ip='localhost', port=5000):
        self.ip = ip
        self.port = port

    @contextmanager
    def thrift_client(self):
        socket = TSocket.TSocket(self.ip, self.port)
        transport = TTransport.TBufferedTransport(socket)
        protocol = TBinaryProtocol.TBinaryProtocolAccelerated(transport)
        client = MapService.Client(protocol)
        transport.open()
        yield client
        transport.close()

    def p2p_route(self, src_lat, src_lng, dst_lat, dst_lng, step):
        src = Point(src_lat, src_lng)
        dst = Point(dst_lat, dst_lng)
        req = PointToPointRequest(src, dst, step)
        res = None
        with self.thrift_client() as client:
            res = client.pointToPointRoute(req)
        return res

    def p2p(self, src, dst, step=False):
        return self.p2p_route(src.lat, src.lng, dst.lat, dst.lng, step)
    
    def batch_p2p_route(self, reqs):
        p2p_reqs = []
        for src_lat, src_lng, dst_lat, dst_lng, step in reqs:
           src = Point(src_lat, src_lng)
           dst = Point(dst_lat, dst_lng)
           req = PointToPointRequest(src, dst, step)
           p2p_reqs.append(req)
        res = []
        with self.thrift_client() as client:
            res = client.batchPointToPointRoute(p2p_reqs)
        return res 
