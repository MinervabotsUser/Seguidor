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

#endif



