#ifndef MOTOR_H
#define MOTOR_H
#include "Arduino.h"

enum {FOWARD,BACKWARD};

class Motor
{
  public:
  Motor(int positivePin, int negativePin):positivePin(positivePin), negativePin(negativePin),minSpeed(0),maxSpeed(255)
  {
    
  };
  void rotatePwm(int pwm,int d)
  {
      if(d == FOWARD)
    {
      analogWrite(positivePin,pwm);
      analogWrite(negativePin,0);
    }
    else
    {
      analogWrite(positivePin,0);
      analogWrite(negativePin,pwm);
    }
  
  }
  void stopMotor()
  {
    analogWrite(positivePin,255);
    analogWrite(negativePin,255);
  };
  void rotate(float s, int d)
  {
    if(d == FOWARD)
    {
      analogWrite(positivePin,(maxSpeed - minSpeed) * s + minSpeed);
      analogWrite(negativePin,0);
    }
    else
    {
      analogWrite(positivePin,0);
      analogWrite(negativePin,(maxSpeed - minSpeed) * s + minSpeed);
    }
  
  };
  void setMaxSpeed(int maxS)
  {
    this->maxSpeed = maxS;
  };
  void setMinSpeed(int minS)
  {
    this->minSpeed = minS;
  };
   int minSpeed,maxSpeed;
  private:
    int positivePin, negativePin;
};

#endif
