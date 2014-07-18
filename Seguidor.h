#ifndef SEGUIDOR_H
#define SEGUIDOR_H

#define LIMIAR_MAIS_ESQUERDO        350
#define LIMIAR_ESQUERDO             800
#define LIMIAR_MENOS_ESQUERDO       600
#define LIMIAR_MENOS_DIREITO        750
#define LIMIAR_DIREITO              900
#define LIMIAR_MAIS_DIREITO         900
#define R  0.015
#define L  0.085;

#include "Arduino.h"
#include "LightSensor.h"
#include "Motor.h"
#include "Fuzzy.h"
#include "Controler.h"
#include "IMU.h"
#include <Wire.h>
#include <Adafruit_BMP085_U.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_10DOF.h>
#include "KalmanFilter.h"

class Seguidor
{
  public:
    Seguidor(int numberOfSensors, int MotorLeft, int dir1Left1, int dir1Left2, int MotorRight, int dir1Right1, int dir1Right2)
    {
      Serial.print("Seguidor Ok");
      activeSensors = 0;
      rightMotor = new Motor(MotorRight, dir1Right1, dir1Right2);
      rightMotor->setConstants(1.375e4, 0.0003937, -1.815e4, -0.01682);
      rightMotor->setTicks(6580, 14759);
      leftMotor = new Motor(MotorLeft, dir1Left1, dir1Left2);
      leftMotor->setConstants(1.34e4, 0.0005189, -1.79e4, -0.01754);
      leftMotor->setTicks(6402, 14876);
      pid = new PIDControler(9, 4, .025);
      //KalmanPosition = new KalmanFilterPosicao(.1, .1);
      //KalmanRotation = new KalmanFilterRotation(1000, .1, .1, 0);

    };
    void addSensor(int pin)
    {
      lightSensors[activeSensors] = new LightSensor(pin);
      activeSensors++;
    };
    void calibrateManual(int minMax[6][2]) {
      for (int i = 0; i < activeSensors; i++) {
        lightSensors[i]->setMin(minMax[i][0]);
        lightSensors[i]->setMax(minMax[i][1]);
      }
    };
    void warmMotors()
    {
      delay(100);
      rightMotor->rotatePwm(100, FOWARD);
      leftMotor->rotatePwm(100, FOWARD);
      delay(5);

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
    void setMinSpeed(int s)
    {
      rightMotor->setMinSpeed(s);
      leftMotor->setMinSpeed(s);
    };
    void stopMotors()
    {
      rightMotor->stopMotor();
      leftMotor->stopMotor();
      velocity.reset();
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

      Serial.print("Cog: ");
      Serial.print(cog);
      Serial.print("\tOutput: ");
      Serial.println(output);
      /*
      if (cog < 0) {
        if ((rightMotor->maxSpeed + output) > 0) {
          rightMotor->rotatePwm(rightMotor->maxSpeed + output , FOWARD);
        }else {
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
      */
    };
    float getVelocity()
    {
      return(velocity.integrate(imu.getAceleration()));
    };
    float getOmega()
    {
//      KalmanRotation->Update();
//      float theta = imu.getHeading();
      float omega = imu.getOmega();
//      KalmanRotation->Predict(theta,omega);
      return omega;
    };
    float getRightSpeed()
    {
      return this->velocity.getValue()/R + this->getOmega() * 0.5 * R/L;
    };
    float getLeftSpeed()
    {
      float vr = getRightSpeed();
      return ((2 * velocity.getValue() / R) - vr);
    };
  private:
    LightSensor  *lightSensors[6];
    Integrator velocity;
    Motor *rightMotor;
    Motor *leftMotor;
//    KalmanFilterRotation *KalmanRotation;
//    KalmanFilterPosicao *KalmanPosition;
    int activeSensors;
    Fuzzy fuzzy;
    float initialHeading();
    IMU imu;
    PIDControler *pid;

};

#endif
