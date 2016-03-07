//We always have to include the library
#include "LedMatrix.h"

// pin 12 is connected to the DataIn 
// pin 11 is connected to the CLK 
// pin 10 is connected to LOAD 
LedMatrix matrix(12,11,10);

/* we always wait a bit between updates of the display */
const uint16_t delaytime = 1000;


void setup() 
{
    Serial.begin(9600);
    // Set the brightness to a medium values
    matrix.setIntensity(1);
}

void printSer(const char * str) 
{

    Serial.println("--------------------------");
    Serial.println(str);
    Serial.println("--------------------------");
    for(auto row: matrix.rows()) {
        for(auto col: matrix.cols()) {
            Serial.print(matrix.get(row, col) ? ("*  ") : ("-  "));
        }
        Serial.println();
    }
    Serial.println("==========================");
}

void loop() 
{
    matrix.set({B00111111, B00011111, B00001111, B00011111, B00110011, B01100001, B11000111, B10000111});
    printSer("orig:");
    delay(delaytime);
    
    matrix.invert();
    printSer("inverted:");
    delay(delaytime);
    
    matrix.setRotation();
}
