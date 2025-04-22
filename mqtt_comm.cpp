/*
================================
Filename: mqtt_comm.cpp
Author: Emry Hankins
Description: Creates a class that connects the exp32 to a mqtt broker
================================
*/


#include <Arduino.h>
#include <ArduinoJson.h> 
#include "mqtt_comm.h"


MqttComm::MqttComm(const char* ssid, const char* password,
                   const char* mqtt_broker, const int mqtt_port,
                   const char* mqtt_username, const char* mqtt_password,
                   const char* mqtt_topic)
    : _ssid(ssid), _password(password),
      _mqtt_broker(mqtt_broker), _mqtt_port(mqtt_port),
      _mqtt_username(mqtt_username), _mqtt_password(mqtt_password),
      _mqtt_topic(mqtt_topic), _mqttClient(_wifiClient) {}


void MqttComm::begin() {
    connectWiFi();
    _mqttClient.setServer(_mqtt_broker, _mqtt_port);
    _mqttClient.setCallback(MqttComm::mqttCallback);
}

void MqttComm::loop() {
    if (!_mqttClient.connected()) {
        connectMQTT();
    }
    _mqttClient.loop();
}

void MqttComm::publish(String jsonPayload) {
  if (!_mqttClient.connected()) {
    connectMQTT();  
  }

  // Publish to the MQTT topic
  _mqttClient.publish(_mqtt_topic, jsonPayload.c_str());

  Serial.print("Published message: ");
  Serial.println(jsonPayload);
}

void MqttComm::connectWiFi() {
  delay(10);
    Serial.print("Connecting to WiFi: ");
    Serial.println(_ssid);

    WiFi.begin(_ssid, _password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Connected to WiFi");
}


void MqttComm::connectMQTT() {
 while (!_mqttClient.connected()) {
        Serial.print("Attempting MQTT connection...");

        if (_mqttClient.connect("ESP32", _mqtt_username, _mqtt_password)) {
            Serial.println("connected");
            _mqttClient.subscribe(_mqtt_topic);
        } else {
            Serial.print("failed, rc=");
            Serial.print(_mqttClient.state());
            delay(5000);
        }
  }
}

void MqttComm::mqttCallback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message arrived: ");
    Serial.print(topic);
    Serial.print(" - ");
    for (int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);
    }
    Serial.println();
}



