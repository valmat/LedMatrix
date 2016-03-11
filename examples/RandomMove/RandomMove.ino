#include "LedMatrix.h"
#include "randomMovement.h"

// A single display
// pin 11 is connected to the DataIn
// pin 13 is connected to the CLK
// pin 10 is connected to LOAD (cs)
LedMatrix matrix(11, 13, 10);

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
