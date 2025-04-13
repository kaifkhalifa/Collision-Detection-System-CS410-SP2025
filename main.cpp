#include "cds_algo.h"
#include <Arduino.h>
#include <String>

// Replace with SSID and password of desired WiFi
#define WIFI_SSID "NETGEAR74"
#define WIFI_PASSWORD "helpfulflower781"

int ECHO_PIN = 14;
int TRIG_PIN = 13;
int COLLISION_PIN = 25;
int THINFILM_PIN = 32;

bool isConnected = false;

void setup() {
  Serial.begin(9600);

  pinMode(THINFILM_PIN, INPUT);
  pinMode(COLLISION_PIN, INPUT_PULLDOWN);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
 precollision_warning(TRIG_PIN, ECHO_PIN, COLLISION_PIN);
 collision_detected(TRIG_PIN, ECHO_PIN, COLLISION_PIN, THINFILM_PIN);
 delay(1000);
}
