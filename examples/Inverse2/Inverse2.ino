#include "LedMatrix.h"

// pin 11 is connected to the DataIn
// pin 13 is connected to the CLK
// pin 10 is connected to LOAD (cs)
LedMatrix matrix(11, 13, 10);

void setup()
{
    // Set the brightness. (0..15)
    matrix.setIntensity(0);
}

void loop()
{
    // Switch all LEDs on the display to off.
    matrix.clear();
    delay(300);

    // Switch all LEDs on the display to on.
    matrix.fill();
    delay(300);

    // Iterate over rows to invert them
    for(auto &row: matrix.rows()) {
        matrix.invert(row);
        delay(70);
    }
    // Iterate over colomns to invert them
    for(auto &col: matrix.cols()) {
        matrix.invert(col);
        delay(70);
    }

    // Iterate for each point to invert it
    for(auto &row: matrix.rows()) {
        for(auto &col: matrix.cols()) {
            matrix.invert(row, col);
            delay(30);
        }
    }

}
