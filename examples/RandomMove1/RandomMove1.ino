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
    Serial.begin(9600);
    Serial.print( "setup: " );
    Serial.println( lc[1].getIndex() );

    int devices = lc.size();

    //we have to init all devices in a loop
    for(int i=0; i < devices; i++) {
        
        Serial.print( "I: " );
        Serial.print( i );
        Serial.print( "\t" );
        Serial.println( lc[i].getIndex() );

        //  Set the brightness to a medium values
        lc[i].setIntensity(1);

        Serial.println( "^" );
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

    Serial.print( "loop: " );
    Serial.println( lc[1].getIndex() );
}
