#include "LedMatrix.h"

// pin 11 is connected to the DataIn
// pin 13 is connected to the CLK
// pin 10 is connected to LOAD (cs)
LedMatrix matrix(11, 13, 10);

const uint16_t delaytime = 1000;

const uint8_t picsCount = 6;
const uint8_t pics[6][8] = {
    {0b10000011, 0b10000111, 0b10001001, 0b11010010, 0b11110100, 0b11010010, 0b10001001, 0b10000111},
    {0b11001111, 0b10011110, 0b00111100, 0b01111001, 0b11110011, 0b11100111, 0b11001111, 0b10011110},
    {0b01001001, 0b10010010, 0b00100100, 0b01001000, 0b10010000, 0b00100000, 0b01000000, 0b10000000},
    {0b11111111, 0b10000001, 0b10111101, 0b10100101, 0b10100101, 0b10111101, 0b10000001, 0b11111111},
    {0b10011001, 0b01011010, 0b00111100, 0b11111111, 0b11111111, 0b00111100, 0b01011010, 0b10011001},
    {0b11111000, 0b00000100, 0b00000010, 0b11111111, 0b11111111, 0b11000010, 0b11000100, 0b11001000},
};


void setup() 
{
    matrix.setIntensity(0);
}

uint8_t ind = 0;

void loop()
{
    
    auto pic = pics[ind % picsCount];

    matrix.set(pics[ind % picsCount]);
    for(int i = 0; i < 8; i++){
        matrix.shiftUp(pic[i%8]);
        delay(80);
    }
    delay(1000);
    
    matrix.set(pic);
    for(int i = 0; i < 8; i++){
        matrix.shiftDown(pic[i%8]);
        delay(80);
    }
    delay(1000);
    
    matrix.set(pic);
    for(int i = 0; i < 8; i++){
        matrix.shiftLeft(pic[i%8]);
        delay(80);
    }
    delay(1000);
    
    matrix.set(pic);
    for(int i = 0; i < 8; i++){
        matrix.shiftRight(pic[i%8]);
        delay(80);
    }
    delay(1000);

    ind++;
}
