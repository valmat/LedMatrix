/*
 *
 * MatrixCascade - is is my fork of LedControl lylbrary
 *
 */

#pragma once

#include <Pino.h>
#include "LedMatrix.h"

template<uint8_t cascadeSize>
class MatrixCascade {
public:
    
    // Constructor
    // @param dataPin   pin on the Arduino where data gets shifted out
    // @param clockPin  pin for the clock
    // @param csPin     pin for selecting the device 
    MatrixCascade(Pino data, Pino clk, Pino cs)
    {
        for(uint8_t i = 0; i < cascadeSize; i++) {
            matrixes[i] = LedMatrix(data, clk, cs, i, cascadeSize);
        }
    }

    // Returns the number of devices on this MatrixCascade
    constexpr uint8_t size()
    {
        return cascadeSize;
    }

    // This can be used for accessing to the LedMatrix arrays
    // @param  index -- index of matrix in cascade
    LedMatrix& get(uint8_t index)
    {
        return matrixes[ ( (index >=0 && index < cascadeSize) ? index : 0 ) ];
    }

    // Array access operator
    // This can be used for accessing to the LedMatrix arrays
    // @param  index -- index of matrix in cascade
    LedMatrix& operator[](uint8_t index)
    {
        return get(index);
    }

    // Make iterable
    LedMatrix* begin()
    {
        return matrixes;
    }
    LedMatrix* end()
    {
        return matrixes + cascadeSize;
    }


private:
    
    // Size of matrix (the length of the row and column of a square matrix)
    constexpr static uint8_t _matrixSize = 8;
    
    // The maximum number of matrices
    constexpr static uint8_t _matrixLimit = 8;

    // Cascadec array
    LedMatrix matrixes[cascadeSize];
};



