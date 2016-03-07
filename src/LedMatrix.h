/*
 *
 * LedMatrix is a class to control 8-bit LED matrix on controller MAX7219 and MAX7221.
 * This class manages only the LED-matrix, but does it well.
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

    // Switch all LEDs on the display to off.
    void clear();

    // Switch all LEDs on the display to on.
    void fill();

    
    // Set the status of a single LED.
    // @param Row row   the row of the Led (0..7)
    // @param Col col   the column of the Led (0..7)
    // @param state If true the led is switched on, if false it is switched off
    void set(const Row &row, const Col &col, bool state);
    
    // Turn on LED at a point
    // @param Row row   the row of the Led (0..7)
    // @param Col col   the column of the Led (0..7)
    template <typename T1, typename T2>
    void on(T1&& t1, T2&& t2) {
        set(std::forward<T1>(t1), std::forward<T2>(t2), true);
    }
    // Turn off LED at a point
    // @param Row row   the row of the Led (0..7)
    // @param Col col   the column of the Led (0..7)
    template <typename T1, typename T2>
    void off(T1&& t1, T2&& t2) {
        set(std::forward<T1>(t1), std::forward<T2>(t2), false);
    }

    // Set all LEDs in a row to a new state
    // @param  row which is to be set (0..7)
    // @param  value each bit set to 1 will light up the corresponding LED.
    void set(const Row &row, uint8_t value);

    // Set all LEDs in a column to a new state
    // @param  col -- column which is to be set (0..7)
    // @param  value -- each bit set to 1 will light up the corresponding LED.
    void set(const Col &col, uint8_t value);

    // Set all LEDs in a row to a new state
    // @param  row which is to be set (0..7)
    // @param  value each bit set to 1 will light up the corresponding LED.
    void setRow(const Row &row, uint8_t value)
    {
        set(row, value);
    }

    // Set all LEDs in a column to a new state
    // @param  col -- column which is to be set (0..7)
    // @param  value -- each bit set to 1 will light up the corresponding LED.
    void setCol(const Col &col, uint8_t value)
    {
        set(col, value);
    }

    // Allows to initialize the values of all points of the matrix
    // @param  initializer_list instance
    template <typename T>
    void set(const std::initializer_list<T> &disp)
    {
        uint8_t rowNom = 0;
        for (auto &&rowVal : disp) {
            setRow(rowNom++, rowVal);
        }
    }

    // Allows to initialize the values of all points of the matrix
    // Attention. If you pass an array to this function, strictly follow its length
    // @param  raw array
    void set(const uint8_t arr[]);

    
    // Get state of LED point on matrix
    // @param row   the row of the Led (0..7)
    // @param col   the column of the Led (0..7)
    bool get(const Row &row, const Col &col);

    // Get the values on row of LED-matrix
    // @param row   the row of the Led (0..7)
    uint8_t get(const Row &row);

    // Get the values on colomn of LED-matrix
    // @param col   the column of the Led (0..7)
    uint8_t get(const Col &col);

    // Get the values on row of LED-matrix
    // @param row   the row of the Led (0..7)
    uint8_t getRow(const Row &row)
    {
        return get(row);
    }

    // Get the values on colomn of LED-matrix
    // @param col   the column of the Led (0..7)
    uint8_t getCol(const Col &col)
    {
        return get(col);
    }

    
    // Invert all points of matrix
    void invert();

    // Invert current point on matrix
    // @param row   the row of the LED (0..7)
    // @param col   the column of the LED (0..7)
    void invert(const Row &row, const Col &col);

    // Invert row on matrix
    // @param row   the row of the LED (0..7)
    void invert(const Row &row);

    // Invert colomn on matrix
    // @param col   the column of the LED (0..7)
    void invert(const Col &col);

    // Invert row on matrix
    // @param row   the row of the LED (0..7)
    void invertRow(const Row &row)
    {
        invert(row);
    }

    // Invert colomn on matrix
    // @param col   the column of the LED (0..7)
    void invertCol(const Col &col)
    {
        invert(col);
    }

    
    // Shift matrix
    // @param value is shifting value
    // @return shifted value
    uint8_t shiftUp(uint8_t value = 0);
    uint8_t shiftDown(uint8_t value = 0);
    uint8_t shiftLeft(uint8_t value = 0);
    uint8_t shiftRight(uint8_t value = 0);

    
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
    
    // This array contains the statuses of all points of LED matrix
    uint8_t _status[_size];
    
    // A pin on the Arduino where data gets shifted out (DIN).
    // Data is shifted out of this pin
    Pino _mosi{0};
    
    // The clock is signaled on this pin (CLK)
    Pino _clk{0};
    
    // This one is driven LOW for chip selection (CS)
    Pino _cs{0};

    // If the matrix is placed in cascade, _index is a index in the cascade.
    uint8_t _index = 0;

    // Rotate index. How many times to rotate the matrix clockwise
    uint8_t _rotate = 0;

    // If the matrix is placed in a cascade, cascadeSize is a index of cascade device.
    uint8_t _cascadeSize = 1;

    // Rows and colomns iterators
    constexpr static RowsIterator _rows{};
    constexpr static ColsIterator _cols{};

    template<uint8_t __cascadeSize>
    friend class MatrixCascade;
};


