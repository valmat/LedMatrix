#include "MatrixCascade.h"
// This time we have more than one device. 


// pin 11 is connected to the DataIn
// pin 13 is connected to the CLK
// pin 10 is connected to LOAD (cs)
const uint8_t CascadeSize = 3;
MatrixCascade<CascadeSize> cascade(11, 13, 10);

unsigned long delaytime = 30;

void setup()
{
    // Set the brightness. (0..15)
    cascade.setIntensity(0);

    // Rotate some matrixes
    cascade[1].setRotation(2);
    cascade[2].setRotation(2);
}

void loop()
{ 
    for(auto &matrix: cascade) {
        for(auto &row: matrix.rows()) {
            for(auto &col: matrix.cols()) {
                delay(delaytime);
                matrix.on(row, col);
            }
        }
    }

    for(auto &matrix: cascade) {
        for(auto &col: matrix.cols()) {
            for(auto &row: matrix.rows()) {
                delay(delaytime);
                matrix.off(row, col);
            }
        }

        // Rotate matrix
        matrix.setRotation();
    }
}

