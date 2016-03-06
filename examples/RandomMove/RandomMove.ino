//We always have to include the library
#include "LedMatrix.h"
#include "randomMovement.h"

// A single display
// pin 12 is connected to the DataIn 
// pin 11 is connected to the CLK 
// pin 10 is connected to LOAD 
LedMatrix lc(12,11,10);

randomMovement randMov(lc, A4);

void setup() {

  // Set the brightness to a medium values
  //lc.setIntensity(8);
  lc.setIntensity(1);
}


void loop() { 
  randMov.off();
  randMov.move();
  randMov.on();
  delay(150);
}
