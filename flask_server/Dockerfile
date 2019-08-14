FROM centos:7.6.1810
RUN mkdir -p /opt

WORKDIR /opt

RUN yum install -y gcc gcc-c++ vim
RUN yum install -y python-devel protobuf-devel

RUN yum install -y epel-release
RUN yum install -y python-pip

RUN pip install --upgrade pip
RUN pip install imposm.parser \
  thrift==0.10.0 \
  flask \
  folium \
  thrift_json
