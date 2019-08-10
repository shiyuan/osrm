#ifndef COORDINATE_CONVERTER
#define COORDINATE_CONVERTER

#include "util/coordinate.hpp"

#include <cmath>

namespace osrm
{
namespace util
{
namespace coordinate_converter
{
const double r = 6378245.0; // 长半轴
const double ee = 0.00669342162296594323; // 扁率
const double pi = M_PI;

inline double to_rad(double x)
{
     return x / 180.0 * pi; 
}

inline double transform_lat(double lat, double lng)
{
    double res = -100.0 + 2.0 * lng + 3.0 * lat + 0.2 * lat * lat + 0.1 * lng * lat + 0.2 * std::sqrt(std::abs(lng));
    res += (20.0 * sin(6.0 * lng * pi) + 20.0 * sin(2.0 * lng * pi)) * 2.0 / 3.0;
    res += (20.0 * sin(lat * pi) + 40.0 * sin(lat / 3.0 * pi)) * 2.0 / 3.0;
    res += (160.0 * sin(lat / 12.0 * pi) + 320 * sin(lat * pi / 30.0)) * 2.0 / 3.0;
    return res;
}

inline double transform_lng(double lat, double lng)
{
    double res = 300.0 + lng + 2.0 * lat + 0.1 * lng * lng + 0.1 * lng * lat + 0.1 * std::sqrt(std::abs(lng));
    res += (20.0 * sin(6.0 * lng * pi) + 20.0 * sin(2.0 * lng * pi)) * 2.0 / 3.0;
    res += (20.0 * sin(lng * pi) + 40.0 * sin(lng / 3.0 * pi)) * 2.0 / 3.0;
    res += (150.0 * sin(lng / 12.0 * pi) + 300.0 * sin(lng / 30.0 * pi)) * 2.0 / 3.0;
    return res;
}

inline void convert_wgs84_to_gcj02(const FloatCoordinate &coordinate, FloatCoordinate &res_coordinate)
{
    const auto lat = static_cast<double>(coordinate.lat);
    const auto lng = static_cast<double>(coordinate.lon);
    double t_lat = transform_lat(lat - 35.0, lng - 105.0);
    double t_lng = transform_lng(lat - 35.0, lng - 105.0);
    double rad_lat = to_rad(lat);
    double magic = sin(rad_lat);
    magic = 1 - ee * magic * magic;
    double sqrt_magic = sqrt(magic);
    t_lat = t_lat * 180.0 / ((r * (1 - ee)) / (magic * sqrt_magic) * pi);
    t_lng = t_lng * 180.0 / (r / sqrt_magic * cos(rad_lat) * pi);
    res_coordinate = FloatCoordinate{util::FloatLongitude{lng + t_lng}, util::FloatLatitude{lat + t_lat}};
}

} // ns coordinate_converter
} // ns util
} // ns osrm


#endif // COORDINATE_CONVERTER

