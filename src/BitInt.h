/*
 *
 * BitInt is a helper type for use the numeric types as a binary arrays
 *
 *  @author   Valeriy V Dmitriev aka valmat <ufabiz@gmail.com>, http://valmat.ru/
 *  @licenses MIT https://opensource.org/licenses/MIT
 *  @repo     https://github.com/valmat/LedMatrix
 *
 */

#pragma once
#include "BitIntMember.h"

template<typename T, uint8_t  _size = 8 * sizeof(T)>
class BitInt {
public:
    
    // Constructors
    constexpr BitInt(T value) : _value(value) {}
    constexpr BitInt() : _value(0) {}

    // Get size
    constexpr uint8_t size () const
    {
        return _size;
    }

    // Cast to a number
    constexpr operator T () const
    {
        return _value;
    }

    constexpr bool get(uint8_t index) const
    {
        return _value & (1 << (_size - 1 - (index % _size)));
    }


    BitInt& set(uint8_t index, bool state)
    {
        T val = (1 << (_size - 1 - index % _size));
        _value = state ? (_value | val) : (_value & ~val);
        return *this;
    }
    
    // Array access operator
    constexpr bool operator[](uint8_t index) const
    {
        return get(index);
    }

    // Array access operator
    BitIntMember<T, _size> operator[](uint8_t index)
    {
        return BitIntMember<T, _size>(index, *this);
    }

    // Cast to a number
    constexpr T get () const
    {
        return _value;
    }

    // Reverse operator
    // Binary order inverting transposition
    BitInt operator!() const
    {
        T rez = 0;
        uint8_t pos = 1;
        T x; 
        uint8_t s = _size, s2 = _size / 2;

        for(uint8_t i = 0; i < s2; i++) {
            x = _value & (pos << i);
            rez = rez | ( x << (s-2*i-1) );
        }
        for(uint8_t i = 0; i < s2; i++) {
            x = _value & ( pos << (s - i - 1) );
            rez = rez | ( x >> (s-2*i-1) );
        }
        return rez;
    }


    //  Increment position (pre-increment)
    BitInt &operator++()
    {
        ++_value;
        return *this;
    }
    
    //  Increment position (post-increment)
    BitInt operator++(int)
    {
        BitInt copy(*this);
        ++(*this);
        return copy;
    }
    
    //  Decrement position (pre-decrement)
    BitInt &operator--()
    {
        --_value;
        return *this;
    }

    //  Increment position (post-decrement)
    BitInt operator--(int)
    {
        BitInt copy(*this);
        --(*this);
        return copy;
    }

    // Make iterable
    constexpr const BitIntMember<T, _size> begin() const
    {
        return BitIntMember<T, _size>(0, *this);
    }
    constexpr const BitIntMember<T, _size> end() const
    {
        return BitIntMember<T, _size>(_size, *this);
    }

    
    BitIntMember<T, _size> begin()
    {
        return BitIntMember<T, _size>(0, *this);
    }
    BitIntMember<T, _size> end()
    {
        return BitIntMember<T, _size>(_size, *this);
    }

private:

    T _value;
};

// Types predefinition
using buint8_t  = BitInt<uint8_t>;
using buint16_t = BitInt<uint16_t>;
using buint32_t = BitInt<uint32_t>;
using buint64_t = BitInt<uint64_t>;

using bint8_t  = BitInt<int8_t>;
using bint16_t = BitInt<int16_t>;
using bint32_t = BitInt<int32_t>;
using bint64_t = BitInt<int64_t>;


