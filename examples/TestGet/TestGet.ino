#include "LedMatrix.h"

// pin 12 is connected to the DataIn 
// pin 11 is connected to the CLK 
// pin 10 is connected to LOAD 
LedMatrix matrix(12,11,10);

const uint16_t delaytime = 1000;

void setup() 
{
    Serial.begin(9600);
    // Set the brightness. (0..15)
    matrix.setIntensity(1);
}

// Print matrix on serial console
void printSer(const char * str) 
{
    Serial.println("--------------------------");
    Serial.println(str);
    Serial.println("--------------------------");
    for(auto &row: matrix.rows()) {
        for(auto &col: matrix.cols()) {
            Serial.print(matrix.get(row, col) ? ("*  ") : ("-  "));
        }
        Serial.println();
    }
    Serial.println("==========================");

    /*
    //Test for get(Row/Col):
    Serial.println("Rows:");
    for(auto &row: matrix.rows()) {
        Serial.println(matrix.get(row), BIN);
    }
    Serial.println("Cols:");
    for(auto &col: matrix.cols()) {
        Serial.println(matrix.get(col), BIN);
    }
    */
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
