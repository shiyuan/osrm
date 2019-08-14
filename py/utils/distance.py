from math import radians, cos, sqrt

EARTH_RADIUS = 6367000.

def gcd_distance(src_lat, src_lng, dst_lat, dst_lng):
    delta_lng = dst_lng - src_lng
    delta_lat = dst_lat - src_lat
    avg_lat = (src_lat + dst_lat) / 2
    x = radians(delta_lng) * cos(radians(avg_lat))
    y = radians(delta_lat)
    return sqrt(x ** 2 + y ** 2) * EARTH_RADIUS

