from sqlalchemy import Column, Integer, String
from database import db
from app import ma


class Note(db.Model):
    __tablename__ = 'notes'
    id = Column(Integer, primary_key=True)
    userid = Column(Integer)
    note = Column(String)


class NoteSchema(ma.Schema):
    class Meta:
        fields = ('id', 'userid', 'note')


note_schema = NoteSchema()
notes_schema = NoteSchema(many=True)
