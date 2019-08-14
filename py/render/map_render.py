import folium
map_tileset = ('https://webrd01.is.autonavi.com/appmaptile?'
               'lang=zh_cn&size=1&scale=1&style=8&x={x}&y={y}&z={z}')

load_node_location = lambda x: (x.lat, x.lng)
get_avg_location = lambda x, y: ((x.lat + y.lat)/2., (x.lng + y.lng)/2.)

import uuid
gen_uuid = lambda: uuid.uuid4().hex

import os
rm_file = lambda x: os.system('rm -rf {}'.format(x))

import sys
sys.path.append(os.path.dirname(__file__) + '/..')
from utils.distance import gcd_distance

# converte folium map to html text
def map_to_text(m):
    temp_file = gen_uuid()
    try:
        m.save(temp_file)
        with open(temp_file) as f:
            res = f.read()
    finally:
        rm_file(temp_file)
    return res

def render_node(m, node, color='black', radius=3):
    detail = 'id: {:.0f}, loc: {:.6f},{:.5f}'.format(node.id, node.lat, node.lng)
    folium.Circle(
        load_node_location(node), 
        radius = radius,
        fill = True,
        color = color,
        popup = detail
   ).add_to(m)

def render_line(m, source, target, color='green', weight=5, extra=''):
    road_length = int(gcd_distance(source.lat, source.lng, target.lat, target.lng) + .5)
    detail = 'from {} to {}, road_length: {:.2f}'.format(source.id, target.id, road_length) + ', {}'.format(extra)
    folium.PolyLine(
        [load_node_location(x) for x in [source, target]],
        color = color,
        weight = weight,
        opacity = 1,
        popup = detail
    ).add_to(m)

def render_node_icon(m, node, color, extra):
    detail = '{}, loc: {:.6f},{:.5f}'.format(extra, node.lat, node.lng)
    folium.Marker(
        [node.lat, node.lng],
        popup = detail,
        icon = folium.Icon(color=color)
    ).add_to(m)

def render_node_connection(m, source, target, color):
    folium.PolyLine(
        [load_node_location(x) for x in [source, target]],
        opacity = 0.8,
        color = color
    ).add_to(m)


def render_map(all_nodes, route):
    content = 'distance: {:.2f}, duration: {:.2f}'.format(route.distance, route.duration)
    avg_location = get_avg_location(*[all_nodes[step.target] for step in [route.steps[0], route.steps[-1]]])
    return folium.Map(
        location = avg_location,
        zoom_start = 12,
        attr = content,
        tiles = map_tileset
    )

def gen_map(all_nodes, route, source, target):
    m_ = render_map(all_nodes, route)
    nodes = []
    for step in route.steps:
        content = 'distance: {}, duration: {}'.format(step.distance, step.duration)
        step_source = all_nodes[step.source]
        step_target = all_nodes[step.target]
        render_line(m_, step_source, step_target, 'green', 5, content)
        if len(nodes) == 0:
            nodes.append(step_source)
        nodes.append(step_target)
    
    for node in nodes:
        render_node(m_, node, 'orange')

    render_node_icon(m_, source, 'blue', 'origin source')
    render_node_icon(m_, target, 'darkred', 'origin target')

    proj_source, proj_target = route.projections
    render_node_icon(m_, proj_source, 'lightblue', 'project source')
    render_node_icon(m_, proj_target, 'red', 'project target')   
    render_node_connection(m_, source, proj_source, 'orange')
    render_node_connection(m_, target, proj_target, 'orange')

    return map_to_text(m_)

