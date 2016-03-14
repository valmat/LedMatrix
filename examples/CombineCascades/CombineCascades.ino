#include "MatrixCascade.h"

//
//
// This example clearly shows the difference in the speed between the hardware and software SPI
//
//

// pin 11 is connected to the DataIn
// pin 13 is connected to the CLK
// pin 10 is connected to LOAD
auto cascade = combineCascades(
    MatrixCascade<2>(10), 
    MatrixCascade<1>(5, 6, 7)
);



const uint8_t picsCount = 3;
const uint8_t pics[3][8] = {
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
    // Shifting Right
    //

    //iterate over colomns
    for (uint8_t i = 0; i < matrixSize; ++i)
    {
        // get last colomn in cascade
        auto LastCol = cascade[cascade.size() - 1].getCol(matrixSize - 1);

        for (auto &matrix: cascade)
        {
            LastCol = matrix.shiftRight(LastCol);
            delay(20);
        }
        //delay(100);
    }
    //delay(100);
}
