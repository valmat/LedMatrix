/*
 *
 * CoreMax72xx this is a class to direct interaction with a controller MAX72xx
 *
 *  @author   Valeriy V Dmitriev aka valmat <ufabiz@gmail.com>, http://valmat.ru/
 *  @licenses MIT https://opensource.org/licenses/MIT
 *  @repo     https://github.com/valmat/LedMatrix
 *
 */

#pragma once

#include "Arduino.h"
#include "RowCol.h"
#include "RowColIterator.h"
#include "BitInt.h"
#include "DirectInteract.h"
 

class CoreMax72xx {
public:

    // Software-SPI constructor
    // @param dataPin      pin on the Arduino where data gets shifted out (DIN)
    // @param clockPin     pin for the clock  (CLK)
    // @param csPin        pin for selecting the device   (CS -- chip select pin)
    // @param ind          index in the devises cascade, if the devise is placed in cascade
    // @param cascadeSize  count of devices in cascade, if the devise is placed in a cascade
    CoreMax72xx(uint8_t dataPin, uint8_t clockPin, uint8_t csPin, uint8_t ind, uint16_t cascadeSize);
    
    CoreMax72xx(uint8_t dataPin, uint8_t clockPin, uint8_t csPin) :
        CoreMax72xx(dataPin, clockPin, csPin, 0, 1)
    {}

    // HardWare-SPI constructor
    // @param csPin        pin for selecting the device   (CS -- chip select pin)
    // @param ind          index in the devises cascade, if the devise is placed in cascade
    // @param cascadeSize  count of devices in cascade, if the devise is placed in a cascade
    CoreMax72xx(uint8_t csPin, uint8_t ind, uint16_t cascadeSize, bool);
    
    CoreMax72xx(uint8_t csPin) :
        CoreMax72xx(csPin, 0, 1, true)
    {}
    
    // Empty constructor
    CoreMax72xx() {}


    // Copy & Move constructors
    CoreMax72xx( const CoreMax72xx& ) = default;
    CoreMax72xx( CoreMax72xx&& ) = default;
    // Copy & Move assigment
    CoreMax72xx& operator=(const CoreMax72xx&) = default;
    CoreMax72xx& operator=(CoreMax72xx &&) = default;

    // Set the shutdown (power saving) mode for the device
    void shutdown() const;

    // Set the wakeup mode for the device
    void wakeup() const;

    // Set the brightness of the display.
    // @param intensity the brightness of the display. (0..15)
    void setIntensity(uint8_t intensity) const;

    // Switch all LEDs on the display to off.
    void clear();

    // Switch all LEDs on the display to on.
    void fill();


    // Set the status of a single LED.
    // @param Row row   the row of the Led (0..7)
    // @param Col col   the column of the Led (0..7)
    // @param state If true the led is switched on, if false it is switched off
    void set(const Row &row, const Col &col, bool state);

    // Set all LEDs in a row to a new state
    // @param  row which is to be set (0..7)
    // @param  value each bit set to 1 will light up the corresponding LED.
    void setRow(const Row &row, buint8_t value);

    // Set all LEDs in a column to a new state
    // @param  col -- column which is to be set (0..7)
    // @param  value -- each bit set to 1 will light up the corresponding LED.
    void setCol(const Col &col, buint8_t value);


    // Get state of LED point on matrix
    // @param row   the row of the Led (0..7)
    // @param col   the column of the Led (0..7)
    bool get(const Row &row, const Col &col) const;

    // Get the values on row of LED-matrix
    // @param row   the row of the Led (0..7)
    buint8_t getRow(const Row &row) const;

    // Get the values on colomn of LED-matrix
    // @param col   the column of the Led (0..7)
    buint8_t getCol(const Col &col) const;


    // get device index in cascade
    uint8_t index() const
    {
        return _index;
    }


    // Make rows and colomns iterable
    RowsIterator rows() const
    {
        return _rows;
    }
    ColsIterator cols() const
    {
        return _cols;
    }


private:

    // Set the number of digits (or rows) to be displayed.
    // See datasheet for sideeffects of the scanlimit on the brightness
    // of the display.
    // @param limit  number of digits to be displayed (1..8)
    void _setScanLimit(uint8_t limit) const;

    // Send out a single command to the device
    void _spiTransfer(uint8_t opcode, uint8_t data) const;

    // Initialize the chip
    void _initialize();


protected:

    // Rows and colomns iterators
    RowsIterator _rows{};
    ColsIterator _cols{};

    // Size of matrix (the length of the row and column of a square matrix)
    constexpr static uint8_t _size = 8;


private:

    // The maximum number of matrices
    constexpr static uint8_t _limit = 8;

    // The maximum of posible intensity
    constexpr static uint8_t _maxIntensity = 16;
   
    // This array contains the statuses of all points of LED matrix
    buint8_t _status[_size];
    
    // Pins interactor
    DirectInteract _pins;

    // If the matrix is placed in cascade, _index is a index in the cascade.
    uint8_t _index = 0;

    // If the matrix is placed in a cascade, cascadeSize is count of devices.
    uint16_t _cascadeSize = 1;

    bool _isHardwareSPI = false;
};

