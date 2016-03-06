#pragma once

/*
 *
 * Helper class to control matrix rotation
 *
 */

class MatrixRotator {
public:
    // Constructor
    MatrixRotator(uint8_t row, uint8_t col, uint8_t rotate, uint8_t size) : 
        _x(row), _y(col), _swaped(rotate % 2)
    {
        if(1 == rotate) {
            _x = col;
            _y = size - 1 - row;
        } else if(2 == rotate) {
            _x = size - 1 - row;
            _y = size - 1 - col;

        } else if(3 == rotate) {
            _x = size - 1 - col;
            _y = row;
        }
        // If rotate == 0 nothing doing
    }

    uint8_t row() const
    {
        return _x;
    }

    uint8_t col() const
    {
        return _y;
    }

    bool isSwaped() const
    {
        return _swaped;
    }

private:
    uint8_t _x;
    uint8_t _y;
    bool _swaped;
};


