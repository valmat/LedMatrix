/*
 *
 * LedMatrix is a class to control 8-bit LED matrix on controller MAX7219 and MAX7221.
 * This class manages only the LED-matrix, but does it well.
 *
 *  @author   Valeriy V Dmitriev aka valmat <ufabiz@gmail.com>, http://valmat.ru/
 *  @licenses MIT https://opensource.org/licenses/MIT
 *  @repo     https://github.com/valmat/LedMatrix
 *
 *
 */

#pragma once

#include "Arduino.h"
#include "RowCol.h"
#include "RowColIterator.h"
#include "CoreMax72xx.h"
#include "initializer_list.h"
#include "move.h"

// forward declaration
template<uint16_t CascadeSize>
class MatrixCascade;

 
class LedMatrix : public CoreMax72xx {
    
    using core = CoreMax72xx;

public:

    // Software-SPI Constructor
    // @param dataPin   pin on the Arduino where data gets shifted out (DIN)
    // @param clockPin  pin for the clock  (CLK)
    // @param csPin     pin for selecting the device   (CS - chip select pin)
    LedMatrix(uint8_t data, uint8_t clk, uint8_t cs) :
        LedMatrix(data, clk, cs, 0, 1)
    {}

    // HardWare-SPI Constructor
    // @param csPin        pin for selecting the device   (CS -- chip select pin)
    LedMatrix(uint8_t cs) :
        LedMatrix(cs, 0, 1, true)
    {}

    // Copy & Move constructors
    LedMatrix( const LedMatrix& ) = delete;
    LedMatrix( LedMatrix&& ) = default;
    // Copy & Move assigment
    LedMatrix& operator=(const LedMatrix&) = delete;
    LedMatrix& operator=(LedMatrix &&) = default;
    
   
    // Set the status of a single LED.
    // @param Row row   the row of the Led (0..7)
    // @param Col col   the column of the Led (0..7)
    // @param state If true the led is switched on, if false it is switched off
    void set(const Row &row, const Col &col, bool state);
    
    // Turn on LED at a point
    // @param Row row   the row of the Led (0..7)
    // @param Col col   the column of the Led (0..7)
    void on(const Row &row, const Col &col)
    {
        set(row, col, true);
    }
    // Turn off LED at a point
    // @param Row row   the row of the Led (0..7)
    // @param Col col   the column of the Led (0..7)
    void off(const Row &row, const Col &col)
    {
        set(row, col, false);
    }

    // Set all LEDs in a row to a new state
    // @param  row which is to be set (0..7)
    // @param  value each bit set to 1 will light up the corresponding LED.
    void set(const Row &row, buint8_t value);

    // Set all LEDs in a column to a new state
    // @param  col -- column which is to be set (0..7)
    // @param  value -- each bit set to 1 will light up the corresponding LED.
    void set(const Col &col, buint8_t value);

    // Set all LEDs in a row to a new state
    // @param  row which is to be set (0..7)
    // @param  value each bit set to 1 will light up the corresponding LED.
    void setRow(const Row &row, buint8_t value)
    {
        set(row, value);
    }

    // Set all LEDs in a column to a new state
    // @param  col -- column which is to be set (0..7)
    // @param  value -- each bit set to 1 will light up the corresponding LED.
    void setCol(const Col &col, buint8_t value)
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
    bool get(const Row &row, const Col &col) const;

    // Get the values on row of LED-matrix
    // @param row   the row of the Led (0..7)
    buint8_t get(const Row &row) const;

    // Get the values on colomn of LED-matrix
    // @param col   the column of the Led (0..7)
    buint8_t get(const Col &col) const;

    // Get the values on row of LED-matrix
    // @param row   the row of the Led (0..7)
    buint8_t getRow(const Row &row) const
    {
        return get(row);
    }

    // Get the values on colomn of LED-matrix
    // @param col   the column of the Led (0..7)
    buint8_t getCol(const Col &col) const
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
    buint8_t shiftUp(buint8_t value = 0);
    buint8_t shiftDown(buint8_t value = 0);
    buint8_t shiftLeft(buint8_t value = 0);
    buint8_t shiftRight(buint8_t value = 0);

    
    // Set how many times to rotate the matrix clockwise
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

    // Get how many times the matrix was rotated clockwise
    uint8_t getRotation() const
    {
        return _rotate;
    }


    // get device index in cascade
    uint16_t index() const
    {
        return _index;
    }
    

private:

    // set device index in cascade
    void index(uint16_t ind)
    {
        _index = ind;
    }

    // Private empty constructor
    // Only MatrixCascade can use it
    LedMatrix() {}

    // Private Software-SPI Constructor
    // Only MatrixCascade can use it
    // @param dataPin      pin on the Arduino where data gets shifted out (DIN)
    // @param clockPin     pin for the clock  (CLK)
    // @param csPin        pin for selecting the device   (CS -- chip select pin)
    // @param ind          index in the devises cascade, if the devise is placed in cascade
    // @param cascadeSize  count of devices in cascade, if the devise is placed in a cascade
    LedMatrix(uint8_t data, uint8_t clk, uint8_t cs, uint8_t ind, uint16_t cascadeSize) :
        core(data, clk, cs, ind, cascadeSize),
        _index(ind)
    {}

    // Private HardWare-SPI Constructor
    // Only MatrixCascade can use it
    // @param csPin        pin for selecting the device   (CS -- chip select pin)
    // @param ind          index in the devises cascade, if the devise is placed in cascade
    // @param cascadeSize  count of devices in cascade, if the devise is placed in a cascade
    LedMatrix(uint8_t cs, uint8_t ind, uint16_t cascadeSize, bool) :
        core(cs, ind, cascadeSize, true),
        _index(ind)
    {}

private:  
    // Rotate index. How many times to rotate the matrix clockwise
    uint8_t _rotate = 0;

    // If the matrix is placed in cascade, _index is a index in the cascade.
    // The variable _index is already in the parent class CoreMax72xx.
    // But we can not use it, if cascade is united in supercascade.
    // Therefore, this class contains  its own variable _index
    uint16_t _index = 0;


    template<uint16_t __cascadeSize>
    friend class MatrixCascade;
};


