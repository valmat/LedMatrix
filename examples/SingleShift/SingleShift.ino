#include "LedMatrix.h"

// pin 12 is connected to the DataIn 
// pin 11 is connected to the CLK 
// pin 10 is connected to LOAD 
LedMatrix matrix(12,11,10);

const uint16_t delaytime = 1000;

//const uint8_t pic[] = {B11001111, B10011110, B00111100, B01111001, B11110011, B11100111, B11001111, B10011110};
const uint8_t pic[] = {B01001001, B10010010, B00100100, B01001000, B10010000, B00100000, B01000000, B10000000};

void setup() 
{
    //Serial.begin(9600);
    // Set the brightness. (0..15)
    matrix.setIntensity(0);
    matrix.set(pic);
}


uint8_t ind = 0;

void loop()
{
    delay(delaytime);

    //matrix.shiftUp(pic[ind%8]);

    //matrix.shiftUp();
    //matrix.shiftDown();
    //matrix.shiftRight();
    matrix.shiftLeft();


    ind++;




    /*

    for(auto &row: matrix.rows()) {
        for(auto &col: matrix.cols()) {
        }
    }

    matrix.set({B00111111, B00011111, B00001111, B00011111, B00110011, B01100001, B11000111, B10000111});
    printSer("orig:");
    delay(delaytime);
    
    matrix.invert();
    printSer("inverted:");
    delay(delaytime);
    
    matrix.setRotation();
    */
}
