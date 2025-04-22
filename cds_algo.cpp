

// include section
#include "cds_algo.h"
#include "sensor_functions.h"
#include <Arduino.h>
#include "mqtt_comm.h"
#include <ArduinoJson.h> 



void trigger_warning(double ultrasonic_dist, String timestamp, MqttComm &mqtt) {
  bool isCollision = false;
  
  // Log to the console 
  Serial.print("Warning triggered: near collision detected at distance ");
  Serial.println(ultrasonic_dist);

  // Create a JSON document for the warning
  StaticJsonDocument<256> jsonDoc;
  jsonDoc["timestamp"] = timestamp;
  jsonDoc["collision"] = isCollision;
  jsonDoc["severity"] = "PRE-COLLISION WARNING";
  jsonDoc["distance_cm"] = ultrasonic_dist;
  
  String jsonPayload;
  serializeJson(jsonDoc, jsonPayload);

  // Publish the JSON message to MQTT
  mqtt.publish(jsonPayload); 
}

void trigger_collision_alert(String message, double ultrasonic_dist, double thinfilm_severity, String timestamp, MqttComm &mqtt) {
  bool isCollision = true; // collision has occured

  // Log to the console 
  Serial.print("Collision detected: ");
  Serial.println(message);

  // Create a JSON document for the collision
  StaticJsonDocument<256> jsonDoc;
  jsonDoc["timestamp"] = timestamp;
  jsonDoc["collision"] = isCollision;
  jsonDoc["severity"] = message;
  jsonDoc["pressure"] = thinfilm_severity;
  jsonDoc["distance_cm"] = ultrasonic_dist;
  
  String jsonPayload;
  serializeJson(jsonDoc, jsonPayload);

  // Publish the JSON message to MQTT
  mqtt.publish(jsonPayload); 
}
// for pre collision detection only if the object is within the allotted distance will we warn the user

void precollision_warning(int trigPin, int echoPin, int colPin, String timestamp, MqttComm &mqtt)
{
  double ultrasonic_dist = read_ultrasonic_sns(trigPin, echoPin);
  int is_collision_detected = read_collision_sns(colPin);
  

  if (ultrasonic_dist < DISTANCE_THRESHOLD && ultrasonic_dist >= DANGER_THRESHOLD && is_collision_detected != COLLISION_DETECTION_THRESHOLD)
  {
    trigger_warning(ultrasonic_dist, timestamp, mqtt);
  }
  if (ultrasonic_dist < DANGER_THRESHOLD && is_collision_detected != COLLISION_DETECTION_THRESHOLD)
  {
    trigger_warning(ultrasonic_dist, timestamp, mqtt);
  }
}

// Collision Confirmation

void collision_detected(int trigPin, int echoPin, int colPin, int pressurePin, String timestamp, MqttComm &mqtt)
{
  double ultrasonic_dist = read_ultrasonic_sns(trigPin, echoPin);
  int is_collision_detected = read_collision_sns(colPin);

  
  if (ultrasonic_dist < DANGER_THRESHOLD && is_collision_detected == COLLISION_DETECTION_THRESHOLD)
  {
    double thinfilm_severeity = get_thinfilm_data(pressurePin);
    Serial.print("Thin Film Severity: ");
    Serial.println(thinfilm_severeity);
    if (thinfilm_severeity >= THINFILM_SENSOR_THRESHOLD_HIGH)
    {
      trigger_collision_alert("HIGH-SEVERITY IMPACT!", ultrasonic_dist, thinfilm_severeity, timestamp, mqtt);
    }
    else if (thinfilm_severeity >= THINFILM_SENSOR_THRESHOLD_MID)
    {
      trigger_collision_alert("MODERATE-SEVERITY IMPACT!", ultrasonic_dist, thinfilm_severeity, timestamp, mqtt);
    }
    else if (thinfilm_severeity >= THINFILM_SENSOR_THRESHOLD_LOW)
    {
      trigger_collision_alert("LOW-SEVERITY IMPACT!", ultrasonic_dist, thinfilm_severeity, timestamp, mqtt);
    }
    else
    {
      trigger_collision_alert("NO SEVERE IMPACT", ultrasonic_dist, thinfilm_severeity, timestamp, mqtt);
    }
  }
}