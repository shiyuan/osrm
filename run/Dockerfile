FROM centos:7.6.1810 AS base
RUN mkdir -p /src /opt

FROM base AS builder
WORKDIR /src

# environment
RUN yum install -y gcc gcc-c++ wget \
    make cmake vim git

# gcc-5.4.0
RUN yum install -y texinfo bzip2 file && \
  wget https://mirrors.ustc.edu.cn/gnu/gcc/gcc-5.4.0/gcc-5.4.0.tar.gz && \
  tar vxf gcc-5.4.0.tar.gz && \
  cd gcc-5.4.0 && \
  ./contrib/download_prerequisites && \
  mkdir build && cd build && \
  ../configure --enable-checking=release --enable-languages=c,c++ --disable-multilib && \
  make && make install && \
  cd ../.. && \
  rm -rf gcc-5.4.0* && \
  rm -rf /usr/lib64/libstdc++.so.6* && \
  ln -s /usr/local/lib64/libstdc++.so.6.0.21 /usr/lib64/libstdc++.so.6

# boost 1.63
RUN yum install -y python-devel zlib-devel && \
  wget https://dl.bintray.com/boostorg/release/1.63.0/source/boost_1_63_0.tar.bz2 && \
  tar jvxf boost_1_63_0.tar.bz2 && cd boost_1_63_0 && \
  export CC=/usr/local/bin/gcc CXX=/usr/local/bin/g++ && \
  ./bootstrap.sh && \
  ./b2 cxxflags="--std=c++11" --includedir=/usr/include --libdir=/usr/lib64 release install && \
  cd .. && rm -rf boost_*

# luabind
RUN yum install -y lua-devel && \
  git clone https://github.com/rpavlik/luabind.git -b master && \
  cd luabind && \
  git checkout a0edf58e14cfb8cd4f13779707921b5e9caf686c && \
  mkdir build && cd build && \
  export CC=/usr/local/bin/gcc CXX=/usr/local/bin/g++ && \
  cmake .. && \
  make && make install && \
  cd ../.. && rm -rf luabind

# stxxl 1.4.0
RUN wget -O stxxl-1.4.0.tar.gz https://github.com/stxxl/stxxl/archive/1.4.0.tar.gz && \
  tar vxf stxxl-1.4.0.tar.gz && \
  cd stxxl-1.4.0 && \
  mkdir build && cd build && \
  export CC=/usr/local/bin/gcc CXX=/usr/local/bin/g++ && \
  cmake -DCMAKE_BUILD_TYPE=Release ..  && \
  make && make install && \
  cd ../.. && rm -rf stxxl-*

# thrift 0.10.0
#RUN export CC=/usr/local/bin/gcc CXX=/usr/local/bin/g++ && \
#  yum install -y libtool flex bison && \
#  wget -O thrift-0.10.0.tar.gz https://github.com/apache/thrift/archive/0.10.0.tar.gz && \
#  tar vxf thrift-0.10.0.tar.gz && \
#  cd thrift-0.10.0 && \
#  ./bootstrap.sh && \
#  ./configure --without-qt4 --without-qt5 --without-java --without-nodejs --without-lua --without-csharp --without-erlang --without-perl --without-php --without-php_extension --without-haskell --without-dart --without-ruby --without-haskell --without-go --without-haxe --without-d && \
#  make && make install && \
#  rm -rf thrift-*

# devel
RUN yum install -y libzip-devel expat-devel \
  tbb-devel bzip2-devel

COPY osrm-backend /src/osrm-backend
RUN export CC=/usr/local/bin/gcc CXX=/usr/local/bin/g++ && \
  cd osrm-backend && \
  mkdir -p build && \
  cd build && \
  cmake .. -DCMAKE_BUILD_TYPE=Release && \
  cmake --build . && \
  cmake --build . --target install && \
  make && \
  cd ../../ && \
  cp -r osrm-backend/profiles /opt && \
  rm -rf osrm-backend

FROM builder AS runstage
COPY --from=builder /usr/local /usr/local
WORKDIR /opt
