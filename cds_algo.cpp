// include section
#include "cds_algo.h"
#include "sensor_functions.h"
#include <Arduino.h>

void trigger_warning() {
  Serial.print("warning triggered");
}

void trigger_collision_alert(String message) {
  Serial.print("collision detected ");
  Serial.println(message);
}

// for pre collision detection only if the object is within the allotted distance will we warn the user

void precollision_warning(int trigPin, int echoPin, int colPin)
{
  double ultrasonic_dist = read_ultrasonic_sns(trigPin, echoPin);
  int is_collision_detected = read_collision_sns(colPin);

  if (ultrasonic_dist < DISTANCE_THRESHOLD && ultrasonic_dist >= DANGER_THRESHOLD && is_collision_detected != COLLISION_DETECTION_THRESHOLD)
  {
    trigger_warning();
  }
  if (ultrasonic_dist < DANGER_THRESHOLD && is_collision_detected != COLLISION_DETECTION_THRESHOLD)
  {
    trigger_warning();
  }
}

// Collision Confirmation

void collision_detected(int trigPin, int echoPin, int colPin, int pressurePin)
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
      trigger_collision_alert("HIGH-SEVERITY IMPACT!");
    }
    else if (thinfilm_severeity >= THINFILM_SENSOR_THRESHOLD_MID)
    {
      trigger_collision_alert("MODERATE-SEVERITY IMPACT!");
    }
    else if (thinfilm_severeity >= THINFILM_SENSOR_THRESHOLD_LOW)
    {
      trigger_collision_alert("LOW-SEVERITY IMPACT!");
    }
    else
    {
      trigger_collision_alert("NO SEVERE IMPACT");
    }
  }
}