#include "Model.h"
#include "Const.h"
#include "Controler.h"
#include "Fuzzy.h"
#include "FuzzyRule.h"
#include "FuzzyComposition.h"
#include "FuzzyRuleConsequent.h"
#include "FuzzyOutput.h"
#include "FuzzyInput.h"
#include "FuzzyIO.h"
#include "FuzzySet.h"
#include "FuzzyRuleAntecedent.h"
#define DEBUG

#include <SoftwareSerial.h>
// software serial #1: TX = digital pin 2, RX = digital pin 3
SoftwareSerial bluetooth(BLUETOOTH_TX, BLUETOOTH_RX);

PIDControler Pid;
Model model;
Controler controler;

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
  Pid.Init(9,4,.025);  
}
void loop(){
  model.printSensors();
  Serial.print("\t");
  Serial.println(model.getCenterOfMass());
  //model.moveRobot();
}
