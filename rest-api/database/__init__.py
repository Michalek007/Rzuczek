from flask_sqlalchemy import SQLAlchemy
from app import app

db = SQLAlchemy()
db.init_app(app)

from database.user import User, user_schema, users_schema
from database.parameters import Parameters, parameter_schema, parameters_schema
