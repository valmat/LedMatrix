/*
 *
 * LedMatrix - is is my fork of LedContr1ol lylbrary
 *
 */

#pragma once

#include <Pino.h>
#include "RowCol.h"
#include "RowColIterator.h"
#include "initializer_list.h"
#include "move.h"

// forward declaration
template<uint8_t CascadeSize>
class MatrixCascade;

 
class LedMatrix {
public:

    // Constructor
    // @param dataPin   pin on the Arduino where data gets shifted out (DIN)
    // @param clockPin  pin for the clock  (CLK)
    // @param csPin     pin for selecting the device   (CS)
    LedMatrix(Pino data, Pino clk, Pino cs) :
        LedMatrix(data, clk, cs, 0)
    {}

    // Copy & Move constructors
    LedMatrix( const LedMatrix& ) = default;
    LedMatrix( LedMatrix&& ) = default;
    // Copy & Move assigment
    LedMatrix& operator=(const LedMatrix&) = default;
    LedMatrix& operator=(LedMatrix &&) = default;

    // Set the shutdown (power saving) mode for the device
    void shutdown() const;

    // Set the wakeup mode for the device
    void wakeup() const;

    // Set the brightness of the display.
    // @param intensity the brightness of the display. (0..15)
    void setIntensity(uint8_t intensity) const;

    // Switch all Leds on the display to off. 
    void clear();

    // Set the status of a single LED.
    // @param row   the row of the Led (0..7)
    // @param col   the column of the Led (0..7)
    // @param state If true the led is switched on, if false it is switched off
    void set(Row row, Col col, bool state);
    
    template <typename T1, typename T2>
    void on(T1&& t1, T2&& t2) {
        set(std::forward<T1>(t1), std::forward<T2>(t2), true);
    }
    template <typename T1, typename T2>
    void off(T1&& t1, T2&& t2) {
        set(std::forward<T1>(t1), std::forward<T2>(t2), false);
    }

    // Set all LED's in a row to a new state
    // @param  row which is to be set (0..7)
    // @param  value each bit set to 1 will light up the corresponding LED.
    void setRow(Row row, uint8_t value);

    // Set all LED's in a column to a new state
    // @param  col -- column which is to be set (0..7)
    // @param  value -- each bit set to 1 will light up the corresponding LED.
    void setCol(Col col, uint8_t value);

    void set(Row row, uint8_t value)
    {
        setRow(row, value);
    }
    void set(Col col, uint8_t value)
    {
        setCol(col, value);
    }

    void set(std::initializer_list<uint8_t> disp)
    {
        uint8_t rowNom = 0;
        for (auto &rowVal : disp) {
            setRow(rowNom++, rowVal);
        }
    }

    // Get state of LED point on matrix
    // @param row   the row of the Led (0..7)
    // @param col   the column of the Led (0..7)
    bool get(Row row, Col col);

    // Invert filled matrix
    void invert();


    // How many times to rotate the matrix clockwise
    // @param From 0 to 3
    void setRotation(uint8_t times = 1)
    {
        _rotate += times;
        _rotate = _rotate % 4;
    }
    // Reset rotation flag to default
    void resetRotation()
    {
        _rotate = 0;
    }
    
    // get matrix index in cascade
    uint8_t getIndex() const
    {
        return _index;
    }

    // Make rows and colomns iterable
    constexpr static RowsIterator rows()
    {
        return _rows;
    }
    constexpr static ColsIterator cols()
    {
        return _cols;
    }

private:

    // Private empty constructor
    // Only MatrixCascade can use it
    LedMatrix() {}

    // Private constructor
    // Only MatrixCascade can use it
    LedMatrix(Pino data, Pino clk, Pino cs, uint8_t ind, uint8_t cascadeSize = 1);

    // Set the number of digits (or rows) to be displayed.
    // See datasheet for sideeffects of the scanlimit on the brightness
    // of the display.
    // @param limit  number of digits to be displayed (1..8)
    void _setScanLimit(uint8_t limit) const;

    // Send out a single command to the device
    void _spiTransfer(uint8_t opcode, uint8_t data) const;

    void _set(uint8_t row, uint8_t col, bool state);
    void _setRow(uint8_t row, uint8_t value);
    void _setCol(uint8_t col, uint8_t value);


private:
    // Size of matrix (the length of the row and column of a square matrix)
    constexpr static uint8_t _size = 8;

    // The maximum number of matrices
    constexpr static uint8_t _limit = 8;

    // The maximum of posible intensity
    constexpr static uint8_t _maxIntensity = 16;

    // The array for shifting the data to the devices
    mutable uint8_t _spidata[2 * _limit];
    
    // We keep track of the led-status for all 8 devices in this array
    uint8_t _status[_size];
    
    // Data is shifted out of this pin
    Pino _mosi{0};
    
    // The clock is signaled on this pin
    Pino _clk{0};
    
    // This one is driven LOW for chip selectzion
    Pino _cs{0};

    // If the matrix is placed in cascade, _index is a index in the cascade.
    uint8_t _index = 0;

    // Rotate index. How many times to rotate the matrix clockwise
    uint8_t _rotate = 0;

    // If the matrix is placed in cascade, cascadeSize is a number of cascade devices.
    uint8_t _cascadeSize = 1;

    // Rows and colomns iterators
    constexpr static RowsIterator _rows{};
    constexpr static ColsIterator _cols{};

    template<uint8_t __cascadeSize>
    friend class MatrixCascade;
};


