#include "LedMatrix.h"

// pin 11 is connected to the DataIn
// pin 13 is connected to the CLK
// pin 10 is connected to LOAD (cs)
LedMatrix matrix(11, 13, 10);

const uint16_t delaytime = 1000;

void setup() 
{
    // Set the brightness. (0..15)
    matrix.setIntensity(1);
}


void loop()
{
    matrix.set({B00111111, B00011111, B00001111, B00011111, B00110011, B01100001, B11000111, B10000111});
    delay(delaytime);
    
    matrix.invert();
    delay(delaytime);
    
    matrix.setRotation();
}
