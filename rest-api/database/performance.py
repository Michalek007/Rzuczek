from sqlalchemy import Column, Integer, String, Float
from app import ma
from database import db


class Performance(db.Model):
    __tablename__ = 'performance'
    id = Column(Integer, primary_key=True)
    date = Column(String, unique=True)
    memory_usage = Column(Float)
    CPU_usage = Column(Float)
    disk_usage = Column(Float)


class PerformanceSchema(ma.Schema):
    class Meta:
        fields = ('id', 'date', 'memory_usage', 'CPU_usage', 'disk_usage')


performance_schema = PerformanceSchema()
performances_schema = PerformanceSchema(many=True)
