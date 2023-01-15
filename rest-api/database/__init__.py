from flask_sqlalchemy import SQLAlchemy
from app import app

db = SQLAlchemy()
db.init_app(app)

from database.user import User, user_schema, users_schema
from database.note import Note, note_schema, notes_schema
from database.performance import Performance, performance_schema, performances_schema
