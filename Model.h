#ifndef MODEL_H
#define MODEL_H
#define DEBUG
#include "Arduino.h"
#include "Const.h"
#include "Controler.h"
#include "LightSensor.h"
#include "Fuzzy.h"
#include "FuzzyRule.h"
#include "FuzzyComposition.h"
#include "FuzzyRuleConsequent.h"
#include "FuzzyOutput.h"
#include "FuzzyInput.h"
#include "FuzzyIO.h"
#include "FuzzySet.h"
#include "FuzzyRuleAntecedent.h"

class Model
{
public:
  //Model();
  void Init();
  float getCenterOfMass();
  void printSensors();
  void moveRobot();
private:
  Controler control;
  LightSensor sensors[NUMBER_OF_SENSORS];
  float centerOfMass;
  void readSensors();
  void getMinMax();  
  Fuzzy *fuzzy;
};

void Model::Init()
{
  fuzzy = new Fuzzy();
  for(int i  = 0; i < NUMBER_OF_SENSORS; i++)
  {
    sensors[i].Init(i);
  }
  getMinMax();
  Serial.println("Calibrou");
  //Criando Variavceis de Input dos Sensores
  FuzzyInput *SensorMostLeft = new FuzzyInput(1);
  FuzzyInput *SensorLeft = new FuzzyInput(2);
  FuzzyInput *SensorCenterLeft = new FuzzyInput(3);
  FuzzyInput *SensorCenterRight = new FuzzyInput(4);
  FuzzyInput *SensorRight = new FuzzyInput(5);
  FuzzyInput *SensorMostRight = new FuzzyInput(6);
  //Fuzzy Sets
  FuzzySet* Dark1 = new FuzzySet(0.0,0.0,0.2,0.8);
  FuzzySet* Bright1 = new FuzzySet(0.2,0.8,1.0,1.0);

  FuzzySet* Dark2 = new FuzzySet(0.0,0.0,0.2,0.8);
  FuzzySet* Bright2 = new FuzzySet(0.2,0.8,1.0,1.0);

  FuzzySet* Dark3 = new FuzzySet(0.0,0.0,0.2,0.8);
  FuzzySet* Bright3 = new FuzzySet(0.2,0.8,1.0,1.0);

  FuzzySet* Dark4 = new FuzzySet(0.0,0.0,0.2,0.8);
  FuzzySet* Bright4 = new FuzzySet(0.2,0.8,1.0,1.0);

  FuzzySet* Dark5 = new FuzzySet(0.0,0.0,0.2,0.8);
  FuzzySet* Bright5 = new FuzzySet(0.2,0.8,1.0,1.0);

  FuzzySet* Dark6 = new FuzzySet(0.0,0.0,0.2,0.8);
  FuzzySet* Bright6 = new FuzzySet(0.2,0.8,1.0,1.0);
  //Adding Fuzzy Sets
  SensorMostLeft->addFuzzySet(Bright1);
  SensorMostLeft->addFuzzySet(Dark1);

  SensorLeft->addFuzzySet(Bright2);
  SensorLeft->addFuzzySet(Dark2);

  SensorCenterLeft->addFuzzySet(Bright3);
  SensorCenterLeft->addFuzzySet(Dark3);

  SensorCenterRight->addFuzzySet(Bright4);
  SensorCenterRight->addFuzzySet(Dark4);

  SensorRight->addFuzzySet(Bright5);
  SensorRight->addFuzzySet(Dark5);

  SensorMostRight->addFuzzySet(Bright6);
  SensorMostRight->addFuzzySet(Dark6);

  //Add Fuzzy Inputs

  fuzzy->addFuzzyInput(SensorMostLeft);
  fuzzy->addFuzzyInput(SensorLeft);
  fuzzy->addFuzzyInput(SensorCenterLeft);
  fuzzy->addFuzzyInput(SensorCenterRight);
  fuzzy->addFuzzyInput(SensorRight);
  fuzzy->addFuzzyInput(SensorMostRight);

  //Creating Ouput
  FuzzyOutput* MotorRight = new FuzzyOutput(1);

  FuzzySet *NegativeHighRight = new FuzzySet(-1.0,-0.25,-0.25,-0.5);
  FuzzySet *NegativeLowRight = new FuzzySet(-.25,-.5,0.5,-.75);
  FuzzySet* ZeroRight = new FuzzySet(-.75,0.0,0.0,.25);
  FuzzySet *PositiveLowRight = new FuzzySet(0.0,0.25,0.25,0.5);
  FuzzySet *PositiveHighRight = new FuzzySet(.25,.5,0.5,1.0);

  MotorRight->addFuzzySet(NegativeHighRight);
  MotorRight->addFuzzySet(NegativeLowRight);
  MotorRight->addFuzzySet(ZeroRight);
  MotorRight->addFuzzySet(PositiveLowRight);
  MotorRight->addFuzzySet(PositiveHighRight);

  fuzzy->addFuzzyOutput(MotorRight);

  FuzzyOutput* MotorLeft = new FuzzyOutput(2);

  FuzzySet *NegativeHighLeft = new FuzzySet(-1.0,-0.25,-0.25,-0.5);
  FuzzySet *NegativeLowLeft = new FuzzySet(-.25,-.5,0.5,-.75);
  FuzzySet* ZeroLeft = new FuzzySet(-.75,0.0,0.0,.25);
  FuzzySet *PositiveLowLeft = new FuzzySet(0.0,0.25,0.25,0.5);
  FuzzySet *PositiveHighLeft = new FuzzySet(.25,.5,0.5,1.0);

  MotorLeft->addFuzzySet(NegativeHighLeft);
  MotorLeft->addFuzzySet(NegativeLowLeft);
  MotorLeft->addFuzzySet(ZeroLeft);
  MotorLeft->addFuzzySet(PositiveLowLeft);
  MotorLeft->addFuzzySet(PositiveHighLeft);

  fuzzy->addFuzzyOutput(MotorLeft);
  //Rules
  //if Sensor Right is Dark Cog is Positive
  FuzzyRuleAntecedent* ifSensorMostRightIsDark = new FuzzyRuleAntecedent();
  ifSensorMostRightIsDark->joinWithOR(Dark5,Dark6);
  FuzzyRuleConsequent* thenCogPositive = new FuzzyRuleConsequent();
  thenCogPositive->addOutput(PositiveHighLeft);
  thenCogPositive->addOutput(PositiveLowRight);
  FuzzyRule *fuzzyRule01 = new FuzzyRule(1,ifSensorMostRightIsDark,thenCogPositive);
  fuzzy->addFuzzyRule(fuzzyRule01);

  //if Sensors Center is Dark Cog is Zero
  FuzzyRuleAntecedent* ifSensorCenterIsDark = new FuzzyRuleAntecedent();
  ifSensorCenterIsDark->joinWithOR(Dark4,Dark3);
  FuzzyRuleConsequent* thenCogZero = new FuzzyRuleConsequent();
  thenCogZero->addOutput(PositiveHighLeft);
  thenCogZero->addOutput(PositiveHighRight);
  FuzzyRule *fuzzyRule02 = new FuzzyRule(2,ifSensorCenterIsDark,thenCogZero);
  fuzzy->addFuzzyRule(fuzzyRule02);

  //if Sensors left is Dark Cog is Negative
  FuzzyRuleAntecedent* ifSensorLeftIsDark = new FuzzyRuleAntecedent();
  ifSensorLeftIsDark->joinWithOR(Dark2,Dark1);
  FuzzyRuleConsequent* thenCogNegative = new FuzzyRuleConsequent();
  thenCogNegative->addOutput(PositiveLowRight);
  thenCogNegative->addOutput(NegativeLowLeft);
  FuzzyRule *fuzzyRule03 = new FuzzyRule(3,ifSensorLeftIsDark,thenCogNegative);
  fuzzy->addFuzzyRule(fuzzyRule03);

}

