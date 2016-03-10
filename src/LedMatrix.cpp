#include "LedMatrix.h"

// Binary order inverting transposition (helper function)
inline static uint8_t _binTranspos(uint8_t v)
{
    uint8_t r = 0;
    uint8_t pos = 1;
    uint8_t x, s = 8, s2 = 4; // s = sizeof(uint8_t)

    for(uint8_t i = 0; i < s2; i++) {
        x = v & (pos << i);
        r = r | ( x << (s-2*i-1) );
    }
    for(uint8_t i = 0; i < s2; i++) {
        x = v & ( pos << (s - i - 1) );
        r = r | ( x >> (s-2*i-1) );
    }
    return r;
}

void LedMatrix::set(const Row &row, const Col &col, bool state)
{
    // Set the value to the desired position depending on the seted rotation value
    if( 1 == _rotate ) {
        core::set(col, !row, state);
    } else if( 2 == _rotate ) {
        core::set(!row, !col, state);
    } else if( 3 == _rotate ) {
        core::set(!col, row, state);
    } else { // If _rotate == 0
        core::set(row, col, state);
    }
}

// Set all LEDs in a row to a new state
void LedMatrix::set(const Row &row, uint8_t value)
{
    // Set the value to the desired position depending on the seted rotation value
    if( 1 == _rotate ) {
        core::setCol(!row, value);
    } else if( 2 == _rotate ) {
        core::setRow(!row, _binTranspos(value));
    } else if( 3 == _rotate ) {
        core::setCol(row, _binTranspos(value));
    } else { // If _rotate == 0
        core::setRow(row, value);
    }
}

// Set all LEDs in a column to a new state
void LedMatrix::set(const Col &col, uint8_t value)
{
    // Set the value to the desired position depending on the seted rotation value
    if( 1 == _rotate ) {
        core::setRow(col, _binTranspos(value));
    } else if( 2 == _rotate ) {
        core::setCol(!col, _binTranspos(value));
    } else if( 3 == _rotate ) {
        core::setRow(!col, value);
    } else { // If _rotate == 0
        core::setCol(col, value);
    }
}

// Allows to initialize the values of all points of the matrix
void LedMatrix::set(const uint8_t arr[])
{
    for(auto &row: _rows) {
        set(row, arr[row]);
    }
}

// Get state of LED point on matrix
bool LedMatrix::get(const Row &row, const Col &col) const
{
    // Get the value to the desired position depending on the seted rotation value
    if( 1 == _rotate ) {
        return core::get(col, !row);
    } else if( 2 == _rotate ) {
        return core::get(!row, !col);
    } else if( 3 == _rotate ) {
        return core::get(!col, row);
    } else { // If _rotate == 0
        return core::get(row, col);
    }
}

// Get the values on row of LED-matrix
uint8_t LedMatrix::get(const Row &row) const
{
    // Set the value to the desired position depending on the seted rotation value
    if( 1 == _rotate ) {
        return core::getCol(!row);
    } else if( 2 == _rotate ) {
        return _binTranspos( core::getRow(!row) );
    } else if( 3 == _rotate ) {
        return _binTranspos( core::getCol(row) );
    } else { // If _rotate == 0
        return core::getRow(row);
    }
}

// Get the values on colomn of LED-matrix
uint8_t LedMatrix::get(const Col &col) const
{
    // Set the value to the desired position depending on the seted rotation value
    if( 1 == _rotate ) {
        return _binTranspos( core::getRow(col) );
    } else if( 2 == _rotate ) {
        return _binTranspos( core::getCol(!col) );
    } else if( 3 == _rotate ) {
        return core::getRow(!col);
    } else { // If _rotate == 0
        return core::getCol(col);
    }
}

// Invert all points of matrix
void LedMatrix::invert()
{
    for(auto &row: _rows) {
        // Using core methods is more effecient
        core::setRow(row, ~core::getRow(row));
    }
}

// Invert current point on matrix
void LedMatrix::invert(const Row &row, const Col &col)
{
    set(row, col, !get(row, col));
}

// Invert row on matrix
void LedMatrix::invert(const Row &row)
{
    set(row, ~get(row));
}

// Invert colomn on matrix
void LedMatrix::invert(const Col &col)
{
    set(col, ~get(col));
}

// Shift matrix
// Shift matrix
uint8_t LedMatrix::shiftUp(uint8_t value)
{
    uint8_t rez = getRow(0);
    for(uint8_t i = 0; i < _size-1; i++) {
        setRow(i, getRow(i+1));
    }
    setRow(_size-1, value);
    return rez;
}

uint8_t LedMatrix::shiftDown(uint8_t value)
{
    uint8_t rez = getRow(_size-1);
    for(uint8_t i = _size-1; i > 0; i--) {
        setRow(i, getRow(i-1));
    }
    setRow(0, value);
    return rez;
}

uint8_t LedMatrix::shiftLeft(uint8_t value)
{
    uint8_t rez = getCol(0);
    for(uint8_t i = 0; i < _size-1; i++) {
        setCol(i, getCol(i+1));
    }
    setCol(_size-1, value);
    return rez;
}

uint8_t LedMatrix::shiftRight(uint8_t value)
{
    uint8_t rez = getCol(_size-1);
    for(uint8_t i = _size-1; i > 0; i--) {
        setCol(i, getCol(i-1));
    }
    setCol(0, value);
    return rez;
}


