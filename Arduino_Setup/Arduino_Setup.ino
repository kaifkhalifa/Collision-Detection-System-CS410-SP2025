#include <IRremote.hpp>
#include <WiFi.h>

#define WIFI_SSID "WiFi_name"
#define WIFI_PASSWORD "password"

bool isConnected = false;

void setup() { 
  Serial.begin(9600);

  // Begin WiFi connection
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
}

void loop() {
  // If the WiFi is connected, this will only run once
  if (WiFi.status() == WL_CONNECTED && !isConnected) {
    Serial.println("Connected");
    digitalWrite(LED_BUILTIN, HIGH);
    isConnected = true;
  }

  // If the WiFi is ever not connected
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println(".");
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    delay(1000);
    isConnected = false;
  }

}