#include "Model.h"
#include "Const.h"
#include "Conteoler.h"
#include "Fuzzy.h"
#define DEBUG

#include <SoftwareSerial.h>
// software serial #1: TX = digital pin 2, RX = digital pin 3
SoftwareSerial bluetooth(BLUETOOTH_TX, BLUETOOTH_RX);

Model model;

void setup(){
  #ifdef DEBUG
  Serial.begin(9600);
  bluetooth.begin(9600);
  #endif
  analogWrite(MOTOR_ESQUERDO, 255);
  analogWrite(TERRA_ESQUERDO, 255);
  analogWrite(MOTOR_DIREITO, 255);
  analogWrite(TERRA_DIREITO, 255);
  model.Init();
}
void loop(){
  model.printSensors();
}
