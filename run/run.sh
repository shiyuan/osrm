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
docker run -i -v ${PWD}:/data ${IMAGE} osrm-contract /data/${CITY}.osrm

# routed server
docker run -i -p 5000:5000 -v ${PWD}:/data ${IMAGE} osrm-routed /data/${CITY}.osrm

# test
# curl "http://127.0.0.1:5000/route/v1/driving/121.3199201313,31.2389434953;121.3774272910,31.2348205216?steps=true" | jq  '.routes[0]| [.duration, .distance]'
