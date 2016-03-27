/*
 *
 * DirectPin this is a helper class to direct manipulation pins bypassing additional checks.
 * The purpose of this class is to increase speed by eliminating unnecessary in this case checks.
 * Not all methods are implemented, but only those that are needed within the library.
 *
 *  @author   Valeriy V Dmitriev aka valmat <ufabiz@gmail.com>
 *  @author   ...
 *  @licenses MIT https://opensource.org/licenses/MIT
 *  @repo     https://github.com/valmat/LedMatrix
 *
 */

#pragma once

#include "Arduino.h"

class DirectPin
{
public:

    // Constructor
    DirectPin(uint8_t pinNom) :
        _baseReg( portInputRegister( digitalPinToPort(pinNom) ) ),
        _bitMask( digitalPinToBitMask(pinNom) )
    {}

    // Сonstructor initializes the pins as a mode
    DirectPin(uint8_t pinNom, uint8_t mode) :
        DirectPin(pinNom)
    {
        setMode(mode);
    }

    // Empty constructor
    DirectPin() :
        _baseReg(nullptr),
        _bitMask(0)
    {}

    // Directly set mode as `OUTPUT`
    void modeOut(bool mode)
    {
        *(_baseReg + 1) |= _bitMask;
    }

    // Directly set mode as `INPUT`
    void modeIn()
    {
        *(_baseReg + 1) &= ~_bitMask;
    }

    // Directly set mode as `OUTPUT`
    void modeOut()
    {
        *(_baseReg + 1) |= _bitMask;
    }

    // Directly set mode
    void setMode(uint8_t mode)
    {
        if(OUTPUT == mode) {
            modeOut();
        } else {
            modeIn();
        }
    }

    // Directly turn the pin to `HIGH` voltage level
    void on() const
    {
        *(_baseReg + 2) |= _bitMask;
    }

    // Directly turn the pin off by making the voltage level `LOW`
    void off() const
    {
        *(_baseReg + 2) &= ~_bitMask;
    }

    // turn the pin to a value
    void turn(bool value) const
    {
        if(value) {
            on();
        } else {
            off();
        }
    }

    // Shifts out a byte of data one bit at a time
    // bitOrder == MSBFIRST
    void shiftOut(const DirectPin &clock, uint8_t val) const
    {
        for(uint8_t i = 0; i < 8; ++i) {
            turn(val & (1 << (7 - i)));
            clock.on();
            clock.off();
        }
    }

    // Shifts out a byte of data one bit at a time
    // bitOrder == LSBFIRST
    void shiftOutRe(const DirectPin &clock, uint8_t val) const
    {
        for(uint8_t i = 0; i < 8; ++i) {
            turn(val & (1 << i));

            clock.on();
            clock.off();
        }
    }

private:
    volatile uint8_t *_baseReg;
    uint8_t _bitMask;
};
