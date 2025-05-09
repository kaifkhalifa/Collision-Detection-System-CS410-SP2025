#ifndef SENSOR_FUNCTIONS_H
#define SENSOR_FUNCTIONS_H

/**
  * @brief Read ultrasonic sensor data
  * @param trigPin Pin number for trig pin
  * @param echoPin Pin number for echo pin
  * @return Distance in cm as a double
  */
double read_ultrasonic_sns(int trigPin, int echoPin); 

/**
  * @brief Read collision sensor data
  * @param pin Pin number for collision pin
  * @return 0 if collision detected and 1 otherwise
  */
int read_collision_sns(int pin);

/**
  * @brief Read thin film sensor data
  * @param pin Pin number for collision pin
  * @return Read pressure value as an int
  */
double get_thinfilm_data(int pin);

#endif
