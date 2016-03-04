#pragma once


template<uint8_t maxRows>
class Row {
public:
    // Constructor
    Row(uint8_t nom) : 
        // If out of matrix range
        _valid(nom >= 0 && nom < maxRows), 
        _nom(_valid ? nom : 0) 
    {}

    // Copy constructor
    Row( const Row& ) = default;

    // Move constructor
    Row ( Row && ) = default;

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


template<uint8_t maxRows>
using Col = Row<maxRows>;

