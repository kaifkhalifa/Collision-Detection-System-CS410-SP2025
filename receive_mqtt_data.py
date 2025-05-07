import paho.mqtt.client as mqtt
import os
import json
import csv
import time
import smtplib
from email.message import EmailMessage
from dotenv import load_dotenv
from random import uniform
from cryptography.fernet import Fernet
import logging

logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)


def initialize():
    # loading the environment variables
    load_dotenv("env.env")

    # loading the encryption key and creating the Fernet object
    key = os.getenv("FERNET_KEY").encode()
    cipher = Fernet(key)

    send_email = 'hankins.emry@gmail.com'
    email_app_password = 'mzio ppcz ccgo gshe'
    # to_number = '2026795229@txt.att.net'

    # returning the cipher object and the email to send the message to
    return cipher, send_email, email_app_password


topic = "collision_data"
mqttBroker = "cdsproject.cloud.shiftr.io"


def send_sms_via_email(subject, body, send_email, to_number, email_app_password):
    msg = EmailMessage()
    msg.set_content(body)
    msg['Subject'] = subject
    msg['From'] = send_email
    msg['To'] = to_number

    # Use Gmail's SMTP server (or update if using another email provider)
    with smtplib.SMTP_SSL('smtp.gmail.com', 465) as smtp:
        smtp.login(send_email, email_app_password)
        smtp.send_message(msg)
        logging.info("Message sent!")


def get_phonenumber(device_id):
    filename = 'data.csv'
    try:
        with open(filename, mode='r') as csvfile:
            reader = csv.DictReader(csvfile)
            for row in reader:
                if row['device_id'].strip().lower() == device_id.strip().lower():
                    return row['phonenumber']
    except FileNotFoundError:
        logger.error("csv file not found")
    except Exception as e:
        logger.error(f'error reading csv: {e}')

    return None


def on_connect(client, userdata, flags, rc, properties):
    if rc == 0:  # 0 means successful connection
        logger.info("Successfully connected to the broker")
        client.subscribe(topic)
        logger.info(f"Subscribed to topic: {topic}")
    else:
        logger.error(f"Connection failed with code {rc}")


def on_message(client, userdata, msg):
    logger.info(f"Received message: {msg.payload.decode()}")
    cipher, send_email, email_app_password = userdata
    payload = msg.payload.decode()
    print(f"Received JSON: {payload}")
    try:
        data = json.loads(payload)
        deviceId = data.get("device_id")
        timestamp = data.get("timestamp")
        isCollision = data.get("collision")
        severityMessage = data.get("severity")
        pressureData = data.get("pressure")
        distanceFromObject = data.get("distance_cm")

        encryptedPhoneNumber = get_phonenumber(deviceId)

        if encryptedPhoneNumber is None:
            logging.error(
                f"No encrypted phone number found for device ID: {deviceId}")
            return

        try:
            # Convert to bytes
            encryptedPhoneNumber = encryptedPhoneNumber.encode('utf-8')

            # Decrypt the phone number
            phoneNumber = cipher.decrypt(encryptedPhoneNumber).decode('utf-8')
        except Exception as e:
            logging.exception("Failed to decrypt phone number")
            return

        sms_email = f"{phoneNumber}@txt.att.net"

        # send the message to the user based on if collisionc = true or false
        if isCollision:
            logger.info("sending collision text")
            subject = "Collision Detected"
            body = (
                f"Collision detected!\n"
                f"Severity: {severityMessage}\n"
                f"at time: {timestamp}"
            )
        else:
            logger.info("sending warning text")
            subject = "Warning Alert"
            body = (
                f"Warning Near Collision!!\n"
                f"Distance: {distanceFromObject} cm away\n"
                f"at time: {timestamp}"
            )
        send_sms_via_email(subject, body, send_email,
                           sms_email, email_app_password)
    except json.JSONDecodeError:
        logger.error(f"Failed to decode the JSON")


def run():

    cipher, send_email, email_app_password = initialize()
    client = mqtt.Client(callback_api_version=mqtt.CallbackAPIVersion.VERSION2)
    client.username_pw_set(username="cdsproject", password="hP8yIYhAryhXULuI")
    client.user_data_set((cipher, send_email, email_app_password))
    client.on_connect = on_connect
    client.on_message = on_message
    client.connect(mqttBroker, 1883, 60)
    client.loop_start()
    logger.info("MQTT client started")
    try:
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        logger.info("Stopping subscriber.")
        client.loop_stop()
    except Exception as e:
        logger.error(f"Error while running the MQTT client: {e}")


if __name__ == '__main__':
    # cipher, twilioClient, testPhoneNumber = initialize()
    run()

   