float Model::getCenterOfMass(){
  readSensors();
  for(int i = 1; i <= NUMBER_OF_SENSORS;i++)
  {
    fuzzy->setInput(i,sensors[i].getValue());
  }
  fuzzy->fuzzify();
  return fuzzy->defuzzify(1);
}

void Model::moveRobot()
{
  readSensors();
  for(int i = 1; i <= NUMBER_OF_SENSORS;i++)
  {
    fuzzy->setInput(i,sensors[i].getValue());
  }
  fuzzy->fuzzify();
  float velRight = fuzzy->defuzzify(1);
  float velLeft = fuzzy->defuzzify(2);
  Serial.print("Velocidade Direito ");
  Serial.print(velRight);
  Serial.print("Velocidade Esquerdo ");
  Serial.println(velLeft);
  control.motorRight(velRight);
  control.motorLeft(velLeft);
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
  float vel = 0.15;
  control.rotateRight(vel);
  unsigned long b = millis();
  for (int i = 0; i < 5; i++){
    do{
      for(int i = 0; i < NUMBER_OF_SENSORS;i++){
        int actualRead = analogRead(i);
        if(actualRead < sensors[i].getMin())sensors[i].setMin(actualRead);
        if(actualRead > sensors[i].getMax())sensors[i].setMax(actualRead);
      }
    }
    while(millis() - b < 300);
    b = millis();
    control.rotateLeft(vel);
    do{
      for(int i = 0; i < NUMBER_OF_SENSORS;i++){
        int actualRead = analogRead(i);
        if(actualRead < sensors[i].getMin())sensors[i].setMin(actualRead);
        if(actualRead > sensors[i].getMax())sensors[i].setMax(actualRead);
      }

    }
    while(millis() - b < 300);
    control.stopMotors();
  }
  //Retornar ao centro - Tem que melhorar isso
  control.rotateRight(vel);
  b = millis();
  do{
    readSensors();
  }
  while(sensors[3].getValue() < 0.5 || sensors[4].getValue() < 0.5  );
  control.stopMotors();
}
#endif








