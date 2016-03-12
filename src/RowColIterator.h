/*
 *
 * Makes rows and colomns of LedMatrix iterable
 * Helper class.
 *
 *  @author   Valeriy V Dmitriev aka valmat <ufabiz@gmail.com>, http://valmat.ru/
 *  @licenses MIT https://opensource.org/licenses/MIT
 *  @repo     https://github.com/valmat/LedMatrix
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

