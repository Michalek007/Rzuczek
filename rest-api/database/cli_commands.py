from app import app, bcrypt
from database import *


@app.cli.command('db_create')
def db_create():
    db.create_all()
    print('Database created!')


@app.cli.command('db_drop')
def db_drop():
    db.drop_all()
    print('Database dropped!')


@app.cli.command('db_seed')
def db_seed():
    user1 = User(username='first', pw_hash=bcrypt.generate_password_hash('1234'))
    user2 = User(username='second', pw_hash=bcrypt.generate_password_hash('1234'))
    user3 = User(username='third', pw_hash=bcrypt.generate_password_hash('1234'))
    db.session.add(user1)
    db.session.add(user2)
    db.session.add(user3)
    db.session.commit()
    print('Database seeded!')
