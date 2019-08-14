/**
 * Autogenerated by Thrift Compiler (0.10.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef map_service_TYPES_H
#define map_service_TYPES_H

#include <iosfwd>

#include <thrift/Thrift.h>
#include <thrift/TApplicationException.h>
#include <thrift/TBase.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/transport/TTransport.h>

#include <thrift/cxxfunctional.h>


namespace map_service {

struct RetCode {
  enum type {
    fail = -1,
    success = 0,
    degrade = 1
  };
};

extern const std::map<int, const char*> _RetCode_VALUES_TO_NAMES;

class Point;

class Step;

class PointToPointRequest;

class PointToPointResponse;


class Point : public virtual ::apache::thrift::TBase {
 public:

  Point(const Point&);
  Point& operator=(const Point&);
  Point() : lat(0), lng(0) {
  }

  virtual ~Point() throw();
  double lat;
  double lng;

  void __set_lat(const double val);

  void __set_lng(const double val);

  bool operator == (const Point & rhs) const
  {
    if (!(lat == rhs.lat))
      return false;
    if (!(lng == rhs.lng))
      return false;
    return true;
  }
  bool operator != (const Point &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Point & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(Point &a, Point &b);

inline std::ostream& operator<<(std::ostream& out, const Point& obj)
{
  obj.printTo(out);
  return out;
}


class Step : public virtual ::apache::thrift::TBase {
 public:

  Step(const Step&);
  Step& operator=(const Step&);
  Step() : source(0), target(0), distance(0), duration(0) {
  }

  virtual ~Step() throw();
  int64_t source;
  int64_t target;
  double distance;
  double duration;

  void __set_source(const int64_t val);

  void __set_target(const int64_t val);

  void __set_distance(const double val);

  void __set_duration(const double val);

  bool operator == (const Step & rhs) const
  {
    if (!(source == rhs.source))
      return false;
    if (!(target == rhs.target))
      return false;
    if (!(distance == rhs.distance))
      return false;
    if (!(duration == rhs.duration))
      return false;
    return true;
  }
  bool operator != (const Step &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Step & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(Step &a, Step &b);

inline std::ostream& operator<<(std::ostream& out, const Step& obj)
{
  obj.printTo(out);
  return out;
}

typedef struct _PointToPointRequest__isset {
  _PointToPointRequest__isset() : step(true) {}
  bool step :1;
} _PointToPointRequest__isset;

class PointToPointRequest : public virtual ::apache::thrift::TBase {
 public:

  PointToPointRequest(const PointToPointRequest&);
  PointToPointRequest& operator=(const PointToPointRequest&);
  PointToPointRequest() : step(false) {
  }

  virtual ~PointToPointRequest() throw();
  Point source;
  Point target;
  bool step;

  _PointToPointRequest__isset __isset;

  void __set_source(const Point& val);

  void __set_target(const Point& val);

  void __set_step(const bool val);

  bool operator == (const PointToPointRequest & rhs) const
  {
    if (!(source == rhs.source))
      return false;
    if (!(target == rhs.target))
      return false;
    if (__isset.step != rhs.__isset.step)
      return false;
    else if (__isset.step && !(step == rhs.step))
      return false;
    return true;
  }
  bool operator != (const PointToPointRequest &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const PointToPointRequest & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(PointToPointRequest &a, PointToPointRequest &b);

inline std::ostream& operator<<(std::ostream& out, const PointToPointRequest& obj)
{
  obj.printTo(out);
  return out;
}

typedef struct _PointToPointResponse__isset {
  _PointToPointResponse__isset() : steps(false), projections(false) {}
  bool steps :1;
  bool projections :1;
} _PointToPointResponse__isset;

class PointToPointResponse : public virtual ::apache::thrift::TBase {
 public:

  PointToPointResponse(const PointToPointResponse&);
  PointToPointResponse& operator=(const PointToPointResponse&);
  PointToPointResponse() : code((RetCode::type)-1), distance(-1), duration(-1) {
    code = (RetCode::type)-1;

  }

  virtual ~PointToPointResponse() throw();
  RetCode::type code;
  double distance;
  double duration;
  std::vector<Step>  steps;
  std::vector<Point>  projections;

  _PointToPointResponse__isset __isset;

  void __set_code(const RetCode::type val);

  void __set_distance(const double val);

  void __set_duration(const double val);

  void __set_steps(const std::vector<Step> & val);

  void __set_projections(const std::vector<Point> & val);

  bool operator == (const PointToPointResponse & rhs) const
  {
    if (!(code == rhs.code))
      return false;
    if (!(distance == rhs.distance))
      return false;
    if (!(duration == rhs.duration))
      return false;
    if (__isset.steps != rhs.__isset.steps)
      return false;
    else if (__isset.steps && !(steps == rhs.steps))
      return false;
    if (__isset.projections != rhs.__isset.projections)
      return false;
    else if (__isset.projections && !(projections == rhs.projections))
      return false;
    return true;
  }
  bool operator != (const PointToPointResponse &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const PointToPointResponse & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(PointToPointResponse &a, PointToPointResponse &b);

inline std::ostream& operator<<(std::ostream& out, const PointToPointResponse& obj)
{
  obj.printTo(out);
  return out;
}

} // namespace

#endif
