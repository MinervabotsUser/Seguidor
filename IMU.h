#ifndef IMU_H
#define IMU_H
#include <Wire.h>
#include <Adafruit_BMP085_U.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_10DOF.h>
#include "Arduino.h"
class IMU
{
  public:
    IMU()
    {
      Serial.println("1");

      mag = new Adafruit_LSM303_Mag_Unified(30302);
      accel = new Adafruit_LSM303_Accel_Unified(30301);
      gyro = new Adafruit_L3GD20_Unified(20);
      dof = new  Adafruit_10DOF();
      Serial.println("1");

      Serial.println("1");
      if (!accel->begin())
      {
        /* There was a problem detecting the ADXL345 ... check your connections */
        Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
        while (1);
      }
      Serial.println(1);
      if (!mag->begin())
      {
        /* There was a problem detecting the LSM303 ... check your connections */
        Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
        while (1);
      }
      Serial.println(1);
      if (!gyro->begin())
      {
        /* There was a problem detecting the L3GD20 ... check your connections */
        Serial.print("Ooops, no L3GD20 detected ... Check your wiring or I2C ADDR!");
        while (1);
      }
      Serial.println(1);
    };
    float getHeading()
    {
      sensors_event_t mag_event;
      sensors_event_t accel_event;
      sensors_vec_t   orientation;
      mag->getEvent(&mag_event);
      accel->getEvent(&accel_event);
      dof->fusionGetOrientation(&accel_event, &mag_event, &orientation);
      return orientation.heading;
    };
    float getAceleration()
    {
      sensors_event_t event;
      accel->getEvent(&event);
      Serial.println(event.acceleration.x);
      return event.acceleration.x;
    };
    float getOmega()
    {
      sensors_event_t event;
      gyro->getEvent(&event);
      return event.gyro.y;
    };
  private:
    Adafruit_10DOF                *dof;
    Adafruit_LSM303_Mag_Unified   *mag;
    Adafruit_LSM303_Accel_Unified *accel;
    Adafruit_L3GD20_Unified       *gyro;

};
#endif
