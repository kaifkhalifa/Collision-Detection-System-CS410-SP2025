#ifndef MQTT_COMM_H
#define MQTT_COMM_H

#include <ArduinoJson.h>
#include <WiFi.h>
#include <PubSubClient.h>

class MqttComm {
  public:
    MqttComm(const char* ssid, const char* password, const char* mqtt_broker, const int mqtt_port, const char *mqtt_username,
            const char* mqtt_password, const char* mqtt_topic);
    void begin();
    void loop();
    void publish(String jsonPayload);
  
  private:
    const char* _ssid;
    const char* _password;
    const char* _mqtt_broker;
    const int _mqtt_port;
    const char* _mqtt_username;
    const char* _mqtt_password;
    const char* _mqtt_topic;

    WiFiClient _wifiClient;
    PubSubClient _mqttClient;

    void connectWiFi();
    void connectMQTT();
    static void mqttCallback(char* topic, byte* payload, unsigned int length);
};
#endif