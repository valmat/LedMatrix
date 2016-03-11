#include "LedMatrix.h"

// pin 11 is connected to the DataIn
// pin 13 is connected to the CLK
// pin 10 is connected to LOAD (cs)
LedMatrix matrix(11, 13, 10);

const uint16_t delaytime = 700;

void setup() 
{
    // Set the brightness to a medium values
    matrix.setIntensity(1);
}

void loop() 
{
    matrix.set({B01011010, B10100101, B01100110, B10011001, B10011001, B01100110, B10100101, B01011010});
    delay(delaytime);
    matrix.invert();
    delay(delaytime);

    
    matrix.set({B00011000, B00100100, B01100110, B10011001, B10011001, B01100110, B00100100, B00011000});
    delay(delaytime);
    matrix.invert();
    delay(delaytime);
    
    matrix.set({B11111111, B11111111, B11111111, B01111110, B00111100, B00011000, B00011000, B01111110});
    delay(delaytime);
    matrix.invert();
    delay(delaytime);
    
    matrix.set({B00000000, B00010000, B00101000, B00010000, B00111000, B10010010, B01010100, B00111000});
    delay(delaytime);
    matrix.invert();
    delay(delaytime);
    
    matrix.set({B11111110, B10000010, B10000010, B11111110, B10101010, B11111110, B10101010, B11111110});
    delay(delaytime);
    matrix.invert();
    delay(delaytime);

    matrix.set({B00000000, B01100110, B10011001, B10000001, B01000010, B00100100, B00011000, B00000000});
    delay(delaytime);
    matrix.invert();
    delay(delaytime);
    
    matrix.set({B01111111, B00111111, B00011111, B00011111, B00111111, B01110011, B11100001, B01000000});
    delay(delaytime);
    matrix.invert();
    delay(delaytime);
    
    
    matrix.setRotation();
}
