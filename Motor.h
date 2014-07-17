#ifndef MOTOR_H
#define MOTOR_H
#include "Arduino.h"

enum {FOWARD,BACKWARD};

class Motor
{
  public:
  Motor(int pwmPin, int directionPin1, int directionPin2):pwmPin(pwmPin), directionPin1(directionPin1),directionPin2(directionPin2),minSpeed(0),maxSpeed(255)
  {
    
  };
  void rotatePwm(int pwm,int d)
  {
    analogWrite(pwmPin,pwm);
      if(d == FOWARD)
    {
      digitalWrite(directionPin1,HIGH);
      digitalWrite(directionPin2,LOW);
    }
    else
    {
      digitalWrite(directionPin1,LOW);
      digitalWrite(directionPin2,HIGH);
    }
  
  }
  void setConstants(double a,double b, double c,double d)
  {
    this->a = a;
    this->b = b;
    this->c = c;
    this->d = d;
  };
  int getPwm(float s)
  {
    s = s * (maxTick-minTick) + minTick;
    return round(a*exp(b*s)+c*exp(d*s));
  };
  void setTicks(int m,int M)
  {
    minTick =m;
     maxTick =M;
  };
  void stopMotor()
  {
    digitalWrite(directionPin1,HIGH);
    digitalWrite(directionPin2,HIGH);
  };
  void rotate(float s, int d)
  {
    analogWrite(pwmPin,(maxSpeed - minSpeed) * s + minSpeed);
      if(d == FOWARD)
    {
      digitalWrite(directionPin1,HIGH);
      digitalWrite(directionPin2,LOW);
    }
    else
    {
      digitalWrite(directionPin1,LOW);
      digitalWrite(directionPin2,HIGH);
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
    int pwmPin,directionPin1,directionPin2;
    double a,b,c,d;
    int maxTick,minTick;
};

#endif
