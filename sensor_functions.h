#ifndef SENSOR_FUNCTIONS_H
#define SENSOR_FUNCTIONS_H

double read_ultrasonic_sns(int trigPin, int echoPin); 
int read_collision_sns(int pin);
double get_thinfilm_data(int pin);

#endif