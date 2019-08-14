IMAGE=osrm_flask
DIR=`pwd`
PORT=10000
CITY=shanghai

# build docker
cd .. && cp flask_server/Dockerfile . && \
  docker build -t ${IMAGE} . && \
  rm -rf Dockerfile && cd $DIR

# get host
THRIFT_SERVER_IP=`python -c "import socket
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.connect(('8.8.8.8', 80))
print(s.getsockname()[0])
s.close()"`

# run flask server
docker run -d -v ${PWD}/../py:/opt/py -p ${PORT}:${PORT} -t ${IMAGE} \
   sh -c "cd py && python flask_server.py -ti ${THRIFT_SERVER_IP} -tp 5000 -p ${PORT} -c ${CITY}"
