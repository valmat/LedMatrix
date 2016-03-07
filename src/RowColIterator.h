/*
 *
 * Makes rows and colomns of LedMatrix iterable
 * Helper class.
 *
 */

#pragma once

#include "RowCol.h"

template<uint8_t maxRows, bool isRow>
struct RowColIterator {
    // Constructor
    constexpr RowColIterator() {}

    constexpr uint8_t size() const
    {
        return maxRows;
    }

    // Make iterable
    constexpr RowCol<maxRows, isRow> begin() const
    {
        return RowCol<maxRows, isRow>(0, true);
    }
    constexpr RowCol<maxRows, isRow> end() const
    {
        return RowCol<maxRows, isRow>(maxRows, false);
    }
};

using RowsIterator = RowColIterator<8, true>;
using ColsIterator = RowColIterator<8, false>;

