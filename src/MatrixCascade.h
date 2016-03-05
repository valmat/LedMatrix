/*
 *
 * MatrixCascade - is is my fork of LedControl lylbrary
 *
 */

#pragma once

#include <Pino.h>
#include "LedMatrix.h"

template<uint8_t CascadeSize>
class MatrixCascade {
public:
    /* 
     * Create a new controler 
     * Params :
     * dataPin		pin on the Arduino where data gets shifted out
     * clockPin		pin for the clock
     * csPin		pin for selecting the device 
     * numDevices	maximum number of devices that can be controled
     */
    MatrixCascade(Pino data, Pino clk, Pino cs)
    {
        for(uint8_t i = 0; i < CascadeSize; i++) {
            matrixes[i] = LedMatrix(data, clk, cs, i);
        }
    }


    /**
     *  Gets the number of devices attached to this MatrixCascade.
     *  @return uint8_t the number of devices on this MatrixCascade
     */
    constexpr uint8_t size()
    {
        return CascadeSize;
    }

    /**
     *  Array access operator
     *  This can be used for accessing arrays
     *  @param  index
     *  @return LedMatrix&
     */
    LedMatrix& get(uint8_t index)
    {
        //return 
    }

    /**
     *  Array access operator
     *  This can be used for accessing arrays
     *  @param  index
     *  @return Value
     */
    LedMatrix& operator[](uint8_t index)
    {
        return get(index);
    }


private :
    // Size of matrix (the length of the row and column of a square matrix)
    constexpr static uint8_t _matrixSize = 8;
    // The maximum number of matrices
    constexpr static uint8_t _matrixLimit = 8;

    LedMatrix matrixes[CascadeSize];
};



