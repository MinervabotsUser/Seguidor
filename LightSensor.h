#ifndef LIGHT_SENSOR_H
#define LIGHT_SENSOR_H
#include "Arduino.h"
class LightSensor
{
  public:
  void Init(unsigned short port);
  float getValue();
  void setMin(unsigned m);
  void setMax(unsigned m);
  unsigned getMin(){return minRead;};
  unsigned getMax(){return maxRead;};
  void setWeight(float w);
  int getRawValue();
  private:
  unsigned short port;
  unsigned minRead;
  unsigned maxRead;
  float weight;
  float value;
};
void LightSensor::Init(unsigned short port)
{
  this->port = port;
  minRead = 1024;
  maxRead = 0;
  weight = 1.0;
}
void LightSensor::setMin(unsigned m)
{
  minRead = m;
}
void LightSensor::setMax(unsigned m)
{
  maxRead = m;
}
void LightSensor::setWeight(float w)
{
  weight = w;
}
int LightSensor::getRawValue()
{
  return analogRead(port);
}

float LightSensor::getValue()
{
  value = analogRead(port);
  value = (value - minRead) / (maxRead - minRead);
  return value;
}

#endif
