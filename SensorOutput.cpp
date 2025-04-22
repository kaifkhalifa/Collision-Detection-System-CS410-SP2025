
/*
=============================
Filename: SensorOutput.cpp
Author: Gustavo Aguiar
Description: Contains functions use to read sensor data
*/

#include "SensorOutput.h"

void ConnectWiFi(const char* ssid, const char* password) {
    String ssidString = String(ssid);
    String passwordString = String(password);
    Serial.println(ssidString);
    Serial.println(passwordString);
    Serial.println("Connecting to WiFi...");
    WiFi.begin(ssidString, passwordString);
}

void WiFiCheck(bool &isConnected) {
    if (WiFi.status() == WL_CONNECTED && !isConnected) {
        Serial.println("Connected");
        digitalWrite(LED_BUILTIN, HIGH); // Turn on the LED to indicate connection
        isConnected = true;
    }

    if(WiFi.status() != WL_CONNECTED){
        Serial.print(".");
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); // Blink the LED to indicate disconnection
        delay(1000);
        isConnected = false;
        //WiFi.reconnect();
    }
}

int SendPressureSensorData(int &pin) {
    int sensorValue = analogRead(pin);
    //Serial.print("Pressure Sensor Value: ");
    //Serial.println(sensorValue);
    return sensorValue;
}

float SendDistanceSensorData(int &trigPin, int &echoPin) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    
    float distance = pulseIn(echoPin, HIGH) / 58.2; // Convert to cm

    //Serial.print("Distance Sensor Value: ");
    //Serial.println(distance); // Convert to cm

    return distance; // Convert to cm
}

int SendCollisionSensorData(int &pin) {
    int sensorValue = digitalRead(pin);
    //Serial.print("Collision Sensor Value: ");
    //Serial.println(sensorValue);
    return sensorValue;
}