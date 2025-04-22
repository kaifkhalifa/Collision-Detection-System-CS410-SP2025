#ifndef CDS_ALGO_H
#define CDS_ALGO_H

#include <Arduino.h>
#include <ArduinoJson.h> 
#include "mqtt_comm.h"

const int DISTANCE_THRESHOLD = 50;             // If the object is farther than this, we do nothing
const int DANGER_THRESHOLD = 20;               // If an object is detected under this distance, we check for collision confirmation
const int COLLISION_DETECTION_THRESHOLD = 0;   // 0 for impact detected, 1 for no impact
const int THINFILM_SENSOR_THRESHOLD_HIGH = 80; // High severity impact threshold for the thin-film sensor
const int THINFILM_SENSOR_THRESHOLD_MID = 50;  // Moderate severity threshold for the thin-film sensor
const int THINFILM_SENSOR_THRESHOLD_LOW = 30;  // Low severity threshold for the thin-film sensor

// Function declarations for collision detection system
void precollision_warning(int trigPin, int echoPin, int colPin, String timestamp, MqttComm &mqtt);
void collision_detected(int trigPin, int echoPin, int colPin, int pressurePin, String timestamp, MqttComm &mqtt);
void trigger_warning(String message, MqttComm &mqtt);
void trigger_collision_alert(String message, MqttComm &mqtt);

#endif
