#!/bin/bash
IMAGE='osrm_demo'
CITY='shanghai'
STXXL_MEM='2G'
MODE='car' # car or bicycle or foot

# build docker
cd .. && cp run/Dockerfile . && \
  docker build -t ${IMAGE} . && \
  rm -rf Dockerfile && cd run

# download data
wget http://download.openstreetmap.fr/extracts/asia/china/${CITY}.osm.pbf

# extract
docker run -i -v ${PWD}:/data ${IMAGE} sh -c "echo 'disk=/tmp/stxxl,${STXXL_MEM},syscall unlink' > .stxxl && osrm-extract /data/${CITY}.osm.pbf -p profiles/${MODE}.lua"

# contract
docker run -i -v ${PWD}:/data ${IMAGE} sh -c "echo 'disk=/tmp/stxxl,${STXXL_MEM},syscall unlink' > .stxxl && osrm-contract /data/${CITY}.osrm"

# http server
#docker run -i -p 5000:5000 -v ${PWD}:/data ${IMAGE} osrm-routed /data/${CITY}.osrm
# curl "http://127.0.0.1:5000/route/v1/driving/121.3244462013,31.2370225222;121.3820385933,31.2329448269?steps=true" | jq  '.routes[0]| [.duration, .distance]'

# thrift server
# docker run -i -p 5000:5000 -v ${PWD}:/data ${IMAGE} sh -c "export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib:/usr/lib && osrm-server /data/${CITY}.osrm"
docker run -i -p 5000:5000 -v ${PWD}:/data ${IMAGE} sh -c "source ~/.bashrc && osrm-server /data/${CITY}.osrm"

echo done
