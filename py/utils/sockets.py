import socket
from contextlib import contextmanager

@contextmanager
def upd():
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.connect(('8.8.8.8', 80))
    yield s
    s.close()
    
def get_host_ip():
    ip = None
    with upd() as s:
        ip = s.getsockname()[0]
    return ip
