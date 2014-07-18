

#include <Wire.h>
#include <Adafruit_BMP085_U.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_10DOF.h>

#include "Seguidor.h"
#include "LightSensor.h"
#include "Motor.h"
#include "Fuzzy.h"
#include "Controler.h"
#include "IMU.h"

//Seguidor seguidor(6, 6, 4, 5, 9, 10, 11);
bool start = true;
IMU *imu;
int minMaxSensors[6][2] = {{54, 917}, {57, 917}, {53, 938}, {48, 945}, {81, 874}, {51, 873}};
void setup() {
  Serial.begin(9600); // Arduino due
  //Serial.begin(9600);

  // for (int i = 5; i >= 0; i--)
  // seguidor.addSensor(i);

  // seguidor.calibrateManual(minMaxSensors);

  Serial.println("Calibrou");
  pinMode(22, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(24, OUTPUT);
  pinMode(20,INPUT);
  pinMode(21,INPUT);
  pinMode(25, OUTPUT);
  digitalWrite(24, LOW);
  digitalWrite(25, HIGH);
  imu = new IMU();
  //delay(1000);
}
int i = 0;
void loop() {
  //  if (start)
  //  {
  //    //seguidor.warmMotors();
  //    start = false;
  //  }

  //seguidor.moveFoward(1);
  //Serial.println(seguidor.getVelocity());
  Serial.println(imu->getAceleration());
}
