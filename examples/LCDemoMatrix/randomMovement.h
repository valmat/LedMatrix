#pragma once

#include "LedMatrix.h"

class randomMovement {
public:
    // Constructor
    randomMovement(const LedMatrix &m, uint8_t randPin) : _m(m)
    {
        randomSeed(analogRead(randPin) + millis());
        _x = random(max+1);
        _y = random(max+1);
        _m.clear();
    }

    // Copy & Move constructors
    randomMovement( const randomMovement& ) = default;
    randomMovement ( randomMovement && ) = default;

    void on() const
    {
        _m.on(_x, _y);
    }
    void off() const
    {
        _m.off(_x, _y);
    }
    void clear() const
    {
        _m.clear();
    }

    void move()
    {
        _x = move(_x);
        _y = move(_y);
    }
private:
    uint8_t move(uint8_t v)
    {
        int8_t dv = 1-random(0, 3);
        
        if(v == 0 && dv != 0) v++;
        else if(v == max && dv != 0) v--;
        else v += dv;
        return v;
    }

private:
    const LedMatrix &_m;
    uint8_t _x = 0;
    uint8_t _y = 0;
    constexpr static uint8_t max = 7;
};


