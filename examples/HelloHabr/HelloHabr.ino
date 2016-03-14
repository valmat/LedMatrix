#include "MatrixCascade.h"

// pin 11 is connected to the DataIn
// pin 13 is connected to the CLK
// pin 10 is connected to LOAD
const uint8_t CascadeSize = 3;
// Software SPI:
//MatrixCascade<CascadeSize> cascade(11, 13, 10);
// Hardware SPI:
MatrixCascade<CascadeSize> cascade(10);

const uint8_t cols[] = {
    0b11111111,
    0b10000000,
    0b10000000,
    0b10000000,
    0b10000000,
    0b11111111,
    0b00000000,

    0b00111111,
    0b00100100,
    0b00100100,
    0b00011000,
    0b00000000,

    0b00111111,
    0b00000010,
    0b00000100,
    0b00001000,
    0b00111111,
    0b00000000,

    0b00111111,
    0b00101001,
    0b00011001,
    0b00000110,
    0b00000000,

    0b00111111,
    0b00101001,
    0b00101001,
    0b00101001,
    0b00000000,

    0b00100000,
    0b00100000,
    0b00111111,
    0b00100000,
    0b00100000,
    0b00000000,

    0b11000011,
    0b01100110,
    0b00111100,
    0b00111100,
    0b01100110,
    0b11000011,
    0b00000000,

    0b00011111,
    0b00100100,
    0b00100100,
    0b00011111,
    0b00000000,

    0b00111111,
    0b00101001,
    0b00101001,
    0b00100110,
    0b00000000,

    0b00111111,
    0b00100100,
    0b00100100,
    0b00011000,
    0b00000000,

    0b00000000,
    0b00000000,
    0b00000000,
};
const uint8_t colsCount = sizeof(cols);


void setup() 
{
    cascade.setIntensity(0);

    // Rotate some matrixes
    cascade[1].setRotation(2);
    cascade[2].setRotation(2);
}

const uint8_t matrixSize = 8;

uint8_t offset = 0;

void loop()
{
    uint8_t colInd = 0;
    for (auto &matrix: cascade)
    {
        for (auto &col: matrix.cols())
        {
            matrix.set(col, cols[(offset + colInd)%colsCount]);
            colInd++;
            delay(3);
        }
        delay(7);
    }
    ++offset;
    offset %= colsCount;
}
