#include "cds_algo.h"
#include "sensor_functions.h"
#include <Arduino.h>
#include <String>
#include "mqtt_comm.h"
#include <time.h>

/**

@brief Retrieves the current time as a formatted string in EST (Eastern Standard Time).

This function attempts to obtain the local time using the system clock and format it

into a human-readable string of the form: "YYYY-MM-DD HH:MM:SS".

Note: Ensure the time zone is set properly using configTime() before calling this.

If the time is unavailable (e.g., WiFi or NTP issues), it will return "TIME_UNAVAILABLE".

@return A String containing the current date and time in EST, or "TIME_UNAVAILABLE" if not set. */

String getCurrentTimeString() {
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        return "TIME_UNAVAILABLE";
    }

    char timeStr[64];
    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", &timeinfo);
    return String(timeStr);
}

// MQTT class, fill with your own data if testing

MqttComm mqtt(
    "WiFi SSID", //ssid
    "WiFi Password", // wifi password
    "cdsproject.cloud.shiftr.io", // mqtt broker
    1883, // port 
    "cdsproject", // mqtt username
    "hP8yIYhAryhXULuI", // MQTT password
    "collision_data" // MQTT topic
);

int ECHO_PIN = 14;
int TRIG_PIN = 13;
int COLLISION_PIN = 25;
int THINFILM_PIN = 32;

bool isConnected = false;
float distance = 0.0;
bool checkDistance = true;

void setup() {
  Serial.begin(9600);
  mqtt.begin();
  configTime(-5 * 3600, 0, "pool.ntp.org", "time.nist.gov"); //configuring the time 

  // Configure pins
  pinMode(THINFILM_PIN, INPUT);
  pinMode(COLLISION_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

}

void loop() {
  mqtt.loop();
  String timestamp = getCurrentTimeString(); // getting curent time

  distance = read_ultrasonic_sns(TRIG_PIN, ECHO_PIN);

  // If checking for distance and distance is less than the distance threshold, trigger a warning and stop checking for distance
  if (checkDistance && distance < DISTANCE_THRESHOLD) {
    trigger_warning(distance, timestamp, mqtt);
    checkDistance = false;
  // Otherwise,
  } else {
    // Check if distance is greater than threshold and we are not checking distance for warnings
    // Start checking for distance again
    if (distance > DISTANCE_THRESHOLD && !checkDistance) {
      checkDistance = true; // Reset the checkDistance flag when the distance is above the threshold
      Serial.println("Will check for distance warning again");
    // Or, if we detect a collision
    } else if (collision_detected(TRIG_PIN, ECHO_PIN, COLLISION_PIN, THINFILM_PIN)) {
      // Get thin film data
      double thinfilm_severeity = get_thinfilm_data(THINFILM_PIN);

      Serial.print("Thin Film Severity: ");
      Serial.println(thinfilm_severeity);
      // Check the severity of the thin film value and trigger an alert
      if (thinfilm_severeity >= THINFILM_SENSOR_THRESHOLD_HIGH)
      {
        trigger_collision_alert("HIGH-SEVERITY IMPACT!", 0, thinfilm_severeity, timestamp, mqtt);
      }
      else if (thinfilm_severeity >= THINFILM_SENSOR_THRESHOLD_MID)
      {
        trigger_collision_alert("MODERATE-SEVERITY IMPACT!", 0, thinfilm_severeity, timestamp, mqtt);
      }
      else if (thinfilm_severeity >= THINFILM_SENSOR_THRESHOLD_LOW)
      {
        trigger_collision_alert("LOW-SEVERITY IMPACT!", 0, thinfilm_severeity, timestamp, mqtt);
      }
      else
      {
        trigger_collision_alert("NO SEVERE IMPACT", 0, thinfilm_severeity, timestamp, mqtt);
      }
      delay(5000); // Delay to avoid flooding the serial monitor
    }
  }
}

