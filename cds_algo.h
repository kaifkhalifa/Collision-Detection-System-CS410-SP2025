#ifndef CDS_ALGO_H
#define CDS_ALGO_H

#include <Arduino.h>
#include <ArduinoJson.h> 
#include "mqtt_comm.h"

const int DISTANCE_THRESHOLD = 50;             // If the object is farther than this, we do nothing
const int COLLISION_DETECTION_THRESHOLD = 0;   // 0 for impact detected, 1 for no impact
const int THINFILM_SENSOR_THRESHOLD_HIGH = 3500; // High severity impact threshold for the thin-film sensor
const int THINFILM_SENSOR_THRESHOLD_MID = 1000;  // Moderate severity threshold for the thin-film sensor
const int THINFILM_SENSOR_THRESHOLD_LOW = 100;  // Low severity threshold for the thin-film sensor

/**
  * @brief Sends a warning if within the distance threshold
  * @param trigPin Pin number for trig pin
  * @param echoPin Pin number for echo pin
  * @param colPin Pin number for collision pin
  * @param timestamp Current data and time of when the function was called
  * @param mqtt MQTT class object reference
  */
void trigger_warning(double ultrasonic_dist, String timestamp, MqttComm &mqtt);

/**
  * @brief Sends a collision warning
  * @param trigPin Pin number for trig pin
  * @param echoPin Pin number for echo pin
  * @param colPin Pin number for collision pin
  * @param timestamp Current data and time of when the function was called
  * @param mqtt MQTT class object reference
  */
void trigger_collision_alert(String message, double ultrasonic_dist, double thinfilm_severity, String timestamp, MqttComm &mqtt);

/**
  * @brief Checks if a collision was detected 
  * @param trigPin Pin number for trig pin
  * @param echoPin Pin number for echo pin
  * @param colPin Pin number for collision pin
  * @param pressurePin Pin number for pressure pin
  * @return true if collision was detected
  */
bool collision_detected(int trigPin, int echoPin, int colPin, int pressurePin);

#endif
