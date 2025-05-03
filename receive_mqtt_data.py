import paho.mqtt.client as mqtt
import os
import json
import csv
import time
from twilio.rest import Client
from dotenv import load_dotenv
from random import uniform
from cryptography.fernet import Fernet

def initialize():
    # loading the environment variables
    load_dotenv("env.env")

    # loading the encryption key and creating the Fernet object 
    key = os.getenv("FERNET_KEY").encode()
    cipher = Fernet(key)

    # loading the twilio number, account ssid, and auth key to send text message alerts
    authKey = os.getenv("TWILIO_TEST_AUTH_TOKEN")
    accountSSID = os.getenv("TWILIO_TEST_SSID")
    testPhoneNumber = os.getenv("TWILIO_PHONENUMBER")

    # creating the twilio object responsible for sending text alerts!
    twilioClient = Client(accountSSID, authKey)
    return cipher, twilioClient, testPhoneNumber 

topic = "collision_data"
mqttBroker = "cdsproject.cloud.shiftr.io"

def send_sms(client,body, from_number, to_number):
    try:
        message = client.messages.create(
            body=body,
            from_= from_number,
            to=to_number
        )
        print(f"Message sent! SID: {message.sid}")
    except Exception as e:
        print(f"Failed to send SMS: {e}")
        
def get_phonenumber(device_id):
    filename = 'data.csv'
    try:
        with open(filename, mode='r') as csvfile:
            reader = csv.DictReader(csvfile)
            for row in reader:
                if row['device_id'] == device_id:
                    return row['phonenumber']
    except FileNotFoundError:
        print("csv file not found")
    except Exception as e:
        print(f'error reading csv: {e}')
        
    return None

def on_connect(client, userdata, flags, rc, properties):
    if rc == 0:  # 0 means successful connection
        print("Successfully connected to the broker")
        client.subscribe(topic)
    else:
        print(f"Connection failed with code {rc}")

def on_message(client, userdata, msg):
    
    cipher, twilioClient, testPhoneNumber = userdata
    
    payload = msg.payload.decode()
    print(f"Received JSON: {payload}")
    try:
        data = json.loads(payload)
        deviceId = data.get("device_id")
        timestamp = data.get("timestamp")
        isCollision = data.get("collision")
        severityMessage = data.get("severity")
        pressureData = data.get("pressure")
        distanceFromObject = data.get("distanc_cm")
        
        encryptedPhoneNumber = get_phonenumber(deviceId)
        phoneNumber = cipher.decrypt(encryptedPhoneNumber)
        
        
        # send the message to the user based on if collisionc = true or false
        if isCollision == 'true':
            print("sending collision text")
        else:
            print("sending warning text")
    except json.JSONDecodeError:
        print(f"Failed to decode the JSON")

    



def run():
    
    """ cipher, twilioClient, testPhoneNumber = initialize()
    
    client = mqtt.Client(callback_api_version=mqtt.CallbackAPIVersion.VERSION2)
    client.username_pw_set(username="cdsproject", password="hP8yIYhAryhXULuI")
    
    client.user_data_set((cipher, twilioClient, testPhoneNumber ))
    client.on_connect = on_connect
    client.on_message = on_message
    client.connect(mqttBroker, 1883, 60)
    client.loop_start()
 
    try:
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        print("Stopping subscriber.")
        client.loop_stop()
 """
    
if __name__ == '__main__':
    cipher, twilioClient, testPhoneNumber = initialize()
   