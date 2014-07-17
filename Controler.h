#ifndef CONTROL_H
#define CONTROL_H
#include "Arduino.h"

class PIDControler
{
public:
  PIDControler(float Kp, float Kd, float Ki);
  float Run(float error);
  //float Run(float sensorReads, float expected);
private:
  float p;
  float d, i;
  float integral, derivative, proportional;
  float lastError;
  unsigned long lastRun;
};

PIDControler::PIDControler(float Kp, float Kd, float Ki)
{
  this->p = Kp;
  this->d = Kd;
  this->i = Ki;
  lastRun = micros();
}

float PIDControler::Run(float error)
{
  float dt = (micros () - lastRun) * .000001;
  lastRun = micros();
  integral += i * error * dt ;
  derivative = d * (error - lastError) / dt;
  lastError = error;
  proportional = p * error;
  return integral + proportional + derivative;
}
#endif




