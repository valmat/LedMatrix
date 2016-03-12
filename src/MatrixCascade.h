/*
 *
 * MatrixCascade is a class to easy control LED matrixes that are combined in a cascade.
 *
 */

#pragma once

#include <Pino.h>
#include "LedMatrix.h"
#include "Traits.h"


template<uint8_t cascadeSize>
class MatrixCascade {
public:

    // Software-SPI Constructor
    // @param dataPin   pin on the Arduino where data gets shifted out
    // @param clockPin  pin for the clock
    // @param csPin     pin for selecting the device (chip select pin)
    MatrixCascade(Pino data, Pino clk, Pino cs)
    {
        // Fill cascade on startup
        for(uint8_t i = 0; i < cascadeSize; i++) {
            matrixes[i] = LedMatrix(data, clk, cs, i, cascadeSize);
        }
    }

    // HardWare-SPI Constructor
    // @param csPin        pin for selecting the device   (CS -- chip select pin)
    MatrixCascade(Pino cs)
    {
        // Fill cascade on startup
        for(uint8_t i = 0; i < cascadeSize; i++) {
            matrixes[i] = LedMatrix(cs, i, cascadeSize, true);
        }
    }

    // A template constructor that allows to join several cascades in one
    template <uint8_t N0, uint8_t ...Ns>
    MatrixCascade(MatrixCascade<N0>&& arg0, MatrixCascade<Ns>&& ...args)
    {
        static_assert(cascadeSize == SumTrait<N0, Ns...>::sum, 
        "Inconsistency sizes. cascadeSize should be the sum of the cascadeSize of its arguments.");
        
        _fillBySubCascades(0, std::move(arg0), std::move(args)...);
    }

    // Returns the number of devices on this MatrixCascade
    constexpr uint8_t size() const
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

    // Switch all LEDs on all displays to on.
    void fill()
    {
        for(auto &matrix: *this) {
            matrix.fill();
        }
    }

    // Invert all points of all matrixes
    void invert()
    {
        for(auto &matrix: *this) {
            matrix.invert();
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
    
    // Helper functions for combining multiple MatrixCascade to one
    template <uint8_t N0, uint8_t ...Ns>
    void _fillBySubCascades(uint8_t offset, MatrixCascade<N0>&& arg0, MatrixCascade<Ns>&& ...args)
    {
        for (uint8_t i = 0; i < N0; ++i)
        {
            matrixes[offset + i] = std::move(arg0.matrixes[i]);
            matrixes[offset + i].index(offset + i);
        }
        _fillBySubCascades(N0, std::move(args)...);
    }
    template <uint8_t N0>
    void _fillBySubCascades(uint8_t offset, MatrixCascade<N0>&& arg0)
    {
        for (uint8_t i = 0; i < N0; ++i)
        {
            matrixes[offset + i] = std::move(arg0.matrixes[i]);
            matrixes[offset + i].index(offset + i);
        }
    }


private:
    
    // Size of matrix (the length of the row and column of a square matrix)
    constexpr static uint8_t _matrixSize = 8;
    
    // The maximum number of matrices
    constexpr static uint8_t _matrixLimit = 8;

    // Cascade array
    LedMatrix matrixes[cascadeSize];

    
    template<uint8_t ___size>
    friend class MatrixCascade;
};

template <uint8_t N0, uint8_t ...Ns>
constexpr MatrixCascade< SumTrait<N0, Ns...>::sum >
combineCascades(MatrixCascade<N0>&& arg0, MatrixCascade<Ns>&& ...args)
{
    return MatrixCascade< SumTrait<N0, Ns...>::sum >(std::move(arg0), std::move(args)...);
}