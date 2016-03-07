#include "LedMatrix.h"

// pin 12 is connected to the DataIn 
// pin 11 is connected to the CLK 
// pin 10 is connected to LOAD 
LedMatrix matrix(12,11,10);

unsigned long delaytime=300;

void setup() {
  // Set the brightness. (0..15)
  matrix.setIntensity(1);
}

/*
 This method will display the characters for the
 word "Arduino" one after the other on the matrix. 
 (you need at least 5x7 leds to see the whole chars)
 */
void writeArduinoOnMatrix() {

  /* now display them one by one with a small delay */
  // A
  matrix.set({B01110000, B10001000, B10001000, B10001000, B11111000, B10001000, B10001000, B10001000});
  //matrix.set({B00000000, B01100110, B10011001, B10000001, B01000010, B00100100, B00011000, B00000000});
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
  matrix.set({B00000000, B00100000, B00000000, B01100000, B00100000, B00100000, B00100000, B01110000});
  delay(3*delaytime);
  
  //n
  matrix.set({B00000000, B00000000, B00000000, B10110000, B11001000, B10001000, B10001000, B10001000});
  delay(3*delaytime);

  // o
  uint8_t o[] = {B00000000, B00000000, B00000000, B01110000, B10001000, B10001000, B10001000, B01110000};
  matrix.setRow(0, o[0]);
  matrix.setRow(1, o[1]);
  matrix.setRow(2, o[2]);
  matrix.setRow(3, o[3]);
  matrix.setRow(4, o[4]);
  matrix.setRow(5, o[5]);
  matrix.setRow(6, o[6]);
  matrix.setRow(7, o[7]);
  delay(3*delaytime);

  matrix.clear();
  delay(3*delaytime);
}

/*
  This function lights up a some Leds in a row.
 The pattern will be repeated on every row.
 The pattern will blink along with the row-number.
 row number 4 (index==3) will blink 4 times etc.
 */
void rows() {
  for(int row=0; row<8; row++) {
    delay(delaytime);
    matrix.setRow(row, B10100000);
    delay(delaytime);
    matrix.setRow(row, 0);
    for(int i=0;i<row;i++) {
      delay(delaytime);
      matrix.setRow(row, B10100000);
      delay(delaytime);
      matrix.setRow(row, 0);
    }
  }
}

/*
  This function lights up a some Leds in a column.
 The pattern will be repeated on every column.
 The pattern will blink along with the column-number.
 column number 4 (index==3) will blink 4 times etc.
 */
void columns() {
  for(int col=0;col<8;col++) {
    delay(delaytime);
    matrix.setCol(col,B10100000);
    delay(delaytime);
    matrix.setCol(col,0);
    for(int i=0;i<col;i++) {
      delay(delaytime);
      matrix.setCol(col,B10100000);
      delay(delaytime);
      matrix.setCol(col,0);
    }
  }
}

/* 
 This function will light up every Led on the matrix.
 The led will blink along with the row-number.
 row number 4 (index==3) will blink 4 times etc.
 */
void single() {
  for(int row=0; row<8; row++) {
    for(int col=0; col<8; col++) {
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
