from math import sin, sqrt, pi, cos
r = 6378245.0
ee = 0.00669342162296594323
to_rad = lambda x: x / 180 * pi
def transform_lat(lat, lng):
    res = -100.0 + 2.0 * lng + 3.0 * lat + 0.2 * lat * lat + 0.1 * lng * lat + 0.2 * sqrt(abs(lng))
    res += (20.0 * sin(6.0 * lng * pi) + 20.0 * sin(2.0 * lng * pi)) * 2.0 / 3.0
    res += (20.0 * sin(lat * pi) + 40.0 * sin(lat / 3.0 * pi)) * 2.0 / 3.0
    res += (160.0 * sin(lat / 12.0 * pi) + 320 * sin(lat * pi / 30.0)) * 2.0 / 3.0
    return res

def transform_lng(lat, lng):
    res = 300.0 + lng + 2.0 * lat + 0.1 * lng * lng + 0.1 * lng * lat + 0.1 * sqrt(abs(lng))
    res += (20.0 * sin(6.0 * lng * pi) + 20.0 * sin(2.0 * lng * pi)) * 2.0 / 3.0
    res += (20.0 * sin(lng * pi) + 40.0 * sin(lng / 3.0 * pi)) * 2.0 / 3.0
    res += (150.0 * sin(lng / 12.0 * pi) + 300.0 * sin(lng / 30.0 * pi)) * 2.0 / 3.0
    return res

def convert_wgs84_to_gcj02(lat, lng):
    t_lat = transform_lat(lat - 35.0, lng - 105.0)
    t_lng = transform_lng(lat - 35.0, lng - 105.0)
    rad_lat = to_rad(lat)
    magic = sin(rad_lat)
    magic = 1 - ee * magic * magic
    sqrt_magic = sqrt(magic)
    t_lat = t_lat * 180.0 / ((r * (1 - ee)) / (magic * sqrt_magic) * pi)
    t_lng = t_lng * 180.0 / (r / sqrt_magic * cos(rad_lat) * pi)
    return lat + t_lat, lng + t_lng

