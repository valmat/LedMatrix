#pragma once

#include "MatrixCascade.h"

template<uint8_t cascadeSize>
class randomMovement {
public:
    // Constructor
    randomMovement(MatrixCascade<cascadeSize> &cascade, uint8_t randPin) : 
        _cascade(cascade)
    {
        randomSeed(analogRead(randPin) + millis());
        _x = random(maxX);
        _y = random(maxY);
        //_cascade.clear();
    }

    // Copy & Move constructors
    randomMovement( const randomMovement& ) = default;
    randomMovement ( randomMovement && ) = default;

    void on()
    {
        uint8_t x = _x%maxY;
        uint8_t i = (_x - x)/maxY;
        _cascade[i].on(x, _y);
    }
    void off()
    {
        uint8_t x = _x%maxY;
        uint8_t i = (_x - x)/maxY;
        _cascade[i].off(x, _y);
    }

    void move()
    {
        _x = move(_x, maxX);
        _y = move(_y, maxY);
    }
private:
    uint8_t move(uint8_t v, uint8_t max)
    {
        int8_t dv = 1-random(0, 3);
        
        if(v == 0 && dv != 0) v++;
        else if(v == (max-1) && dv != 0) v--;
        else v += dv;
        return v;
    }

private:
    MatrixCascade<cascadeSize> &_cascade;
    uint8_t _x = 0;
    uint8_t _y = 0;
    constexpr static uint8_t maxX = 8 * cascadeSize;
    constexpr static uint8_t maxY = 8;
};


