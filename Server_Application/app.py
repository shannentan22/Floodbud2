from flask import Flask, render_template, request, url_for, redirect
import serial
import os
import pytz
from flask_sqlalchemy import SQLAlchemy
from datetime import datetime, timedelta
from sqlalchemy import Sequence
from sqlalchemy import func

# Replace 'Asia/Singapore' with the appropriate timezone identifier
utc_plus_eight = pytz.timezone('Asia/Singapore')

basedir = os.path.abspath(os.path.dirname(__file__))
app = Flask(__name__)
# ser = serial.Serial('COM7', 9600)

# create the extension
db = SQLAlchemy()
# db.dropall()
# create the app
app = Flask(__name__)
# configure the SQLite database, relative to the app instance folder
app.config["SQLALCHEMY_DATABASE_URI"] = "sqlite:///project.db"
# initialize the app with the extension
db.init_app(app)


class DeviceLocation(db.Model):
    __tablename__ = 'device_location'
    deviceid = db.Column(db.Integer, primary_key=True)
    location = db.Column(db.String(100), nullable=False)

    def __repr__(self):
        return self.location


class Records(db.Model):
    # device id
    __tablename__ = 'water_level'
    readingid = db.Column(db.Integer, Sequence(
        'reading_id_seq'), primary_key=True)
    deviceid = db.Column(db.Integer, db.ForeignKey('device_location.deviceid'))
    timestamp = db.Column(db.DateTime(timezone=True),
                          default=lambda: datetime.now(utc_plus_eight))
    reading = db.Column(db.String, nullable=False)
    location = db.relationship(
        'DeviceLocation', backref='water_level', lazy=True)

    def __repr__(self):
        return f'<Device {self.deviceid}: {self.reading} at {self.timestamp}, readingID = {self.readingid}, location = {self.location}>'


with app.app_context():
    db.create_all()

devices = []


@app.route('/arduino', methods=['POST'])
def arduino():
    data = request.form.get('data')
    ser.write(data.encode())
    response = ser.readline().decode().strip()
    return response


@app.route('/', methods=['GET', 'POST'])
def index():
    global data  # Use the global data variable

    if request.method == 'POST':
        new_data = request.get_json()
        # Input format: { 'DeviceID': '', 'WaterLevel': ''}
        if new_data:
            # raw_date =datetime.utcnow() # Obtaining datetime
            # rounded_date = raw_date.replace(microsecond=0) + timedelta(seconds=round(raw_date.microsecond / 1000000))

            DeviceID = int(new_data.get('DeviceID'))
            # Timestamp = str(rounded_date)
            WaterLevel = new_data.get('WaterLevel')

            record = Records(deviceid=DeviceID, reading=WaterLevel)

            db.session.add(record)
            db.session.commit()
    update_db()
    print(devices)

    return render_template('index.html', devices=devices)


def update_db():
    devices.clear()
    for device in sorted(list({record.deviceid for record in Records.query.all()})):
        timestamps = []
        readings = []
        for entry in Records.query.filter_by(deviceid=device):
            timestamps.insert(0, entry.timestamp)
            readings.insert(0, entry.reading.title())

        if len(devices) > device:
            devices[device]['Timestamps'].extend(timestamps)
            devices[device]['WaterLevels'].extend(readings)
        else:
            new_device = {
                'DeviceID': device,
                'Location': entry.location,
                'Timestamps': timestamps,
                'WaterLevels': readings,
            }
            devices.insert(device, new_device)


if __name__ == '__main__':
    app.run(host='192.168.1.3', port=5050, debug=True, threaded=False)
