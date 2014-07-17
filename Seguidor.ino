#include "Seguidor.h"
#include "LightSensor.h"
#include "Motor.h"
#include "Fuzzy.h"
#include "Controler.h"

Seguidor seguidor(6,6,4,5,9,10,11);
bool start = true;
int minMaxSensors[6][2] = {{54,917},{57,917},{53,938},{48,945},{81,874},{51,873}};
void setup() {
  Serial.begin(115200); // Arduino due
  //Serial.begin(9600);
  
  for(int i = 5; i >= 0; i--)
   seguidor.addSensor(i);
   
  seguidor.calibrateManual(minMaxSensors);
  Serial.println("Calibrou");
  pinMode(22,OUTPUT);
  digitalWrite(22,HIGH);
  pinMode(23,OUTPUT);
  digitalWrite(23,LOW);
}

void loop() {
  if(start)
  {
    //seguidor.warmMotors();
    start = false;
  }
    
  seguidor.moveFoward(.2);
}
