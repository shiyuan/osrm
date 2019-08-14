from utils.timeit import timeit
from invoke.invoke import Invoker
from thrift_json import thrift2json

invoker = Invoker('localhost', 5000)

@timeit
def dummy_test():
    src_lng, src_lat = 121.3244462013,31.2370225222
    dst_lng, dst_lat = 121.3820385933,31.2329448269
    res = invoker.p2p_route(src_lat, src_lng, dst_lat, dst_lng, True)
    return thrift2json(res)

@timeit
def batch_test(S = 1000):
    reqs = [[31.2370225222,121.3244462013, 31.2329448269,121.3820385933, True] for _ in range(S)]
    return invoker.batch_p2p_route(reqs)[0]

print(dummy_test())
# method: <function dummy_test at 0x7f42bbd482a8>, args: (), cost: 4.04ms
# {"duration": 422.0, "distance": 6538.7, "code": 0, "steps": [{"duration": 14.8, "target_node": 3478890947, "source_node": 842030636, "distance": 176.0}, {"duration": 1.9, "target_node": 2753439296, "source_node": 3478890947, "distance": 23.0}, {"duration": 1.1, "target_node": 1368557085, "source_node": 2753439296, "distance": 261.0}, {"duration": 4.0, "target_node": 842030670, "source_node": 1368557085, "distance": 45.0}, {"duration": 1.0, "target_node": 266416675, "source_node": 842030670, "distance": 404.0}, {"duration": 1.4, "target_node": 565439951, "source_node": 266416675, "distance": 307.0}, {"duration": 9.9, "target_node": 1078618003, "source_node": 565439951, "distance": 397.0}, {"duration": 16.1, "target_node": 1080167963, "source_node": 1078618003, "distance": 283.0}, {"duration": 14.6, "target_node": 567769708, "source_node": 1080167963, "distance": 501.0}, {"duration": 17.8, "target_node": 567769712, "source_node": 567769708, "distance": 311.0}, {"duration": 7.0, "target_node": 1530714517, "source_node": 567769712, "distance": 288.0}, {"duration": 6.9, "target_node": 3003943636, "source_node": 1530714517, "distance": 406.0}, {"duration": 16.6, "target_node": 3001826838, "source_node": 3003943636, "distance": 291.0}, {"duration": 0.3, "target_node": 726719686, "source_node": 3001826838, "distance": 290.0}, {"duration": 7.9, "target_node": 3001826727, "source_node": 726719686, "distance": 209.0}, {"duration": 7.8, "target_node": 726720536, "source_node": 3001826727, "distance": 274.0}, {"duration": 2.8, "target_node": 1078518678, "source_node": 726720536, "distance": 14.0}, {"duration": 12.4, "target_node": 726719657, "source_node": 1078518678, "distance": 182.0}, {"duration": 17.0, "target_node": 726719652, "source_node": 726719657, "distance": 263.0}, {"duration": 18.6, "target_node": 726719647, "source_node": 726719652, "distance": 290.0}, {"duration": 11.2, "target_node": 726719631, "source_node": 726719647, "distance": 309.0}, {"duration": 4.8, "target_node": 827172050, "source_node": 726719631, "distance": 287.0}, {"duration": 5.2, "target_node": 726720963, "source_node": 827172050, "distance": 56.0}, {"duration": 29.5, "target_node": 726719606, "source_node": 726720963, "distance": 398.0}, {"duration": 8.3, "target_node": 726719895, "source_node": 726719606, "distance": 6.0}, {"duration": 4.5, "target_node": 726720964, "source_node": 726719895, "distance": 265.0}], "projections": [{"lat": 31.236748, "lng": 121.325414}, {"lat": 31.232284, "lng": 121.381922}]}

# print(batch_test())
