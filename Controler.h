#ifndef CONTROL_H
#define CONTROL_H

#include "Const.h"

class Controler
{
  public:
    void rotateLeft(float vel);
    void rotateRight(float vel);
    void stopMotors();
};

class PIDControler
{
  public:
    void Init(float Kp, float Kd, float Ki);
    float Run(float error);
    //float Run(float sensorReads, float expected);
  private:
    float p;
    float d, i;
    float integral, derivative, proportional;
    float lastError;
    unsigned long lastRun;
};
void Controler::rotateLeft(float vel)
{
  analogWrite(MOTOR_ESQUERDO, MAX_SPEED * vel);
  analogWrite(TERRA_ESQUERDO, 0);
  analogWrite(MOTOR_DIREITO, 0);
  analogWrite(TERRA_DIREITO, MAX_SPEED * vel);
}

void Controler::rotateRight(float vel)
{
  analogWrite(MOTOR_ESQUERDO, 0);
  analogWrite(TERRA_ESQUERDO, MAX_SPEED * vel);
  analogWrite(MOTOR_DIREITO, MAX_SPEED * vel);
  analogWrite(TERRA_DIREITO, 0);
}

void Controler::stopMotors()
{
  analogWrite(MOTOR_ESQUERDO, 255);
  analogWrite(TERRA_ESQUERDO, 255);
  analogWrite(MOTOR_DIREITO, 255);
  analogWrite(TERRA_DIREITO, 255);
}
void PIDControler::Init(float Kp, float Kd, float Ki)
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



