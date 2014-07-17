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
    Seguidor(int numberOfSensors, int MotorLeft, int dir1Left1, int dir1Left2, int MotorRight, int dir1Right1, int dir1Right2)
    {

      activeSensors = 0;
      rightMotor = new Motor(MotorRight, dir1Right1, dir1Right2);
      leftMotor = new Motor(MotorLeft, dir1Left1, dir1Left2);
      pid = new PIDControler(9, 4, .025);
    };
    void addSensor(int pin)
    {
      lightSensors[activeSensors] = new LightSensor(pin);
      activeSensors++;
    };
    void calibrate()
    {
      unsigned long initTime = micros();
      unsigned long dt = .5;
      for (int i = 0; i < 5;)
      {
        Serial.print("Calibrating ");
        Serial.println(i);
        if (abs(micros() - initTime) * 0.000001 < dt)
          rotateRight(.5);
        else if (abs(micros() - initTime) * 0.000001 < 2 * dt)
          rotateLeft(.5);
        Serial.println(abs(micros() - initTime) * 0.000001);
        for (int j = 0; j < activeSensors; j++)
        {
          lightSensors[j]->setMin(min(lightSensors[j]->getValue(), lightSensors[j]->getMin()));
          lightSensors[j]->setMax(max(lightSensors[j]->getValue(), lightSensors[j]->getMax()));
        }
        if (abs(micros() - initTime) * 0.000001 > 2 * dt)
        {
          initTime = micros();
          i++;
        }
      }
    };
    void setMaxSpeed(int s)
    {
      rightMotor->setMaxSpeed(s);
      leftMotor->setMaxSpeed(s);
    };
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
    LightSensor  *lightSensors[6];
    Motor *rightMotor;
    Motor *leftMotor;
    int activeSensors;
    Fuzzy fuzzy;
    PIDControler *pid;
};

#endif
