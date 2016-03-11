#include "MatrixCascade.h"

// pin 12 is connected to the DataIn 
// pin 11 is connected to the CLK 
// pin 10 is connected to LOAD 
const uint8_t CascadeSize = 3;
MatrixCascade<CascadeSize> cascade(12, 11, 10);

const uint8_t picsCount = 3;
const uint8_t pics[3][8] = {
    //{0b10000011, 0b10000111, 0b10001001, 0b11010010, 0b11110100, 0b11010010, 0b10001001, 0b10000111},
    //{0b11111111, 0b10000001, 0b10111101, 0b10100101, 0b10100101, 0b10111101, 0b10000001, 0b11111111},
    //{0b10011001, 0b01011010, 0b00111100, 0b11111111, 0b11111111, 0b00111100, 0b01011010, 0b10011001},
    {B00000000, B00000000, B10001000, B11011001, B10101010, B10001011, B10001010, B00000000},
    {B00000000, B00000000, B00000000, B00010010, B10111011, B10010010, B10011010, B00000000},
    {B00000000, B00100000, B00000000, B10101001, B00100010, B00100100, B00101001, B00000000},
};


void setup() 
{
    cascade.setIntensity(0);

    // Rotate some matrixes
    cascade[1].setRotation(2);
    cascade[2].setRotation(2);

    for (auto &matrix: cascade)
    {
        matrix.set(pics[matrix.index()]);
    }
}

const uint8_t matrixSize = 8;

void loop()
{
    //
    // Shifting UP
    //

    //iterate over colomns
    for (uint8_t i = 0; i < matrixSize; ++i)
    {
        // get last colomn in cascade
        auto LastCol = cascade[CascadeSize - 1].getCol(matrixSize - 1);

        for (auto &matrix: cascade)
        {
            LastCol = matrix.shiftRight(LastCol);
            //delay(5);
        }
        //delay(100);
    }
    //delay(100);
}
