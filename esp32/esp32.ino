#include "cds_algo.h"


void setup() {
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
 precollision_warning();
 collision_detected();
 delay(10000);
}
