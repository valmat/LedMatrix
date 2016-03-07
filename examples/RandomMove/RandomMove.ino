#include "LedMatrix.h"
#include "randomMovement.h"

// A single display
// pin 12 is connected to the DataIn 
// pin 11 is connected to the CLK 
// pin 10 is connected to LOAD 
LedMatrix matrix(12,11,10);

randomMovement randMov(matrix, A4);

void setup()
{
    // Set the brightness. (0..15)
    matrix.setIntensity(1);
}

void loop()
{
    randMov.off();
    randMov.move();
    randMov.on();
    delay(150);
}
