from flask_apscheduler import APScheduler
from app import app
from database import db, Parameters
from app.esp32_connection import get_data

scheduler = APScheduler()


@scheduler.task("cron", id="save_data", minute="*")
def save_data():
    values = get_data()
    data = Parameters(temp=values["temp"], press=values["press"], absl=values["absl"])
    with app.app_context():
        db.session.add(data)
        db.session.commit()
    print("Parameters saved!")


scheduler.init_app(app)
scheduler.start()
