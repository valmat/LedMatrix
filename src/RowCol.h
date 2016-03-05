#pragma once


template<uint8_t maxRows, bool isRow>
class RowCol {
public:
    // Constructor
    RowCol(uint8_t nom) : 
        // If out of matrix range
        _valid(nom >= 0 && nom < maxRows), 
        _nom(_valid ? nom : 0) 
    {}

    // Copy & Move constructors
    RowCol( const RowCol& that) :
        _valid(that._valid),
        _nom(that._nom)
    {}
    RowCol ( RowCol&& that) :
        _valid(that._valid),
        _nom(that._nom)
    {}


    bool isValid() const
    {
        return _valid;
    }

    operator uint8_t () const
    {
        return _nom;
    }

private:
    const uint8_t _nom;
    const bool _valid = true;
};


using Row = RowCol<8, true>;
using Col = RowCol<8, false>;

