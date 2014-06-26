#ifndef MODEL_H
#define MODEL_H
#define DEBUG
#include "Arduino.h"
#include "Const.h"
#include "Controler.h"

class Model
{
public:
  //Model();
  void Init();
  float getCenterOfMass();
  void printSensors();
private:
  Controler control;
  float sensors[NUMBER_OF_SENSORS];
  float classSensors[NUMBER_OF_SENSORS][2];
  float weigth[3];
  float minMaxSensors[NUMBER_OF_SENSORS][2];
  float centerOfMass;

  void readSensors();
  void getMinMax();  
};

void Model::Init()
{
  for( int i = 0; i < NUMBER_OF_SENSORS; i++)
  {
    minMaxSensors[i][0] = 1024;
    minMaxSensors[i][1] = 0;
  }
  getMinMax();
}

float Model::getCenterOfMass(){
  return centerOfMass;
}

void Model::readSensors(){
  for(int i = 0;i < NUMBER_OF_SENSORS;i++){
    sensors[i] = map(analogRead(i),minMaxSensors[i][0],minMaxSensors[i][1],0,1000);
  }
}

void Model::printSensors(){
  readSensors();
  for(int i = 0;i < NUMBER_OF_SENSORS;i++){
    Serial.print(sensors[i]);
    Serial.print("\t");
  }
  Serial.println();
}

void Model::getMinMax(){
  float vel = 0.6;
   control.rotateRight(vel);
  do{
    for(int i = 0; i < NUMBER_OF_SENSORS;i++){
      sensors[i] = analogRead(i);
      if(sensors[i] < minMaxSensors[i][0]) minMaxSensors[i][0] = sensors[i];
      if(sensors[i] > minMaxSensors[i][1]) minMaxSensors[i][1] = sensors[i];
    }
  }while(sensors[0] < 850);
  
  control.rotateLeft(vel);
  do{
    for(int i = 0; i < NUMBER_OF_SENSORS;i++){
      sensors[i] = analogRead(i);
      if(sensors[i] < minMaxSensors[i][0]) minMaxSensors[i][0] = sensors[i];
      if(sensors[i] > minMaxSensors[i][1]) minMaxSensors[i][1] = sensors[i];
    }

  }while(sensors[NUMBER_OF_SENSORS - 1] < 970);
  control.stopMotors();
  // Retornar ao centro - Tem que melhorar isso
  control.rotateRight(vel);
  do{
    readSensors();
  }while(sensors[3] < 600);
  control.stopMotors();
}
#endif







