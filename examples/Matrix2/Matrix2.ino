#include "LedMatrix.h"

// pin 12 is connected to the DataIn 
// pin 11 is connected to the CLK 
// pin 10 is connected to LOAD 
LedMatrix matrix(12,11,10);

const uint16_t delaytime = 300;

void setup()
{
    // Set the brightness. (0..15)
    matrix.setIntensity(1);
}



void loop()
{
    matrix.fill();
    delay(delaytime);
    matrix.clear();
    delay(delaytime);
}
