# OSRM
A routing demo running on docker, based on [osrm](https://github.com/Project-OSRM/osrm-backend)

## change
1. Initialize with [osrm-backend v5.4.3](https://github.com/Project-OSRM/osrm-backend/tree/v5.4.3)
2. Run with docker
3. Fix `you are trying to register a class twice` according to [issues](https://github.com/Project-OSRM/osrm-backend/issues/2811) and [pr](https://github.com/Project-OSRM/osrm-backend/pull/3346/files)
4. Convert coordinate from wgs84 to gcj02
5. Add thrift service and handler
6. Use folium to render map result
