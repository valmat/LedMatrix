#include "LedMatrix.h"

// pin 12 is connected to the DataIn 
// pin 11 is connected to the CLK 
// pin 10 is connected to LOAD 
LedMatrix matrix(12,11,10);

const uint16_t delaytime = 300;

void setup()
{
    // Set the brightness. (0..15)
    matrix.setIntensity(0);
}


void loop()
{
    // Switch all LEDs on the display to off.
    matrix.clear();
    delay(delaytime);

    // Switch all LEDs on the display to on.
    matrix.fill();
    delay(delaytime);

    // Iterate over rows to invert them
    for(auto row: matrix.rows()) {
        matrix.invert(row);
        delay(delaytime);
    }
    // Iterate over colomns to invert them
    for(auto col: matrix.cols()) {
        matrix.invert(col);
        delay(delaytime);
    }

    // Iterate for each point to invert it
    for(auto row: matrix.rows()) {
        for(auto col: matrix.cols()) {
            matrix.invert(row, col);
            delay(delaytime);
        }
    }

}
