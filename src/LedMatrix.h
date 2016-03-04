/*
 *
 * LedMatrix - is is my fork of LedContr1ol lylbrary
 *
 */

#pragma once

#include <Pino.h>
#include "RowCol.h"

class LedMatrix {
private:
    // Size of matrix (the length of the row and column of a square matrix)
    constexpr static uint8_t _size = 8;

    // The maximum number of matrices
    constexpr static uint8_t _limit = 8;

    // The array for shifting the data to the devices
    uint8_t spidata[2 * _limit];
    
    // We keep track of the led-status for all 8 devices in this array
    uint8_t status[_size * _size];
    
    // Data is shifted out of this pin
    Pino _mosi;
    
    // The clock is signaled on this pin
    Pino _clk;
    
    // This one is driven LOW for chip selectzion
    Pino _cs;

    // If the matrix is placed in cascade, _index is a number in the cascade.
    const uint8_t _index = 0;
    
public:
    /* 
     * Create a new controler 
     * Params :
     * dataPin		pin on the Arduino where data gets shifted out
     * clockPin		pin for the clock
     * csPin		pin for selecting the device 
     */
    LedMatrix(Pino data, Pino clk, Pino cs);

    // Set the shutdown (power saving) mode for the device
    void shutdown();

    // Set the wakeup mode for the device
    void wakeup();

    /* 
     * Set the brightness of the display.
     * Params:
     * intensity	the brightness of the display. (0..15)
     */
    void setIntensity(int intensity);

    // Switch all Leds on the display off. 
    void clear();

    /* 
     * Set the status of a single Led.
     * Params :
     * row	the row of the Led (0..7)
     * col	the column of the Led (0..7)
     * state	If true the led is switched on, 
     *		if false it is switched off
     */
    void setLed(Row<_size> row, Col<_size> col, boolean state);
    
    void on(Row<_size> row, Col<_size> col)
    {
        setLed(row, col, true);
    }
    void off(Row<_size> row, Col<_size> col)
    {
        setLed(row, col, false);
    }

    /* 
     * Set all 8 Led's in a row to a new state
     * Params:
     * row	row which is to be set (0..7)
     * value	each bit set to 1 will light up the
     *		corresponding Led.
     */
    void setRow(Row<_size> row, uint8_t value);

    /* 
     * Set all 8 Led's in a column to a new state
     * Params:
     * col	column which is to be set (0..7)
     * value	each bit set to 1 will light up the
     *		corresponding Led.
     */
    void setCol(Col<_size> col, uint8_t value);

    /*
    void set(Row<_size> row, uint8_t value)
    {
        setRow(row, value);
    }
    void set(Col<_size> col, uint8_t value)
    {
        setCol(col, value);
    }
    */


private:
    /* 
     * Set the number of digits (or rows) to be displayed.
     * See datasheet for sideeffects of the scanlimit on the brightness
     * of the display.
     * Params :
     * limit    number of digits to be displayed (1..8)
     */
    void setScanLimit(int limit);

    // Send out a single command to the device
    void spiTransfer(uint8_t opcode, uint8_t data);

};


