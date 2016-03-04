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
  lc.setIntensity(8);
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
  lc.set({B01111110,B10001000,B10001000,B10001000,B01111110});
  delay(5*delaytime);

  // r
  lc.set({B00111110,B00010000,B00100000,B00100000,B00010000});
  delay(5*delaytime);

  // d
  lc.set({B00011100,B00100010,B00100010,B00010010,B11111110});
  delay(5*delaytime);

  //u
  lc.set({B00111100,B00000010,B00000010,B00000100,B00111110});
  delay(5*delaytime);

  // i
  lc.set({B00000000,B00100010,B10111110,B00000010,B00000000});
  delay(5*delaytime);
  
  //n
  lc.set({B00111110,B00010000,B00100000,B00100000,B00011110});
  delay(5*delaytime);

  //n
  lc.set({B00111110, B00010000, B00100000, B00100000, B00011110,});
  delay(5*delaytime);

  // o
  uint8_t o[] = {B00011100, B00100010, B00100010, B00100010, B00011100};
  lc.setRow(0, o[0]);
  lc.setRow(1, o[1]);
  lc.setRow(2, o[2]);
  lc.setRow(3, o[3]);
  lc.setRow(4, o[4]);
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
