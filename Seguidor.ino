#include "Seguidor.h"

Seguidor seguidor(6,6,4,5,9,10,11);
void setup() {
  Serial.begin(9600);
  
  for(int i = 0; i < 6; i++)
   seguidor.addSensor(i);
   
  
  seguidor.setMaxSpeed(70);
  seguidor.calibrate();
  Serial.println("Calibrou");
  
}

void loop() {
  seguidor.moveFuzzy();

}
