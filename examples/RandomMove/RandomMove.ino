//We always have to include the library
#include "LedMatrix.h"
#include "randomMovement.h"


/*
 Now we need a LedMatrix to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn 
 pin 11 is connected to the CLK 
 pin 10 is connected to LOAD 
 We have only a single MAX72XX.
 */
LedMatrix lc(12,11,10);

randomMovement randMov(lc, A4);

void setup() {
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.wakeup();
  /* Set the brightness to a medium values */
  //lc.setIntensity(8);
  lc.setIntensity(1);
  /* and clear the display */
  lc.clear();
}


void loop() { 
  randMov.off();
  randMov.move();
  randMov.on();
  delay(150);
}
