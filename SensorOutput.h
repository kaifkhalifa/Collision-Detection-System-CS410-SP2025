/*
================================
Filename: SensorOutput.h
Author: Gustavo Aguiar
Description: Contains functions use to read sensor data
================================
*/

#pragma once
#include <WiFi.h>
#include <string>

/**
 * @brief Connect to WiFi network
 * @param ssid SSID of the WiFi network
 * @param password Password of the WiFi network
 * @return void
 * @note This function should be called before attempting to connect to the WiFi network.
 */
void ConnectWiFi(const char* ssid, const char* password);

/**
 * @brief Continuously check the WiFi connection status and reconnect if necessary
 * @param void
 * @return void
 * @note This function should be called in the main loop to ensure the device stays connected to WiFi.
 */ 
void WiFiCheck(bool &isConnected);

/**
 * @brief Send pressure sensor data to the server
 * @param pin Pin number of the pressure sensor
 * @return Sensor data as an int
 */
int SendPressureSensorData(int &pin);

/**
 * @brief Send distance sensor data in centimeters to the server
 * @param pin Pin number of the distance sensor
 * @return Sensor data as a float 
 */
float SendDistanceSensorData(int &trigPin, int &echoPin);

/**
 * @brief Send collision sensor data to the server
 * @param pin Pin number of the collision sensor
 * @return 0 if collision is detected, 1 if no collision is detected
 */
int SendCollisionSensorData(int &pin);
