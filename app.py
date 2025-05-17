"""@file app.py
@brief Entry point for the Flask web application handling signups.

This application allows users to register their device and phone number to receive SMS alerts in case of a collision.
It also starts a background MQTT listener thread to receive messages from ESP32 devices.
"""

import os 
import csv
import logging
from cryptography.fernet import Fernet
from dotenv import load_dotenv
from flask import Flask, request, jsonify, render_template
from flask_cors import CORS
from threading import Thread
import receive_mqtt_data

def run_mqtt():
     """
    @brief Runs the MQTT listener function from the receive_mqtt_data module in a try-except block.
    
    This function is intended to run in a background thread to handle MQTT messages asynchronously.
    """
   try:
        receive_mqtt_data.run()
   except Exception as e:
        print(f"MQTT thread crashed: {e}")
   
def start_mqtt():
   """
    @brief Starts the MQTT listener thread as a daemon.
    
    This ensures that MQTT messages can be received without blocking the main Flask application.
    """
    mqtt_thread = Thread(target=run_mqtt, daemon=True)
    mqtt_thread.start()

start_mqtt()

app = Flask(__name__)

# loading the environment variables to get the Fernet key
load_dotenv("env.env")

# loading the encryption key and creating the Fernet object 
key = os.getenv("FERNET_KEY").encode()
cipher = Fernet(key)


FILENAME = 'data.csv'

@app.route('/signup', methods=['GET', 'POST'])
def signup():
    """
    @brief Handles user signup via a form (GET) or API call (POST).
    
    GET: Returns the HTML signup form.
    POST: Validates and stores user data in a CSV file with encrypted phone number.
    
    @return HTML page for GET, JSON response for POST.
    """
    if request.method == 'GET':
        return render_template('index.html')
    
    data = request.get_json()
   
    firstname = data.get("firstName")
    lastname = data.get("lastName")
    device_id = data.get("deviceId")
    phonenumber = data.get("phoneNumber")
    optin = data.get("optin") 
    
    # Validate that all required fields are present
    if not all([firstname, lastname, device_id, phonenumber]) or not optin:
            return jsonify({'message' : "Please fill in all fields. and agree to receive alerts"}), 400
    
   
    # Encrypts the data entered phone number for storage
    encrypted_phonenumber = cipher.encrypt(phonenumber.encode()).decode() 
    
    file_exists = os.path.isfile(FILENAME)
    
    try:
        with open(FILENAME, 'a', newline='') as csvfile:
            
            writer = csv.writer(csvfile)
            
            if not file_exists:
                writer.writerow(['firstname', 'lastname', 'device_id', 'phonenumber'])  # Headers for CSV
            
            writer.writerow([firstname, lastname, device_id, encrypted_phonenumber])  
            logging.info("Data saved successfully.")
    
    except Exception as e:
        logging.info(f"Error writing to CSV: {e}")
        return jsonify({"message": f"Error writing to CSV: {e}"}), 400  # returning error
    
    return jsonify({"message": "Signup successful!"}), 200  # returning a success message    
if __name__ == '__main__':
 """
    @brief Runs the Flask app in debug mode.
    """
    app.run(debug=True, use_reloader=False) 
