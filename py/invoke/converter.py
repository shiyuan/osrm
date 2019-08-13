import os
import json
from thrift_converter import JsonThriftConverter, ThriftJsonConverter

thrift_file = os.path.dirname(__file__) + '/map_service.thrift'

print(thrift_file)
