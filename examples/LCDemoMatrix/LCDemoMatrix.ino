//We always have to include the library
#include "LedMatrix.h"

/*
 Now we need a LedMatrix to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn 
 pin 11 is connected to the CLK 
 pin 10 is connected to LOAD 
 We have only a single MAX72XX.
 */
LedMatrix lc(12,11,10);

/* we always wait a bit between updates of the display */
unsigned long delaytime=100;

void setup() {
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.wakeup();
  /* Set the brightness to a medium values */
  //lc.setIntensity(8);
  lc.setIntensity(1);
  /* and clear the display */
  lc.clear();
}

/*
 This method will display the characters for the
 word "Arduino" one after the other on the matrix. 
 (you need at least 5x7 leds to see the whole chars)
 */
void writeArduinoOnMatrix() {
  /* here is the data for the characters */


  /* now display them one by one with a small delay */
  // A
  lc.set({B01110000, B10001000, B10001000, B10001000, B11111000, B10001000, B10001000, B10001000});
  delay(5*delaytime);

  // r
  lc.set({B00000000, B00000000, B00000000, B10110000, B11001000, B10000000, B10000000, B10000000});
  delay(10*delaytime);

  // d
  lc.set({B00000000, B00001000, B00001000, B01101000, B10011000, B10001000, B10011000, B01101000});
  delay(10*delaytime);

  //u
  lc.set({B00000000, B00000000, B00000000, B10001000, B10001000, B10001000, B10011000, B01101000});
  delay(10*delaytime);

  // i
  lc.set({B00000000, B00100000, B00000000, B01100000, B00100000, B00100000, B00100000, B01110000});
  delay(10*delaytime);
  
  //n
  lc.set({B00000000, B00000000, B00000000, B10110000, B11001000, B10001000, B10001000, B10001000});
  delay(10*delaytime);

  // o
  uint8_t o[] = {B00000000, B00000000, B00000000, B01110000, B10001000, B10001000, B10001000, B01110000};
  lc.setRow(0, o[0]);
  lc.setRow(1, o[1]);
  lc.setRow(2, o[2]);
  lc.setRow(3, o[3]);
  lc.setRow(4, o[4]);
  lc.setRow(5, o[5]);
  lc.setRow(6, o[6]);
  lc.setRow(7, o[7]);
  delay(5*delaytime);

  lc.clear();
  delay(10*delaytime);
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
    lc.setRow(row, B10100000);
    delay(delaytime);
    lc.setRow(row, 0);
    for(int i=0;i<row;i++) {
      delay(delaytime);
      lc.setRow(row, B10100000);
      delay(delaytime);
      lc.setRow(row, 0);
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
    lc.setCol(col,B10100000);
    delay(delaytime);
    lc.setCol(col,0);
    for(int i=0;i<col;i++) {
      delay(delaytime);
      lc.setCol(col,B10100000);
      delay(delaytime);
      lc.setCol(col,0);
    }
  }
}

/* 
 This function will light up every Led on the matrix.
 The led will blink along with the row-number.
 row number 4 (index==3) will blink 4 times etc.
 */
void single() {
  for(int row=0;row<8;row++) {
    for(int col=0;col<8;col++) {
      delay(delaytime);
      lc.set(row,col,true);
      delay(delaytime);
      for(int i=0;i<col;i++) {
        lc.set(row,col,false);
        delay(delaytime);
        lc.set(row,col,true);
        delay(delaytime);
      }
    }
  }
}

void loop() { 
  writeArduinoOnMatrix();
  
  /*
  rows();
  columns();
  single();
  */
}
