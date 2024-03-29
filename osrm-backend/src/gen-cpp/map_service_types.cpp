/**
 * Autogenerated by Thrift Compiler (0.10.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#include "map_service_types.h"

#include <algorithm>
#include <ostream>

#include <thrift/TToString.h>

namespace map_service {

int _kRetCodeValues[] = {
  RetCode::fail,
  RetCode::success,
  RetCode::degrade
};
const char* _kRetCodeNames[] = {
  "fail",
  "success",
  "degrade"
};
const std::map<int, const char*> _RetCode_VALUES_TO_NAMES(::apache::thrift::TEnumIterator(3, _kRetCodeValues, _kRetCodeNames), ::apache::thrift::TEnumIterator(-1, NULL, NULL));


Point::~Point() throw() {
}


void Point::__set_lat(const double val) {
  this->lat = val;
}

void Point::__set_lng(const double val) {
  this->lng = val;
}

uint32_t Point::read(::apache::thrift::protocol::TProtocol* iprot) {

  apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;

  bool isset_lat = false;
  bool isset_lng = false;

  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_DOUBLE) {
          xfer += iprot->readDouble(this->lat);
          isset_lat = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_DOUBLE) {
          xfer += iprot->readDouble(this->lng);
          isset_lng = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  if (!isset_lat)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  if (!isset_lng)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  return xfer;
}

uint32_t Point::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("Point");

  xfer += oprot->writeFieldBegin("lat", ::apache::thrift::protocol::T_DOUBLE, 1);
  xfer += oprot->writeDouble(this->lat);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("lng", ::apache::thrift::protocol::T_DOUBLE, 2);
  xfer += oprot->writeDouble(this->lng);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(Point &a, Point &b) {
  using ::std::swap;
  swap(a.lat, b.lat);
  swap(a.lng, b.lng);
}

Point::Point(const Point& other0) {
  lat = other0.lat;
  lng = other0.lng;
}
Point& Point::operator=(const Point& other1) {
  lat = other1.lat;
  lng = other1.lng;
  return *this;
}
void Point::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "Point(";
  out << "lat=" << to_string(lat);
  out << ", " << "lng=" << to_string(lng);
  out << ")";
}


Step::~Step() throw() {
}


void Step::__set_source(const int64_t val) {
  this->source = val;
}

void Step::__set_target(const int64_t val) {
  this->target = val;
}

void Step::__set_distance(const double val) {
  this->distance = val;
}

void Step::__set_duration(const double val) {
  this->duration = val;
}

uint32_t Step::read(::apache::thrift::protocol::TProtocol* iprot) {

  apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;

  bool isset_source = false;
  bool isset_target = false;
  bool isset_distance = false;
  bool isset_duration = false;

  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_I64) {
          xfer += iprot->readI64(this->source);
          isset_source = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_I64) {
          xfer += iprot->readI64(this->target);
          isset_target = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_DOUBLE) {
          xfer += iprot->readDouble(this->distance);
          isset_distance = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 4:
        if (ftype == ::apache::thrift::protocol::T_DOUBLE) {
          xfer += iprot->readDouble(this->duration);
          isset_duration = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  if (!isset_source)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  if (!isset_target)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  if (!isset_distance)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  if (!isset_duration)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  return xfer;
}

uint32_t Step::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("Step");

  xfer += oprot->writeFieldBegin("source", ::apache::thrift::protocol::T_I64, 1);
  xfer += oprot->writeI64(this->source);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("target", ::apache::thrift::protocol::T_I64, 2);
  xfer += oprot->writeI64(this->target);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("distance", ::apache::thrift::protocol::T_DOUBLE, 3);
  xfer += oprot->writeDouble(this->distance);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("duration", ::apache::thrift::protocol::T_DOUBLE, 4);
  xfer += oprot->writeDouble(this->duration);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(Step &a, Step &b) {
  using ::std::swap;
  swap(a.source, b.source);
  swap(a.target, b.target);
  swap(a.distance, b.distance);
  swap(a.duration, b.duration);
}

Step::Step(const Step& other2) {
  source = other2.source;
  target = other2.target;
  distance = other2.distance;
  duration = other2.duration;
}
Step& Step::operator=(const Step& other3) {
  source = other3.source;
  target = other3.target;
  distance = other3.distance;
  duration = other3.duration;
  return *this;
}
void Step::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "Step(";
  out << "source=" << to_string(source);
  out << ", " << "target=" << to_string(target);
  out << ", " << "distance=" << to_string(distance);
  out << ", " << "duration=" << to_string(duration);
  out << ")";
}


PointToPointRequest::~PointToPointRequest() throw() {
}


void PointToPointRequest::__set_source(const Point& val) {
  this->source = val;
}

void PointToPointRequest::__set_target(const Point& val) {
  this->target = val;
}

void PointToPointRequest::__set_step(const bool val) {
  this->step = val;
__isset.step = true;
}

uint32_t PointToPointRequest::read(::apache::thrift::protocol::TProtocol* iprot) {

  apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;

  bool isset_source = false;
  bool isset_target = false;

  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_STRUCT) {
          xfer += this->source.read(iprot);
          isset_source = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_STRUCT) {
          xfer += this->target.read(iprot);
          isset_target = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_BOOL) {
          xfer += iprot->readBool(this->step);
          this->__isset.step = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  if (!isset_source)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  if (!isset_target)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  return xfer;
}

uint32_t PointToPointRequest::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("PointToPointRequest");

  xfer += oprot->writeFieldBegin("source", ::apache::thrift::protocol::T_STRUCT, 1);
  xfer += this->source.write(oprot);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("target", ::apache::thrift::protocol::T_STRUCT, 2);
  xfer += this->target.write(oprot);
  xfer += oprot->writeFieldEnd();

  if (this->__isset.step) {
    xfer += oprot->writeFieldBegin("step", ::apache::thrift::protocol::T_BOOL, 3);
    xfer += oprot->writeBool(this->step);
    xfer += oprot->writeFieldEnd();
  }
  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(PointToPointRequest &a, PointToPointRequest &b) {
  using ::std::swap;
  swap(a.source, b.source);
  swap(a.target, b.target);
  swap(a.step, b.step);
  swap(a.__isset, b.__isset);
}

PointToPointRequest::PointToPointRequest(const PointToPointRequest& other4) {
  source = other4.source;
  target = other4.target;
  step = other4.step;
  __isset = other4.__isset;
}
PointToPointRequest& PointToPointRequest::operator=(const PointToPointRequest& other5) {
  source = other5.source;
  target = other5.target;
  step = other5.step;
  __isset = other5.__isset;
  return *this;
}
void PointToPointRequest::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "PointToPointRequest(";
  out << "source=" << to_string(source);
  out << ", " << "target=" << to_string(target);
  out << ", " << "step="; (__isset.step ? (out << to_string(step)) : (out << "<null>"));
  out << ")";
}


PointToPointResponse::~PointToPointResponse() throw() {
}


void PointToPointResponse::__set_code(const RetCode::type val) {
  this->code = val;
}

void PointToPointResponse::__set_distance(const double val) {
  this->distance = val;
}

void PointToPointResponse::__set_duration(const double val) {
  this->duration = val;
}

void PointToPointResponse::__set_steps(const std::vector<Step> & val) {
  this->steps = val;
__isset.steps = true;
}

void PointToPointResponse::__set_projections(const std::vector<Point> & val) {
  this->projections = val;
__isset.projections = true;
}

uint32_t PointToPointResponse::read(::apache::thrift::protocol::TProtocol* iprot) {

  apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;

  bool isset_code = false;
  bool isset_distance = false;
  bool isset_duration = false;

  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          int32_t ecast6;
          xfer += iprot->readI32(ecast6);
          this->code = (RetCode::type)ecast6;
          isset_code = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_DOUBLE) {
          xfer += iprot->readDouble(this->distance);
          isset_distance = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_DOUBLE) {
          xfer += iprot->readDouble(this->duration);
          isset_duration = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 4:
        if (ftype == ::apache::thrift::protocol::T_LIST) {
          {
            this->steps.clear();
            uint32_t _size7;
            ::apache::thrift::protocol::TType _etype10;
            xfer += iprot->readListBegin(_etype10, _size7);
            this->steps.resize(_size7);
            uint32_t _i11;
            for (_i11 = 0; _i11 < _size7; ++_i11)
            {
              xfer += this->steps[_i11].read(iprot);
            }
            xfer += iprot->readListEnd();
          }
          this->__isset.steps = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 5:
        if (ftype == ::apache::thrift::protocol::T_LIST) {
          {
            this->projections.clear();
            uint32_t _size12;
            ::apache::thrift::protocol::TType _etype15;
            xfer += iprot->readListBegin(_etype15, _size12);
            this->projections.resize(_size12);
            uint32_t _i16;
            for (_i16 = 0; _i16 < _size12; ++_i16)
            {
              xfer += this->projections[_i16].read(iprot);
            }
            xfer += iprot->readListEnd();
          }
          this->__isset.projections = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  if (!isset_code)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  if (!isset_distance)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  if (!isset_duration)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  return xfer;
}

uint32_t PointToPointResponse::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("PointToPointResponse");

  xfer += oprot->writeFieldBegin("code", ::apache::thrift::protocol::T_I32, 1);
  xfer += oprot->writeI32((int32_t)this->code);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("distance", ::apache::thrift::protocol::T_DOUBLE, 2);
  xfer += oprot->writeDouble(this->distance);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("duration", ::apache::thrift::protocol::T_DOUBLE, 3);
  xfer += oprot->writeDouble(this->duration);
  xfer += oprot->writeFieldEnd();

  if (this->__isset.steps) {
    xfer += oprot->writeFieldBegin("steps", ::apache::thrift::protocol::T_LIST, 4);
    {
      xfer += oprot->writeListBegin(::apache::thrift::protocol::T_STRUCT, static_cast<uint32_t>(this->steps.size()));
      std::vector<Step> ::const_iterator _iter17;
      for (_iter17 = this->steps.begin(); _iter17 != this->steps.end(); ++_iter17)
      {
        xfer += (*_iter17).write(oprot);
      }
      xfer += oprot->writeListEnd();
    }
    xfer += oprot->writeFieldEnd();
  }
  if (this->__isset.projections) {
    xfer += oprot->writeFieldBegin("projections", ::apache::thrift::protocol::T_LIST, 5);
    {
      xfer += oprot->writeListBegin(::apache::thrift::protocol::T_STRUCT, static_cast<uint32_t>(this->projections.size()));
      std::vector<Point> ::const_iterator _iter18;
      for (_iter18 = this->projections.begin(); _iter18 != this->projections.end(); ++_iter18)
      {
        xfer += (*_iter18).write(oprot);
      }
      xfer += oprot->writeListEnd();
    }
    xfer += oprot->writeFieldEnd();
  }
  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(PointToPointResponse &a, PointToPointResponse &b) {
  using ::std::swap;
  swap(a.code, b.code);
  swap(a.distance, b.distance);
  swap(a.duration, b.duration);
  swap(a.steps, b.steps);
  swap(a.projections, b.projections);
  swap(a.__isset, b.__isset);
}

PointToPointResponse::PointToPointResponse(const PointToPointResponse& other19) {
  code = other19.code;
  distance = other19.distance;
  duration = other19.duration;
  steps = other19.steps;
  projections = other19.projections;
  __isset = other19.__isset;
}
PointToPointResponse& PointToPointResponse::operator=(const PointToPointResponse& other20) {
  code = other20.code;
  distance = other20.distance;
  duration = other20.duration;
  steps = other20.steps;
  projections = other20.projections;
  __isset = other20.__isset;
  return *this;
}
void PointToPointResponse::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "PointToPointResponse(";
  out << "code=" << to_string(code);
  out << ", " << "distance=" << to_string(distance);
  out << ", " << "duration=" << to_string(duration);
  out << ", " << "steps="; (__isset.steps ? (out << to_string(steps)) : (out << "<null>"));
  out << ", " << "projections="; (__isset.projections ? (out << to_string(projections)) : (out << "<null>"));
  out << ")";
}

} // namespace
