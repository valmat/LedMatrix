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
    // Set the brightness to a medium values
    matrix.setIntensity(1);
    Serial.begin(9600);
}

void printSer(const char * str) 
{

    Serial.println("-----------------------------------");
    Serial.println(str);
    matrix.print();
    Serial.println("-----------------------------------");
    for(auto row: matrix.rows()) {
        for(auto col: matrix.cols()) {
            //Serial.print("(");
            //Serial.print(row);
            //Serial.print(",");
            //Serial.print(col);
            //Serial.print("):");
            Serial.print(matrix.get(row, col) ? ("*\t") : ("-\t"));
        }
        Serial.println();
    }
    Serial.println("-----------------------------------");
}

void loop() 
{


    /*
    uint8_t arr_d[] = {B00111111, B00011111, B00001111, B00011111, B00110011, B01100001, B11000111, B10000111};
    matrix.setCol(0, arr_d[0]);
    delay(50);
    matrix.setCol(1, arr_d[1]);
    delay(50);
    matrix.setCol(2, arr_d[2]);
    delay(50);
    matrix.setCol(3, arr_d[3]);
    delay(50);
    matrix.setCol(4, arr_d[4]);
    delay(50);
    matrix.setCol(5, arr_d[5]);
    delay(50);
    matrix.setCol(6, arr_d[6]);
    delay(50);
    matrix.setCol(7, arr_d[7]);

    delay(delaytime);
    //matrix.clear();
    matrix.invert();
    delay(50);
    */

    
    /*
    //matrix.set({B00000000, B01100110, B10011001, B10000001, B01000010, B00100100, B00011000, B00000000});
    matrix.set({B00111111, B00011111, B00001111, B00011111, B00110011, B01100001, B11000111, B10000111});
    printSer("orig:");
    delay(delaytime);
    //matrix.clear();
    //delay(50);
    //printSer("cleraed:");
    
    matrix.invert();
    //printSer("inverted:");
    delay(delaytime);
    */
    
    /*
    matrix.on(0,5);
    matrix.on(0,6);
    matrix.on(0,7);
    matrix.on(1,7);
    matrix.on(2,7);

    matrix.on(6,6);
    matrix.on(6,7);
    matrix.on(7,6);
    matrix.on(7,7);

    delay(delaytime);
    //matrix.clear();
    matrix.invert();
    delay(delaytime);
    matrix.clear();
    */


    //matrix.invert();
    //printSer("inverted:");
    //delay(delaytime);


    //matrix.set({B01011010, B10100101, B01100110, B10011001, B10011001, B01100110, B10100101, B01011010});
    //delay(delaytime);
    //matrix.clear();
    //matrix.invert();
    //delay(delaytime);

    
    matrix.set({B00011000, B00100100, B01100110, B10011001, B10011001, B01100110, B00100100, B00011000});
    delay(delaytime);
    matrix.invert();
    delay(delaytime);
    
    matrix.set({B11111111, B11111111, B11111111, B01111110, B00111100, B00011000, B00011000, B01111110});
    delay(delaytime);
    matrix.invert();
    delay(delaytime);
    
    matrix.set({B00000000, B00010000, B00101000, B00010000, B00111000, B10010010, B01010100, B00111000});
    delay(delaytime);
    matrix.invert();
    delay(delaytime);
    
    matrix.set({B11111110, B10000010, B10000010, B11111110, B10101010, B11111110, B10101010, B11111110});
    delay(delaytime);
    matrix.invert();
    delay(delaytime);
    
    
    matrix.set({B01111111, B00111111, B00011111, B00011111, B00111111, B01110011, B11100001, B01000000});
    delay(delaytime);
    matrix.invert();
    delay(delaytime);
    
    
    matrix.setRotation();
}
