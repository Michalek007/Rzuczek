from sqlalchemy import Column, Integer, String, Float
from app import ma
from database import db


class Parameters(db.Model):
    __tablename__ = 'parameters'
    id = Column(Integer, primary_key=True)
    temp = Column(Float)
    press = Column(Float)
    absl = Column(Float)


class ParametersSchema(ma.Schema):
    class Meta:
        fields = ('id', 'temp', 'press', 'absl')


parameter_schema = ParametersSchema()
parameters_schema = ParametersSchema(many=True)
