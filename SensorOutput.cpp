/*
=============================
Filename: SensorOutput.cpp
Author: Gustavo Aguiar
Description: Contains functions use to read sensor data
=============================
*/

#include "SensorOutput.h"

int SendPressureSensorData(int &pin) {
    int sensorValue = analogRead(pin);
    return sensorValue;
}

float SendDistanceSensorData(int &trigPin, int &echoPin) {
    // Send sound wave
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Listens for sound wave
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    
    float distance = pulseIn(echoPin, HIGH) / 58.2; // Convert to cm
    return distance;
}

int SendCollisionSensorData(int &pin) {
    int sensorValue = digitalRead(pin);
    return sensorValue;
}
