from utils.timeit import timeit
from invoke.invoke import Invoker
from thrift_json import thrift2json

invoker = Invoker('127.0.0.1', 5000)

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
# {"duration": 422.0, "distance": 6538.7, "code": 0, "steps": [{"duration": 14.8, "target_node": 3478890947, "source_node": 842030636, "distance": 176.20317983416402}, {"duration": 1.9, "target_node": 2753439296, "source_node": 3478890947, "distance": 23.072842110978527}, {"duration": 1.1, "target_node": 1368557085, "source_node": 2753439296, "distance": 261.30477876146364}, {"duration": 4.0, "target_node": 842030670, "source_node": 1368557085, "distance": 45.247922674582654}, {"duration": 1.0, "target_node": 266416675, "source_node": 842030670, "distance": 404.23072928129005}, {"duration": 1.4, "target_node": 565439951, "source_node": 266416675, "distance": 307.4403276620476}, {"duration": 9.9, "target_node": 1078618003, "source_node": 565439951, "distance": 396.6875248835418}, {"duration": 16.1, "target_node": 1080167963, "source_node": 1078618003, "distance": 282.54330760834887}, {"duration": 14.6, "target_node": 567769708, "source_node": 1080167963, "distance": 501.3835755220487}, {"duration": 17.8, "target_node": 567769712, "source_node": 567769708, "distance": 311.4774900196308}, {"duration": 7.0, "target_node": 1530714517, "source_node": 567769712, "distance": 288.09608355455487}, {"duration": 6.9, "target_node": 3003943636, "source_node": 1530714517, "distance": 406.35046923726094}, {"duration": 16.6, "target_node": 3001826838, "source_node": 3003943636, "distance": 290.682023688179}, {"duration": 0.3, "target_node": 726719686, "source_node": 3001826838, "distance": 289.70394976125675}, {"duration": 7.9, "target_node": 3001826727, "source_node": 726719686, "distance": 209.20839866634148}, {"duration": 7.8, "target_node": 726720536, "source_node": 3001826727, "distance": 273.8290078891374}, {"duration": 2.8, "target_node": 1078518678, "source_node": 726720536, "distance": 14.322784122451939}, {"duration": 12.4, "target_node": 726719657, "source_node": 1078518678, "distance": 181.81546548473926}, {"duration": 17.0, "target_node": 726719652, "source_node": 726719657, "distance": 262.6716154577343}, {"duration": 18.6, "target_node": 726719647, "source_node": 726719652, "distance": 290.34899719655857}, {"duration": 11.2, "target_node": 726719631, "source_node": 726719647, "distance": 309.2371780453609}, {"duration": 4.8, "target_node": 827172050, "source_node": 726719631, "distance": 287.185881880207}, {"duration": 5.2, "target_node": 726720963, "source_node": 827172050, "distance": 56.1646139705011}, {"duration": 29.5, "target_node": 726719606, "source_node": 726720963, "distance": 398.34006016381466}, {"duration": 8.3, "target_node": 726719895, "source_node": 726719606, "distance": 6.152037417482428}, {"duration": 4.5, "target_node": 726720964, "source_node": 726719895, "distance": 265.0219901837071}], "projections": [{"lat": 31.236748, "lng": 121.325414}, {"lat": 31.232284, "lng": 121.381922}]}

# print(batch_test())
