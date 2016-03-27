/*
 *
 * DirectInteract this is a helper class to direct interaction with a set of Arduino pins.
 *
 *  @author    Valeriy V Dmitriev aka valmat <ufabiz@gmail.com>
 *  @coauthor  Nikolai Tikhonov aka Dragon_Knight <dubki4132@mail.ru>, https://vk.com/globalzone_edev
 *  @licenses  MIT https://opensource.org/licenses/MIT
 *  @repo      https://github.com/valmat/LedMatrix
 *
 */

#pragma once

#include "DirectPin.h"

class DirectInteract
{
public:
    DirectInteract(uint8_t dataPin, uint8_t clockPin, uint8_t csPin) :
        _data(dataPin, OUTPUT),
        _clock(clockPin, OUTPUT),
        _cs(csPin, OUTPUT)
    {}

    // Simplified constructor. For hardware SPI.
    DirectInteract(uint8_t csPin) :
        _cs(csPin, OUTPUT)
    {}

    // Empty constructor
    DirectInteract() {}
    
    // Enable the line
    void enable() const
    {
        _cs.off();
    }
    
    // Latch the data into chip
    void latch() const
    {
        _cs.on();
    }
    
    void transfer(uint8_t data) const
    {
        _data.shiftOut(_clock, data);
    }

private:

    // A pin on the Arduino where data gets shifted out (DIN).
    // Data is shifted out of this pin
    DirectPin _data;
    
    // The clock is signaled on this pin (CLK)
    DirectPin _clock;
    
    // This one is driven LOW for chip selection (CS)
    DirectPin _cs;
};
