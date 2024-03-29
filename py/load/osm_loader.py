from utils.coordinate_converter import convert_wgs84_to_gcj02
from imposm.parser import OSMParser
from collections import namedtuple
Node = namedtuple('Node', ['id', 'lat', 'lng'])
Way = namedtuple('Way', ['id', 'nodes'])
Link = namedtuple('Link', ['src', 'dst'])

class WayParser(object):
    ways_dict = dict()
    def parse(self, input_ways):
        for osm_id, tags, refs in input_ways:
            self.ways_dict[osm_id] = Way(osm_id, refs)

class NodeParser(object):
    nodes_dict = dict()
    def parse(self, input_coords):
        for osm_id, lng, lat in input_coords:
            _lat, _lng = convert_wgs84_to_gcj02(lat, lng)
            self.nodes_dict[osm_id] = Node(osm_id, _lat, _lng)

way_parser = WayParser()
node_parser = NodeParser()

import multiprocessing
cpu_count = multiprocessing.cpu_count()
parser = OSMParser(concurrency=cpu_count, 
    ways_callback=way_parser.parse, 
    coords_callback=node_parser.parse)

import os, requests
download_url = 'http://download.openstreetmap.fr/extracts/asia/china/{}.osm.pbf'
def load_osm_pbf(city):
    data_file = '{}.osm.pbf'.format(city)
    if os.path.exists(data_file): 
        print('{} already exist'.format(data_file))
    else:
        print('try downloading {}'.format(data_file))
        r = requests.get(download_url.format(city))
        with open(data_file, 'w') as f:
            f.write(r.content)
        print('download finished')
    return data_file
