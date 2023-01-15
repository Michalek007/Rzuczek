from flask import Flask
from flask_bcrypt import Bcrypt
from flask_jwt_extended import JWTManager
from flask_marshmallow import Marshmallow
from configuration import Config

app = Flask(__name__)

app.config.from_object(Config)

jwt = JWTManager(app)
bcrypt = Bcrypt(app)
ma = Marshmallow(app)

from app.views import *
from database.cli_commands import *
