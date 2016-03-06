//We always have to include the library
#include "MatrixCascade.h"
#include "randomMovement.h"


/*
 Now we need a LedMatrix to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn 
 pin 11 is connected to the CLK 
 pin 10 is connected to LOAD 
 We have only a single MAX72XX.
 */
const uint8_t matrixCount = 3;

MatrixCascade<matrixCount> lc(12, 11, 10);
randomMovement<matrixCount> randMov(lc, A4);


void setup() {
    int devices = lc.size();

    //we have to init all devices in a loop
    for(int i=0; i < devices; i++) {
        //  Set the brightness to a medium values
        lc[i].setIntensity(1);
    }
    lc[0].setRotation(3);
    lc[1].setRotation(1);
    lc[2].setRotation(1);
}


void loop() { 
    randMov.off();
    randMov.move();
    randMov.on();
    delay(50);
}
