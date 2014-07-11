#include "Model.h"
#include "Const.h"

#define DEBUG
#define BLACK

#include <SoftwareSerial.h>
// software serial #1: TX = digital pin 2, RX = digital pin 3
SoftwareSerial bluetooth(BLUETOOTH_TX, BLUETOOTH_RX);

Model model;
PIDControler pid;
int Massa = 0;
double CentroDeMassa = 0;

void setup(){
  #ifdef DEBUG
  Serial.begin(9600);
  bluetooth.begin(9600);
  #endif
  analogWrite(MOTOR_ESQUERDO,255);
  analogWrite(TERRA_ESQUERDO,255);
  analogWrite(MOTOR_DIREITO,255);
  analogWrite(TERRA_DIREITO,255);
  model.Init();
  pid.Init(kp,ki,kd);
}

void loop(){
  model.printSensors();
  
  float centerOfMass = model.getCenterOfMass();
  float output = pid.run(centerOfMass);
  model.printSensors();
  //Curva Pra Esquerda
  if(centerOfMass < 0){
      if((MAX_SPEED + output) > 0){
        analogWrite(MOTOR_DIREITO,MAX_SPEED + output);
        analogWrite(TERRA_DIREITO,0);     
      }else{
        analogWrite(MOTOR_DIREITO,0);
        analogWrite(TERRA_DIREITO,abs(MAX_SPEED + output));
      }
   }
   //Curva Pra Direita
   else if (centerOfMass > 0){
      if(MAX_SPEED - output > 0){
        analogWrite(MOTOR_ESQUERDO,MAX_SPEED - output);
        analogWrite(TERRA_ESQUERDO,0);
      }else{
        analogWrite(MOTOR_ESQUERDO,0);
        analogWrite(TERRA_ESQUERDO,abs(MAX_SPEED - output));
      }
      analogWrite(MOTOR_DIREITO,MAX_SPEED);
      analogWrite(TERRA_DIREITO,0);
   }
   else if((centerOfMass == 0)){
     analogWrite(MOTOR_ESQUERDO,MAX_SPEED);
     analogWrite(TERRA_ESQUERDO,0);
     analogWrite(MOTOR_DIREITO,MAX_SPEED);
     analogWrite(TERRA_DIREITO,0);
   }
}
