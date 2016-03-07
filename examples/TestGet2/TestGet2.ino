#include "MatrixCascade.h"

// pin 12 is connected to the DataIn 
// pin 11 is connected to the CLK 
// pin 10 is connected to LOAD 
const uint8_t CascadeSize = 3;
MatrixCascade<CascadeSize> cascade(12, 11, 10);

const uint16_t delaytime = 300;

//const uint8_t pic[] = {B11001111, B10011110, B00111100, B01111001, B11110011, B11100111, B11001111, B10011110};
//const uint8_t pic[] = {B01001001, B10010010, B00100100, B01001000, B10010000, B00100000, B01000000, B10000000};
const uint8_t pic[] = {B10000011, B10000101, B10001001, B11010010, B11110100, B11010010, B10001001, B10000111};


// Print matrix on serial console
void printSer(const char * str) 
{
    /*
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
    */

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

void setup() 
{
    Serial.begin(9600);
    // Set the brightness. (0..15)
    cascade.setIntensity(0);
    
    for(auto &matrix: cascade) {
        matrix.set(pic);
    }

    printSer("orig:");

}

uint32_t ind = 0;

void loop()
{
    delay(delaytime);

    //matrix.shiftUp(pic[ind%8]);
    //matrix.shiftUp();
    
    //matrix.shiftDown(pic[ind%8]);
    //matrix.shiftDown();

    //matrix.shiftRight(pic[ind%8]);
    //matrix.shiftRight();

    //matrix.shiftLeft(pic[ind%8]);
    //matrix.shiftLeft();


    for(auto &matrix: cascade) {
        matrix.set(pic);
        for(int i = 0; i < 8; i++){
            matrix.shiftUp(pic[i%8]);
            delay(delaytime);
        }
        delay(1000);
        
        matrix.set(pic);
        for(int i = 0; i < 8; i++){
            matrix.shiftDown(pic[i%8]);
            delay(delaytime);
        }
        delay(1000);
        
        matrix.set(pic);
        for(int i = 0; i < 8; i++){
            matrix.shiftLeft(pic[i%8]);
            delay(delaytime);
        }
        delay(1000);
        
        matrix.set(pic);
        for(int i = 0; i < 8; i++){
            matrix.shiftRight(pic[i%8]);
            delay(delaytime);
        }
        delay(1000);
    }



    //printSer("Shifted:");
    //matrix.setRotation();


    ind++;

    /*
    matrix.set({B00111111, B00011111, B00001111, B00011111, B00110011, B01100001, B11000111, B10000111});
    printSer("orig:");
    delay(delaytime);
    
    matrix.invert();
    printSer("inverted:");
    delay(delaytime);
    
    matrix.setRotation();
    */
}
