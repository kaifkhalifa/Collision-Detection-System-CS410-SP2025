#include "cds_algo.h"
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
    "Widesocks", //ssid
    "44Crescentgamers", // wifi password
    "cdsproject.cloud.shiftr.io", // mqtt broker
    1883, // port 
    "cdsproject", // mqtt username
    "hP8yIYhAryhXULuI", // MQTT password
    "collision_data" // MQTT topic
);


// Replace with SSID and password of desired WiFi
//#define WIFI_SSID "NETGEAR74"
//#define WIFI_PASSWORD "helpfulflower781"

int ECHO_PIN = 14;
int TRIG_PIN = 13;
int COLLISION_PIN = 25;
int THINFILM_PIN = 32;

bool isConnected = false;

void setup() {
  Serial.begin(9600);
  mqtt.begin();
  configTime(-5 * 3600, 0, "pool.ntp.org", "time.nist.gov"); //configuring the time 

  pinMode(THINFILM_PIN, INPUT);
  pinMode(COLLISION_PIN, INPUT_PULLDOWN);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
 mqtt.loop();
 String timestamp = getCurrentTimeString(); // getting curent time
 precollision_warning(TRIG_PIN, ECHO_PIN, COLLISION_PIN, timestamp, mqtt);
 collision_detected(TRIG_PIN, ECHO_PIN, COLLISION_PIN, THINFILM_PIN, timestamp, mqtt);
 delay(10000);
}
