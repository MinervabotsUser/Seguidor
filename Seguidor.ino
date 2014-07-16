#include "Seguidor.h"

Seguidor seguidor(6,5,6,11,10);
void setup() {
  for(int i = 0; i < 6; i++)
   seguidor.addSensor(i);
  seguidor.calibrate();
}

void loop() {
  seguidor.movePid();

}
