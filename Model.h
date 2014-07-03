#ifndef MODEL_H
#define MODEL_H
#define DEBUG
#include "Arduino.h"
#include "Const.h"
#include "Controler.h"
#include "LightSensor.h"

class Model
{
public:
  //Model();
  void Init();
  float getCenterOfMass();
  void printSensors();
private:
  Controler control;
  LightSensor sensors[NUMBER_OF_SENSORS];
  float centerOfMass;
  void readSensors();
  void getMinMax();  
};

void Model::Init()
{
  for(int i  = 0; i < NUMBER_OF_SENSORS; i++)
  {
    sensors[i].Init(i);
  }
  getMinMax();
}

float Model::getCenterOfMass(){
  return centerOfMass;
}

void Model::readSensors(){
  for(int i = 0;i < NUMBER_OF_SENSORS;i++){
    sensors[i].getValue();
  }
}

void Model::printSensors(){
  for(int i = 0;i < NUMBER_OF_SENSORS;i++){
    Serial.print(sensors[i].getValue());
    Serial.print("\t");
  }
  Serial.println();
}

void Model::getMinMax(){
  float vel = 1;
  float tempoInicial = millis();
  int delayCall = 100;
  for(int j=0;j < 5;j++){
    do{
      control.rotateRight(vel);
      for(int i = 0; i < NUMBER_OF_SENSORS;i++){
        int actualRead = analogRead(i);
        if(actualRead < sensors[i].getMin())sensors[i].setMin(actualRead);
        if(actualRead > sensors[i].getMax())sensors[i].setMax(actualRead);
      }
    }while(sensors[0].getRawValue() < LIMIAR_MAIS_ESQUERDO);
    
    tempoInicial = millis();
    do{
      for(int i = 0; i < NUMBER_OF_SENSORS;i++){
        int actualRead = analogRead(i);
        if(actualRead < sensors[i].getMin())sensors[i].setMin(actualRead);
        if(actualRead > sensors[i].getMax())sensors[i].setMax(actualRead);
      }
    }while(millis() - tempoInicial < delayCall);   
   
    control.rotateLeft(vel);
    do{
      for(int i = 0; i < NUMBER_OF_SENSORS;i++){
        int actualRead = analogRead(i);
        if(actualRead < sensors[i].getMin())sensors[i].setMin(actualRead);
        if(actualRead > sensors[i].getMax())sensors[i].setMax(actualRead);
      }
    }while(sensors[NUMBER_OF_SENSORS - 1].getRawValue() < LIMIAR_MAIS_DIREITO);
    
    tempoInicial = millis();
    do{
      for(int i = 0; i < NUMBER_OF_SENSORS;i++){
        int actualRead = analogRead(i);
        if(actualRead < sensors[i].getMin())sensors[i].setMin(actualRead);
        if(actualRead > sensors[i].getMax())sensors[i].setMax(actualRead);
      }
    }while(millis() - tempoInicial < delayCall);
    
  }
  control.stopMotors();
  // Retornar ao centro - Tem que melhorar isso
  control.rotateRight(vel);
  do{
    readSensors();
    Serial.println(sensors[3].getRawValue());
  }while(sensors[3].getRawValue() < 750);
  control.stopMotors();
}
#endif












