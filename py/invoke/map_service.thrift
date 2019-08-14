namespace cpp map_service

enum RetCode {
  fail = -1;
  success = 0;
  degrade = 1;
}

struct Point {
  1: required double lat;
  2: required double lng;
}

struct Step {
  1: required i64 source;
  2: required i64 target;
  3: required double distance;
  4: required double duration;
}

struct PointToPointRequest {
  1: required Point source;
  2: required Point target;
  3: optional bool step = false;
}

struct PointToPointResponse {
  1: required RetCode code = RetCode.fail;
  2: required double distance = -1;
  3: required double duration = -1;
  4: optional list<Step> steps;
  5: optional list<Point> projections;
}

service MapService {
  i32 ping();
  PointToPointResponse pointToPointRoute(1: PointToPointRequest request);
  list<PointToPointResponse> batchPointToPointRoute(1: list<PointToPointRequest> requests);
}

