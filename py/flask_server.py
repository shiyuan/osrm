from flask import Flask, request
app = Flask(__name__)

from thrift_json import thrift2json
from load.osm_loader import Node
from invoke.invoke import Invoker

def parse_route_request():
    step = request.args.get('step', False)
    req_str = request.args.get('req')
    try:
        source, target = map(lambda x: map(float, x.split(',')), req_str.split(';'))
    except Exception, e:
        return False, 'Invalid Request: {}'.format(req_str)
    source_node = Node(0, source[0], source[1])
    target_node = Node(1, target[0], target[1])
    return True, source_node, target_node, step


@app.route('/api/route')
def route_api():
    reqs = parse_route_request()
    if not reqs[0]:
        return reqs[1]
    source, target, step = reqs[1:]
    ret = invoker.p2p(source, target, step)
    return thrift2json(ret)


@app.route('/route')
def route():
    return None


def parse_args():
    import argparse
    parser = argparse.ArgumentParser()
    parser.add_argument('--thrift_ip', default='localhost')
    parser.add_argument('--thrift_port', default=5000)
    parser.add_argument('--server_port', default=10000)
    return parser.parse_args()

if __name__ == '__main__':
    args = parse_args()
    global invoker
    invoker = Invoker(args.thrift_ip, args.thrift_port)
    app.run('0.0.0.0', port=args.server_port, threaded=True, debug=True)
