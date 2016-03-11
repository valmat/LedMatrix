#include "MatrixCascade.h"

// pin 11 is connected to the DataIn
// pin 13 is connected to the CLK
// pin 10 is connected to LOAD
const uint8_t CascadeSize = 3;
MatrixCascade<CascadeSize> cascade(11, 13, 10);
//MatrixCascade<CascadeSize> cascade(10);

const uint16_t delaytime = 20;

//const uint8_t pic[] = {B11001111, B10011110, B00111100, B01111001, B11110011, B11100111, B11001111, B10011110};
//const uint8_t pic[] = {B01001001, B10010010, B00100100, B01001000, B10010000, B00100000, B01000000, B10000000};
const uint8_t pic[] = {B10000011, B10000101, B10001001, B11010010, B11110100, B11010010, B10001001, B10000111};


void setup() 
{
    // Set the brightness. (0..15)
    cascade.setIntensity(0);
    
    for(auto &matrix: cascade) {
        matrix.set(pic);
    }
}

void loop()
{
    delay(delaytime);

    for(auto &matrix: cascade) {
        matrix.set(pic);
        for(int i = 0; i < 8; i++){
            matrix.shiftUp(pic[i%8]);
            delay(delaytime);
        }
        delay(1000);
        
        matrix.set(pic);
        for(int i = 0; i < 8; i++){
            matrix.shiftDown(pic[i%8]);
            delay(delaytime);
        }
        delay(1000);
        
        matrix.set(pic);
        for(int i = 0; i < 8; i++){
            matrix.shiftLeft(pic[i%8]);
            delay(delaytime);
        }
        delay(1000);
        
        matrix.set(pic);
        for(int i = 0; i < 8; i++){
            matrix.shiftRight(pic[i%8]);
            delay(delaytime);
        }
        delay(1000);
        matrix.setRotation();
    }
}
