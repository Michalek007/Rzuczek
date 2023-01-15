from app import app
from app.periodic_tasks import *

if __name__ == '__main__':
    app.run(host='0.0.0.0')
