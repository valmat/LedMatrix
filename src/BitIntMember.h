/*
 *
 * BitIntMember is an auxiliary type that allows to make BigInt array-accessible and iterable
 *
 *  @author   Valeriy V Dmitriev aka valmat <ufabiz@gmail.com>, http://valmat.ru/
 *  @licenses MIT https://opensource.org/licenses/MIT
 *  @repo     https://github.com/valmat/LedMatrix
 *
 */

#pragma once

// Forward declaration
 template<typename T, uint8_t  _size>
class BitInt;


template<typename T, uint8_t  _size>
class BitIntMember
{
public:
    BitIntMember(uint8_t index, BitInt<T, _size> &val) :
        _val(val),
        _index(index)
    {}

    BitIntMember& operator=(bool state)
    {
        _val.set(_index, state);
        return *this;
    }

    operator bool () const
    {
        return _val.get(_index);
    }

    //
    // Iterator operators
    //

    //  Increment position (pre-increment)
    BitIntMember &operator++()
    {
        ++_index;
        return *this;
    }
    
    //  Increment position (post-increment)
    BitIntMember operator++(int)
    {
        BitIntMember copy(*this);
        ++(*this);
        return copy;
    }
    
    //  Decrement position (pre-decrement)
    BitIntMember &operator--()
    {
        --_index;
        return *this;
    }

    //  Increment position (post-decrement)
    BitIntMember operator--(int)
    {
        BitIntMember copy(*this);
        --(*this);
        return copy;
    }

    //  Compare with other iterator
    bool operator==(const BitIntMember<T, _size> &rhs) const
    {
        return (_val == rhs._val && _index == rhs._index);
    }

    //  Compare with other iterator
    bool operator!=(const BitIntMember<T, _size> &rhs) const
    {
        return !(*this == rhs);
    }

    // Dereference as a current object
    bool operator*() const
    {
        return _val.get(_index);
    }

private:
    BitInt<T, _size> &_val;
    uint8_t _index;
};

