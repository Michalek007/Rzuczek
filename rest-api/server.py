from gevent.monkey import patch_all; patch_all()
from app import app
from gevent import pywsgi
import os


server_wsgi = pywsgi.WSGIServer(listener=(tuple(app.config['LISTENER'].values())), application=app)


def run(server):
    return server.serve_forever()


if __name__ == '__main__':
    run(server_wsgi)
