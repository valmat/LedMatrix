#include "MatrixCascade.h"

// pin 11 is connected to the DataIn
// pin 13 is connected to the CLK
// pin 10 is connected to LOAD (cs)
const uint8_t CascadeSize = 3;
MatrixCascade<CascadeSize> cascade(11, 13, 10);

unsigned long delaytime = 20;

void setup()
{
    // Set the brightness. (0..15)
    cascade.setIntensity(0);

    // Rotate some matrixes
    cascade[1].setRotation(2);
    cascade[2].setRotation(2);

    // Init random sequense
    randomSeed(millis());
}


void loop()
{ 
    for(auto &matrix: cascade) {
        for(auto &row: matrix.rows()) {
            for(auto &col: matrix.cols()) {
                delay(delaytime);
                matrix.set(row, col, random(2));
            }
        }
    }

    // Invert all matrixes on cascade
    cascade.invert();
    delay(50*delaytime);

    for(auto &matrix: cascade) {
        for(auto &col: matrix.cols()) {
            for(auto &row: matrix.rows()) {
                delay(delaytime);
                matrix.set(row, col, random(2));
            }
        }
        // Rotate matrix
        matrix.setRotation();
    }
    cascade.invert();
    delay(50*delaytime);

    cascade.clear();
    delay(50*delaytime);
    cascade.fill();
}

