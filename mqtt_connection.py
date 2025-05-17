#CODE FOR TESTING RECEIVING DATA FROM THE MQTT BROKER 

import paho.mqtt.client as mqtt
import json
import time
from random import uniform



topic = "collision_data"
mqttBroker = "cdsproject.cloud.shiftr.io"
client = mqtt.Client(client_id="ESP32_TEST",
                     callback_api_version=mqtt.CallbackAPIVersion.VERSION2)
client.username_pw_set(username="cdsproject", password="hP8yIYhAryhXULuI")

client.connect(mqttBroker)

timestamp = int(time.time())
collision = True
severity = round(uniform(1.0, 10.0), 2)
pressure = round(uniform(0.5, 2.0), 2)
distance_cm = round(uniform(1.0, 100.0), 2)
device_name = "ESP32_TEST"

try:
    while True:
        # Create the message payload with random values
        payload = {
            "device_id": "DEMOESP",
            "timestamp": time.time(),
            "collision": True,
            "severity": uniform(20.0, 21.5),
            "pressure": uniform(1.0, 10.0),
            "distance_cm": uniform(10.0, 100.0)
            
        }

        # Publish the message to the topic
        client.publish(topic, json.dumps(payload))
        print(f"Just published {payload} to topic {topic}")
        
        # Wait for a while before publishing again (e.g., 5 seconds)
        time.sleep(5)

except KeyboardInterrupt:
    print("Publisher stopped.")
    client.disconnect()
