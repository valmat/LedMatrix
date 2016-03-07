/*
 *
 * MatrixCascade is a class to easy control LED matrixes that are combined in a cascade.
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
        // Fill cascade on startup
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

    //
    // Group methods:
    //

    // Set the shutdown (power saving) mode for all devices
    void shutdown() const
    {
        for(auto &matrix: *this) {
            matrix.shutdown();
        }
    }

    // Set the wakeup mode for all devices
    void wakeup() const
    {
        for(const auto &matrix: *this) {
            matrix.wakeup();
        }
    }

    // Set the brightness of all displays.
    // @param intensity the brightness of the display. (0..15)
    void setIntensity(uint8_t intensity) const
    {
        for(const auto &matrix: *this) {
            matrix.setIntensity(intensity);
        }
    }

    // Switch all LEDs on all displays to off. 
    void clear()
    {
        for(auto &matrix: *this) {
            matrix.clear();
        }
    }

    // How many times to rotate all matrixes clockwise
    // @param From 0 to 3
    void setRotation(uint8_t times = 1)
    {
        for(auto &matrix: *this) {
            matrix.setRotation(times);
        }
    }

    // Reset rotation flag for all matrixes to default
    void resetRotation()
    {
        for(auto &matrix: *this) {
            matrix.resetRotation();
        }
    }

    //
    // Iterator methods:
    //

    // Make iterable
    LedMatrix* begin()
    {
        return matrixes;
    }
    LedMatrix* end()
    {
        return matrixes + cascadeSize;
    }
    const LedMatrix* begin() const
    {
        return matrixes;
    }
    const LedMatrix* end() const
    {
        return matrixes + cascadeSize;
    }


private:
    
    // Size of matrix (the length of the row and column of a square matrix)
    constexpr static uint8_t _matrixSize = 8;
    
    // The maximum number of matrices
    constexpr static uint8_t _matrixLimit = 8;

    // Cascade array
    LedMatrix matrixes[cascadeSize];
};



