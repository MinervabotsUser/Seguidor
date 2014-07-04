#ifndef LIGHT_SENSOR_H
#define LIGHT_SENSOR_H
#include "Arduino.h"
class LightSensor
{
  public:
    void Init(unsigned short port, float weight);
    float getValue();
    void setMin(unsigned m);
    void setMax(unsigned m);
    unsigned getMin(){return minRead;};
    unsigned getMax(){return maxRead;};
    float getWeight();
    int getRawValue();
  private:
    unsigned short port;
    unsigned minRead;
    unsigned maxRead;
    float weight;
    float value;
};

void LightSensor::Init(unsigned short port,float weight)
{
  this->port = port;
  Serial.print("===");
  Serial.print(weight);
  Serial.println("===");
  this->weight = weight;
  minRead = 1024;
  maxRead = 0;
}
void LightSensor::setMin(unsigned m)
{
  minRead = m;
}
void LightSensor::setMax(unsigned m)
{
  maxRead = m;
}
float LightSensor::getWeight(){
  return weight;
}
int LightSensor::getRawValue()
{
  return analogRead(port);
}

float LightSensor::getValue()
{
  value = analogRead(port);
  value = (value - minRead) * 1000.0 / (maxRead - minRead); 
  if(value > 700){
    value = 1;
  }else{
    value = 0;
  }
  
  return weight * value;
}

#endif
