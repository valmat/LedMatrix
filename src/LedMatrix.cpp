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
 
#include "LedMatrix.h"

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
void LedMatrix::set(const Row &row, buint8_t value)
{
    // Set the value to the desired position depending on the seted rotation value
    if( 1 == _rotate ) {
        core::setCol(!row, value);
    } else if( 2 == _rotate ) {
        core::setRow(!row, !value);
    } else if( 3 == _rotate ) {
        core::setCol(row, !value);
    } else { // If _rotate == 0
        core::setRow(row, value);
    }
}

// Set all LEDs in a column to a new state
void LedMatrix::set(const Col &col, buint8_t value)
{
    // Set the value to the desired position depending on the seted rotation value
    if( 1 == _rotate ) {
        core::setRow(col, !value);
    } else if( 2 == _rotate ) {
        core::setCol(!col, !value);
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
buint8_t LedMatrix::get(const Row &row) const
{
    // Set the value to the desired position depending on the seted rotation value
    if( 1 == _rotate ) {
        return core::getCol(!row);
    } else if( 2 == _rotate ) {
        return !core::getRow(!row);
    } else if( 3 == _rotate ) {
        return !core::getCol(row);
    } else { // If _rotate == 0
        return core::getRow(row);
    }
}

// Get the values on colomn of LED-matrix
buint8_t LedMatrix::get(const Col &col) const
{
    // Set the value to the desired position depending on the seted rotation value
    if( 1 == _rotate ) {
        return !core::getRow(col);
    } else if( 2 == _rotate ) {
        return !core::getCol(!col);
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
buint8_t LedMatrix::shiftUp(buint8_t value)
{
    buint8_t rez = getRow(0);
    for(uint8_t i = 0; i < _size-1; i++) {
        setRow(i, getRow(i+1));
    }
    setRow(_size-1, value);
    return rez;
}

buint8_t LedMatrix::shiftDown(buint8_t value)
{
    buint8_t rez = getRow(_size-1);
    for(uint8_t i = _size-1; i > 0; i--) {
        setRow(i, getRow(i-1));
    }
    setRow(0, value);
    return rez;
}

buint8_t LedMatrix::shiftLeft(buint8_t value)
{
    buint8_t rez = getCol(0);
    for(uint8_t i = 0; i < _size-1; i++) {
        setCol(i, getCol(i+1));
    }
    setCol(_size-1, value);
    return rez;
}

buint8_t LedMatrix::shiftRight(buint8_t value)
{
    buint8_t rez = getCol(_size-1);
    for(uint8_t i = _size-1; i > 0; i--) {
        setCol(i, getCol(i-1));
    }
    setCol(0, value);
    return rez;
}


