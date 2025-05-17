#ifndef MQTT_COMM_H
#define MQTT_COMM_H

#include <ArduinoJson.h>
#include <WiFi.h>
#include <PubSubClient.h>

class MqttComm {
  public:
/**
     * @brief Constructor for MqttComm.
     * @param ssid WiFi network SSID.
     * @param password WiFi network password.
     * @param mqtt_broker MQTT broker address.
     * @param mqtt_port MQTT broker port.
     * @param mqtt_username MQTT broker username.
     * @param mqtt_password MQTT broker password.
     * @param mqtt_topic MQTT topic to publish messages to.
     */
    MqttComm(const char* ssid, const char* password, const char* mqtt_broker, const int mqtt_port, const char *mqtt_username,
            const char* mqtt_password, const char* mqtt_topic);


    /**
     * @brief Initializes WiFi and MQTT connections.
     */
    void begin();

  /**
     * @brief keeps the MQTT running.
     */
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
    /**
     * @brief Establishes a connection to the WiFi network.
     */
    void connectWiFi();

    
    /**
     * @brief Connects to the MQTT broker and subscribes.
     */
    void connectMQTT();

    /**
     * @brief Static callback function for handling incoming MQTT messages.
     * @param topic The topic the message was received on.
     * @param payload The message payload.
     * @param length The length of the message payload.
     */
    static void mqttCallback(char* topic, byte* payload, unsigned int length);
};
#endif
