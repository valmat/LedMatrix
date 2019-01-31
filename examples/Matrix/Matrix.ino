#include "LedMatrix.h"

// pin 11 is connected to the DataIn
// pin 13 is connected to the CLK
// pin 10 is connected to LOAD (cs)
LedMatrix matrix(11, 13, 10);

const uint16_t delaytime = 300;

void setup() {
    // Set the brightness. (0..15)
    matrix.setIntensity(1);
}

// This method will display the characters for the
// word "Arduino" one after the other on the matrix. 
// (you need at least 5x7 leds to see the whole chars)
void writeArduinoOnMatrix() {

    // now display them one by one with a small delay
    // A
    // using initializer_list example
    matrix.set({B01110000, B10001000, B10001000, B10001000, B11111000, B10001000, B10001000, B10001000});
    delay(3*delaytime);

    // r
    matrix.set({B00000000, B00000000, B00000000, B10110000, B11001000, B10000000, B10000000, B10000000});
    delay(3*delaytime);

    // d
    matrix.set({B00000000, B00001000, B00001000, B01101000, B10011000, B10001000, B10011000, B01101000});
    delay(3*delaytime);

    //u
    matrix.set({B00000000, B00000000, B00000000, B10001000, B10001000, B10001000, B10011000, B01101000});
    delay(3*delaytime);

    // i
    // Attention. You can do so, but do not use this option.
    // If you pass an array to the function set, strictly follow its length
    uint8_t arr_i[8] = {B00000000, B00100000, B00000000, B01100000, B00100000, B00100000, B00100000, B01110000};
    matrix.set(arr_i);
    delay(3*delaytime);

    //n
    auto arr_n = {B00000000, B00000000, B00000000, B10110000, B11001000, B10001000, B10001000, B10001000};
    matrix.set(arr_n);
    delay(3*delaytime);

    // o
    uint8_t arr_o[] = {B00000000, B00000000, B00000000, B01110000, B10001000, B10001000, B10001000, B01110000};
    // one by one for example
    for(auto &row: matrix.rows()) {
        matrix.set(row, arr_o[row]);
    }
    delay(3*delaytime);

    matrix.set({B00000000, B01100110, B10011001, B10000001, B01000010, B00100100, B00011000, B00000000});
    delay(3*delaytime);

    matrix.clear();
    delay(3*delaytime);
}

// This function lights up a some Leds in a row.
// The pattern will be repeated on every row.
// The pattern will blink along with the row-number.
// row number 4 (index==3) will blink 4 times etc.
void rows() {
    for(auto &row: matrix.rows()) {
        delay(delaytime);
        matrix.set(row, B10101010);
        delay(delaytime);
        matrix.set(row, 0);

        for(int i=0; i<row; i++) {
            delay(delaytime);
            matrix.set(row, B01010101);
            delay(delaytime);
            matrix.set(row, 0);
        }
    }
}

// This function lights up a some Leds in a column.
// The pattern will be repeated on every column.
// The pattern will blink along with the column-number.
// column number 4 (index==3) will blink 4 times etc.
void columns() {
    for(auto &col: matrix.cols()) {
        delay(delaytime);
        matrix.set(col, B10101010);
        delay(delaytime);
        matrix.set(col, 0);

        for(int i=0; i < col; i++) {
            delay(delaytime);
            matrix.set(col, B01010101);
            delay(delaytime);
            matrix.set(col, 0);
        }
    }
}

// This function will light up every Led on the matrix.
// The led will blink along with the row-number.
// row number 4 (index==3) will blink 4 times etc.
void single() {
    for(auto &row: matrix.rows()) {
        for(auto &col: matrix.cols()) {
            delay(delaytime);
            matrix.on(row, col);
            delay(delaytime);
            for(int i=0; i<3; i++) {
                matrix.off(row, col);
                delay(delaytime);
                matrix.on(row, col);
                delay(delaytime);
            }
        }
    }
}




void loop() { 
    writeArduinoOnMatrix();
    rows();
    columns();
    single();
}
