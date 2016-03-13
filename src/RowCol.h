/*
 *
 * RowCol is a generic name for the two classes. Row and Col.
 * These classes are for convenient control the rows and columns
 * of the LED matrix using thr LedMatrix class.
 *
 *  @author   Valeriy V Dmitriev aka valmat <ufabiz@gmail.com>, http://valmat.ru/
 *  @licenses MIT https://opensource.org/licenses/MIT
 *  @repo     https://github.com/valmat/LedMatrix
 *
 */

#pragma once

// Forward declaration
template<uint8_t maxRows, bool isRow>
struct RowColIterator;


template<uint8_t maxRows, bool isRow>
class RowCol {
public:
    // Constructor
    constexpr RowCol(uint8_t nom) : 
        // If out of matrix range
        _valid(nom < maxRows), 
        _nom(_valid ? nom : 0) 
    {}

    // Copy & Move constructors
    constexpr RowCol( const RowCol& that) :
        _valid(that._valid),
        _nom(that._nom)
    {}
    constexpr RowCol ( RowCol&& that) :
        _valid(that._valid),
        _nom(that._nom)
    {}

    // if the Row/Col object is valid
    constexpr bool isValid() const
    {
        return _valid;
    }

    // Cast to a number
    constexpr operator uint8_t () const
    {
        return _nom;
    }

    // Cast to a ... RowCol
    // Row -> Col, Col -> Row
    template<bool B>
    constexpr operator RowCol<maxRows, B> () const
    {
        return RowCol<maxRows, B>(_nom);
    }

    // Reverse operator
    constexpr RowCol operator!() const
    {
        return maxRows - 1 - _nom;
    }

    //
    // Iterator operators
    // Folowing operators needs to RowColIterator
    //

    //  Increment position (pre-increment)
    RowCol &operator++()
    {
        ++_nom;
        return *this;
    }
    
    //  Increment position (post-increment)
    RowCol operator++(int)
    {
        RowCol copy(*this);
        ++(*this);
        return copy;
    }
    
    //  Decrement position (pre-decrement)
    RowCol &operator--()
    {
        --_nom;
        return *this;
    }

    //  Increment position (post-decrement)
    RowCol operator--(int)
    {
        RowCol copy(*this);
        --(*this);
        return copy;
    }
    
    //  Compare with other iterator
    constexpr bool operator==(const RowCol &rhs) const
    {
        return (_nom == rhs._nom);
    }

    //  Compare with other iterator
    constexpr bool operator!=(const RowCol &rhs) const
    {
        return (_nom != rhs._nom);
    }

    // Dereference as a current object
    constexpr const RowCol &operator*() const
    {
        return *this;
    }
    
private:
    // Novalidateble constructor
    constexpr RowCol(uint8_t nom, bool valid) :  _valid(valid), _nom(nom) {}

    const bool _valid = true;
    uint8_t _nom;

    template<uint8_t __maxRows, bool __isRow>
    friend struct RowColIterator;
};


using Row = RowCol<8, true>;
using Col = RowCol<8, false>;

