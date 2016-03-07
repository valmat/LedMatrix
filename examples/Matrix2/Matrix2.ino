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
unsigned long delaytime=300;

void setup() {
    Serial.begin(9600);
    lc.setIntensity(1);
    delay(250);
}

void onCols()
{
    // d
    uint8_t arr_d[] = {B00000000, B00001000, B00001000, B01101000, B10011000, B10001000, B10011000, B01101000};
    lc.setCol(0, arr_d[0]);
    delay(250);
    lc.setCol(1, arr_d[1]);
    delay(250);
    lc.setCol(2, arr_d[2]);
    delay(250);
    lc.setCol(3, arr_d[3]);
    delay(250);
    lc.setCol(4, arr_d[4]);
    delay(250);
    lc.setCol(5, arr_d[5]);
    delay(250);
    lc.setCol(6, arr_d[6]);
    delay(250);
    lc.setCol(7, arr_d[7]);
    delay(250);
    delay(3*delaytime);

    //u
    uint8_t arr_u[] = {B00000000, B00000000, B00000000, B10001000, B10001000, B10001000, B10011000, B01101000};
    lc.setCol(0, arr_u[0]);
    delay(250);
    lc.setCol(1, arr_u[1]);
    delay(250);
    lc.setCol(2, arr_u[2]);
    delay(250);
    lc.setCol(3, arr_u[3]);
    delay(250);
    lc.setCol(4, arr_u[4]);
    delay(250);
    lc.setCol(5, arr_u[5]);
    delay(250);
    lc.setCol(6, arr_u[6]);
    delay(250);
    lc.setCol(7, arr_u[7]);
    delay(250);
    delay(3*delaytime);

    // i
    uint8_t arr_i[] = {B00000000, B00100000, B00000000, B01100000, B00100000, B00100000, B00100000, B01110000};
    lc.setCol(0, arr_i[0]);
    delay(250);
    lc.setCol(1, arr_i[1]);
    delay(250);
    lc.setCol(2, arr_i[2]);
    delay(250);
    lc.setCol(3, arr_i[3]);
    delay(250);
    lc.setCol(4, arr_i[4]);
    delay(250);
    lc.setCol(5, arr_i[5]);
    delay(250);
    lc.setCol(6, arr_i[6]);
    delay(250);
    lc.setCol(7, arr_i[7]);
    delay(250);
    delay(3*delaytime);

    //n
    uint8_t arr_n[] = {B00000000, B00000000, B00000000, B10110000, B11001000, B10001000, B10001000, B10001000};
    lc.setCol(0, arr_n[0]);
    delay(250);
    lc.setCol(1, arr_n[1]);
    delay(250);
    lc.setCol(2, arr_n[2]);
    delay(250);
    lc.setCol(3, arr_n[3]);
    delay(250);
    lc.setCol(4, arr_n[4]);
    delay(250);
    lc.setCol(5, arr_n[5]);
    delay(250);
    lc.setCol(6, arr_n[6]);
    delay(250);
    lc.setCol(7, arr_n[7]);
    delay(250);
    delay(3*delaytime);

    // o
    uint8_t arr_o[] = {B00111111, B00011111, B00001111, B00011011, B00110001, B01100000, B11000111, B00000111};
    lc.setCol(0, arr_o[0]);
    delay(250);
    lc.setCol(1, arr_o[1]);
    delay(250);
    lc.setCol(2, arr_o[2]);
    delay(250);
    lc.setCol(3, arr_o[3]);
    delay(250);
    lc.setCol(4, arr_o[4]);
    delay(250);
    lc.setCol(5, arr_o[5]);
    delay(250);
    lc.setCol(6, arr_o[6]);
    delay(250);
    lc.setCol(7, arr_o[7]);
    delay(250);
    delay(3*delaytime);

    lc.clear();
    delay(3*delaytime);
}

void onRows()
{
    // d
    uint8_t arr_d[] = {B00000000, B00001000, B00001000, B01101000, B10011000, B10001000, B10011000, B01101000};
    lc.setRow(0, arr_d[0]);
    delay(250);
    lc.setRow(1, arr_d[1]);
    delay(250);
    lc.setRow(2, arr_d[2]);
    delay(250);
    lc.setRow(3, arr_d[3]);
    delay(250);
    lc.setRow(4, arr_d[4]);
    delay(250);
    lc.setRow(5, arr_d[5]);
    delay(250);
    lc.setRow(6, arr_d[6]);
    delay(250);
    lc.setRow(7, arr_d[7]);
    delay(250);
    delay(3*delaytime);

    //u
    uint8_t arr_u[] = {B00000000, B00000000, B00000000, B10001000, B10001000, B10001000, B10011000, B01101000};
    lc.setRow(0, arr_u[0]);
    delay(250);
    lc.setRow(1, arr_u[1]);
    delay(250);
    lc.setRow(2, arr_u[2]);
    delay(250);
    lc.setRow(3, arr_u[3]);
    delay(250);
    lc.setRow(4, arr_u[4]);
    delay(250);
    lc.setRow(5, arr_u[5]);
    delay(250);
    lc.setRow(6, arr_u[6]);
    delay(250);
    lc.setRow(7, arr_u[7]);
    delay(250);
    delay(3*delaytime);

    // i
    uint8_t arr_i[] = {B00000000, B00100000, B00000000, B01100000, B00100000, B00100000, B00100000, B01110000};
    lc.setRow(0, arr_i[0]);
    delay(250);
    lc.setRow(1, arr_i[1]);
    delay(250);
    lc.setRow(2, arr_i[2]);
    delay(250);
    lc.setRow(3, arr_i[3]);
    delay(250);
    lc.setRow(4, arr_i[4]);
    delay(250);
    lc.setRow(5, arr_i[5]);
    delay(250);
    lc.setRow(6, arr_i[6]);
    delay(250);
    lc.setRow(7, arr_i[7]);
    delay(250);
    delay(3*delaytime);

    //n
    uint8_t arr_n[] = {B00000000, B00000000, B00000000, B10110000, B11001000, B10001000, B10001000, B10001000};
    lc.setRow(0, arr_n[0]);
    delay(250);
    lc.setRow(1, arr_n[1]);
    delay(250);
    lc.setRow(2, arr_n[2]);
    delay(250);
    lc.setRow(3, arr_n[3]);
    delay(250);
    lc.setRow(4, arr_n[4]);
    delay(250);
    lc.setRow(5, arr_n[5]);
    delay(250);
    lc.setRow(6, arr_n[6]);
    delay(250);
    lc.setRow(7, arr_n[7]);
    delay(250);
    delay(3*delaytime);

    // o
    uint8_t arr_o[] = {B00111111, B00011111, B00001111, B00011011, B00110001, B01100000, B11000111, B00000111};
    lc.setRow(0, arr_o[0]);
    delay(250);
    lc.setRow(1, arr_o[1]);
    delay(250);
    lc.setRow(2, arr_o[2]);
    delay(250);
    lc.setRow(3, arr_o[3]);
    delay(250);
    lc.setRow(4, arr_o[4]);
    delay(250);
    lc.setRow(5, arr_o[5]);
    delay(250);
    lc.setRow(6, arr_o[6]);
    delay(250);
    lc.setRow(7, arr_o[7]);
    delay(250);
    delay(3*delaytime);

    lc.clear();
    delay(3*delaytime);
}

void loop() { 
    onCols();
    onRows();
}
