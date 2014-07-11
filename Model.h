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
  Model();
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

Model::Model(){
  for(int i  = 0; i < NUMBER_OF_SENSORS; i++){
    sensors[i].Init(i);
  }
}
void Model::Init(){
  fuzzy = new Fuzzy();
  getMinMax();
  Serial.println("Calibrou");
  //Criando Variavceis de Input dos Sensores
  FuzzyInput* fuzzySensors[NUMBER_OF_SENSORS];
  //Fuzzy Sets
  FuzzySet* bright[NUMBER_OF_SENSORS];
  FuzzySet* dark[NUMBER_OF_SENSORS];
  //Fuzzy OutPuts
  FuzzyOutput* cog = new FuzzyOutput(3);
  FuzzySet* cogFuzzySets[NUMBER_OF_SENSORS];
  
  //Setting inputs
  for(int i = 0; i < NUMBER_OF_SENSORS; i++){
    fuzzySensors[i] = new FuzzyInput(i+1);
    
    bright[i] = new FuzzySet(-0.9,-0.1,0.1,0.9);
    dark[i] = new FuzzySet(0.1,0.9,1.1,1.9);  
    
    fuzzySensors[i]->addFuzzySet(bright[i]);
    fuzzySensors[i]->addFuzzySet(dark[i]);
    fuzzy->addFuzzyInput(fuzzySensors[i]);  
  }
  
  //Setting Ouput 
  
  cogFuzzySets[0] = new FuzzySet(-3.4,-2.6, -2.4, -1.6);
  cogFuzzySets[1] = new FuzzySet(-2.4, -1.6, -1.4, -0.6);
  cogFuzzySets[2] = new FuzzySet(-1.4, -0.6, -0.4, 0.4);
  cogFuzzySets[3] = new FuzzySet(-0.4, 0.4, 0.6, 1.4);
  cogFuzzySets[4] = new FuzzySet(0.6, 1.4, 1.6, 2.4);
  cogFuzzySets[5] = new FuzzySet(1.6, 2.4, 2.6, 3.4);
  
  for(int i = 0; i < NUMBER_OF_SENSORS; i++){
    cog->addFuzzySet(cogFuzzySets[i]);
  }
  
  fuzzy->addFuzzyOutput(cog);
  /*
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
  */
  //Rules
  //if Sensor Right is Dark Cog is Positive
  /*
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
  */

  FuzzyRuleAntecedent* antecedents[NUMBER_OF_SENSORS];
  FuzzyRuleConsequent* consequents[NUMBER_OF_SENSORS];
  FuzzyRule* rules[NUMBER_OF_SENSORS];
  
  FuzzySet* set[NUMBER_OF_SENSORS][NUMBER_OF_SENSORS] = {{dark[0],bright[1],bright[2],bright[3],bright[4],bright[5]},
                                                        {bright[0],dark[1],bright[2],bright[3],bright[4],bright[5]},
                                                        {bright[0],bright[1],dark[2],bright[3],bright[4],bright[5]},
                                                        {bright[0],bright[1],bright[2],dark[3],bright[4],bright[5]},
                                                        {bright[0],bright[1],bright[2],bright[3],dark[4],bright[5]},
                                                        {bright[0],bright[1],bright[2],bright[3],bright[4],dark[5]}};
  
  for (int i = 0;i < NUMBER_OF_SENSORS; i++){
    antecedents[i] = new FuzzyRuleAntecedent();
    antecedents[i]->joinWithAND(set[i]);
    consequents[i] = new FuzzyRuleConsequent();
    consequents[i]->addOutput(cogFuzzySets[i]);
    rules[i] = new FuzzyRule(i+1,antecedents[i],consequents[i]);
    fuzzy->addFuzzyRule(rules[i]);
  }
}
float Model::getCenterOfMass(){
  readSensors();
  for(int i = 0; i <= NUMBER_OF_SENSORS;i++){
    fuzzy->setInput(i,sensors[i].getValue());
  }
  fuzzy->fuzzify();
  return fuzzy->defuzzify(3);
}

void Model::moveRobot()
{
  readSensors();
  for(int i = 1; i <= NUMBER_OF_SENSORS;i++){
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
  //Serial.println();
}

void Model::getMinMax(){
  float vel = 0.3;
  float tempoInicial = millis();
  int delayCall = 500;
  for(int j=0;j < 5;j++){
    do{
      control.rotateRight(vel);
      for(int i = 0; i < NUMBER_OF_SENSORS;i++){
        int actualRead = analogRead(i);
        if(actualRead < sensors[i].getMin())sensors[i].setMin(actualRead);
        if(actualRead > sensors[i].getMax())sensors[i].setMax(actualRead);
      }
    #ifndef BLACK
    }while(sensors[0].getRawValue() < LIMIAR_MAIS_ESQUERDO);
    #else
    }while(sensors[0].getRawValue() > LIMIAR_MAIS_ESQUERDO);
    #endif
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
    #ifndef BLACK
    }while(sensors[NUMBER_OF_SENSORS - 1].getRawValue() < LIMIAR_MAIS_DIREITO);
    #else
    }while(sensors[NUMBER_OF_SENSORS - 1].getRawValue() > LIMIAR_MAIS_DIREITO);
    #endif
 
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
  }while(sensors[3].getValue() < 0.8);
  control.stopMotors();
}
#endif
