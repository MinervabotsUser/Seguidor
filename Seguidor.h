#ifndef SEGUIDOR_H
#define SEGUIDOR_H

#define LIMIAR_MAIS_ESQUERDO        350
#define LIMIAR_ESQUERDO             800
#define LIMIAR_MENOS_ESQUERDO       600
#define LIMIAR_MENOS_DIREITO        750
#define LIMIAR_DIREITO              900
#define LIMIAR_MAIS_DIREITO         900

#include "Arduino.h"
#include "LightSensor.h"
#include "Motor.h"
#include "Fuzzy.h"
#include "Controler.h"
class Seguidor
{
  public:
    Seguidor(int numberOfSensors, int MotorLeft, int GroundLeft, int MotorRight, int GroundRight)
    {
      
      activeSensors = 0;
      rightMotor = new Motor(MotorRight, GroundRight);
      leftMotor = new Motor(MotorLeft, GroundLeft);
      pid = new PIDControler(9, 4, .025);
    };
    void addSensor(int pin)
    {
      lightSensors[activeSensors] = new LightSensor(pin);
      activeSensors++;
    };
    void calibrate()
    {
      float vel = 1;
      float tempoInicial = millis();
      int delayCall = 500;
      for (int j = 0; j < 5; j++) {
        do {
          rotateRight(vel);
          for (int i = 0; i < activeSensors; i++) {
            int actualRead = analogRead(i);
            if (actualRead < lightSensors[i]->getMin())lightSensors[i]->setMin(actualRead);
            if (actualRead > lightSensors[i]->getMax())lightSensors[i]->setMax(actualRead);
          }
        #ifndef BLACK
        } while (lightSensors[0]->getRawValue() < LIMIAR_MAIS_ESQUERDO);
        #else
        } while (lightSensors[0]->getRawValue() > LIMIAR_MAIS_ESQUERDO);
        #endif
        tempoInicial = millis();
        do {
          for (int i = 0; i < activeSensors; i++) {
            int actualRead = analogRead(i);
            if (actualRead < lightSensors[i]->getMin())lightSensors[i]->setMin(actualRead);
            if (actualRead > lightSensors[i]->getMax())lightSensors[i]->setMax(actualRead);
          }
        } while (millis() - tempoInicial < delayCall);

        rotateLeft(vel);
        do {
          for (int i = 0; i < activeSensors; i++) {
            int actualRead = analogRead(i);
            if (actualRead < lightSensors[i]->getMin())lightSensors[i]->setMin(actualRead);
            if (actualRead > lightSensors[i]->getMax())lightSensors[i]->setMax(actualRead);
          }
        #ifndef BLACK
        } while (lightSensors[activeSensors - 1]->getRawValue() < LIMIAR_MAIS_DIREITO);
        #else
        } while (lightSensors[activeSensors - 1]->getRawValue() > LIMIAR_MAIS_DIREITO);
      #endif

        tempoInicial = millis();
        do {
          for (int i = 0; i < activeSensors; i++) {
            int actualRead = analogRead(i);
            if (actualRead < lightSensors[i]->getMin())lightSensors[i]->setMin(actualRead);
            if (actualRead > lightSensors[i]->getMax())lightSensors[i]->setMax(actualRead);
          }
        } while (millis() - tempoInicial < delayCall);

      }
      stopMotors();
      // Retornar ao centro - Tem que melhorar isso
      rotateRight(vel);
      while (lightSensors[3]->getValue() < 0.8){};
      stopMotors();
    }
    void stopMotors()
    {
      rightMotor->stopMotor();
      leftMotor->stopMotor();
    }
    void moveFoward(float s)
    {
      rightMotor->rotate(s, FOWARD);
      leftMotor->rotate(s, FOWARD);
    };
    void rotateRight(float s)
    {
      rightMotor->rotate(s, FOWARD);
      leftMotor->rotate(s, BACKWARD);
    };
    void rotateLeft(float s)
    {
      rightMotor->rotate(s, BACKWARD);
      leftMotor->rotate(s, FOWARD);
    };
    void moveDiferential(float sRight, float sLeft)
    {
      rightMotor->rotate(sRight, FOWARD);
      leftMotor->rotate(sLeft, FOWARD);
    };
    void moveFuzzy()
    {
      float inputs[activeSensors];
      for (int i = 0; i < activeSensors; i++)
        inputs[i] = lightSensors[i]->getValue();

      fuzzy.setFuzzyOutputs(inputs);

      rightMotor->rotate(fuzzy.getMotorRightSpeed(), FOWARD);
      leftMotor->rotate(fuzzy.getMotorLeftSpeed(), FOWARD);
    };
    void movePid()
    {
      float inputs[activeSensors];
      float cog;
      for (int i = 0; i < activeSensors; i++)
        inputs[i] = lightSensors[i]->getValue();

      fuzzy.setFuzzyOutputs(inputs);

      cog = fuzzy.getCog();

      float output = pid->Run(cog);

      if (cog < 0) {
        if ((rightMotor->maxSpeed + output) > 0) {
          rightMotor->rotatePwm(rightMotor->maxSpeed + output , FOWARD);
        } else {
          rightMotor->rotatePwm(abs(rightMotor->maxSpeed + output) , BACKWARD);
        }
      }
      //Curva Pra Direita
      else if (cog > 0) {
        if (leftMotor->maxSpeed - output > 0) {
          leftMotor->rotatePwm(leftMotor->maxSpeed - output , FOWARD);
        } else {
          leftMotor->rotatePwm(abs(leftMotor->maxSpeed - output), BACKWARD);
        }
        rightMotor->rotatePwm(rightMotor->maxSpeed, FOWARD);
      }
      else if ((cog == 0)) {
        rightMotor->rotate(1.0, FOWARD);
        leftMotor->rotate(1.0, FOWARD);
      }

    };
  private:
    LightSensor  **lightSensors;
    Motor *rightMotor;
    Motor *leftMotor;
    int activeSensors;
    Fuzzy fuzzy;
    PIDControler *pid;
};

#endif
