#include "sensor_functions.h"
#include "SensorOutput.h"
#include <Arduino.h>

double read_ultrasonic_sns(int trigPin, int echoPin) {
    return 5;
    //SendDistanceSensorData(trigPin, echoPin);
}

int read_collision_sns(int pin) {
    return 0;
    //SendCollisionSensorData(pin);
}

double get_thinfilm_data(int pin) {
    return 80;
    //SendPressureSensorData(pin);
}