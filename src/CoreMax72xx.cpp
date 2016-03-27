/*
 *
 * CoreMax72xx this is the class for direct interaction with a controller MAX72xx
 *
 *  @author   Valeriy V Dmitriev aka valmat <ufabiz@gmail.com>, http://valmat.ru/
 *  @licenses MIT https://opensource.org/licenses/MIT
 *  @repo     https://github.com/valmat/LedMatrix
 *
 *
 *  Software SPI and main core functionality implemented
 *  by Eberhard Fahle aka wayoda <e.fahle@wayoda.org>
 *  https://github.com/wayoda/LedControl
 *  http://wayoda.github.io/LedControl/
 *
 */
 

#include "CoreMax72xx.h"
#include <SPI.h>

//the opcodes for the MAX7221 and MAX7219
namespace
{
    constexpr uint8_t OP_NOOP        = 0;
    constexpr uint8_t OP_DIGIT0      = 1;
    constexpr uint8_t OP_DIGIT1      = 2;
    constexpr uint8_t OP_DIGIT2      = 3;
    constexpr uint8_t OP_DIGIT3      = 4;
    constexpr uint8_t OP_DIGIT4      = 5;
    constexpr uint8_t OP_DIGIT5      = 6;
    constexpr uint8_t OP_DIGIT6      = 7;
    constexpr uint8_t OP_DIGIT7      = 8;
    constexpr uint8_t OP_DECODEMODE  = 9;
    constexpr uint8_t OP_INTENSITY   = 10;
    constexpr uint8_t OP_SCANLIMIT   = 11;
    constexpr uint8_t OP_SHUTDOWN    = 12;
    constexpr uint8_t OP_DISPLAYTEST = 15;
}

// Software-SPI constructor
CoreMax72xx::CoreMax72xx(uint8_t data, uint8_t clk, uint8_t cs, uint8_t ind, uint16_t cascadeSize) :
    _pins(data, clk, cs),
    _index(ind),
    _cascadeSize(cascadeSize)
{
    _initialize();
}

// HardWare-SPI constructor
CoreMax72xx::CoreMax72xx(uint8_t cs, uint8_t ind, uint16_t cascadeSize, bool) :
    _pins(cs),
    _index(ind),
    _cascadeSize(cascadeSize),
    _isHardwareSPI(true)
{
    // initialize SPI:
    SPI.setBitOrder(MSBFIRST);
    SPI.setDataMode(SPI_MODE0);
    SPI.begin();

    _initialize();
}

// Initialize the chip
void CoreMax72xx::_initialize()
{
    _pins.latch();

    _spiTransfer(OP_DISPLAYTEST, 0);
    //scanlimit is set to max on startup
    _setScanLimit(_limit - 1);
    //decode is done in source
    _spiTransfer(OP_DECODEMODE, 0);

    // Clear display on startup
    // and fill the _status array by zeros
    clear();
    //we go into wakeup-mode on startup
    wakeup();
}


// Set the shutdown (power saving) mode for the device
void CoreMax72xx::shutdown() const
{
    _spiTransfer(OP_SHUTDOWN, 0);
}

// Set the wakeup mode for the device
void CoreMax72xx::wakeup() const
{
    _spiTransfer(OP_SHUTDOWN, 1);
}

// Set the brightness of the display.
void CoreMax72xx::setIntensity(uint8_t intensity) const
{
    _spiTransfer(OP_INTENSITY, intensity % _maxIntensity);
}

// Switch all LEDs on the display to off.
void CoreMax72xx::clear()
{
    for(auto &row: _rows) {
        _status[row] = 0;
        _spiTransfer(row + 1, _status[row]);
    }
}

// Switch all LEDs on the display to on.
void CoreMax72xx::fill()
{
    for(auto &row: _rows) {
        _status[row] = 0b11111111;
        _spiTransfer(row + 1, _status[row]);
    }
}

//
// Setters:
//

// Set the status of a single LED.
void CoreMax72xx::set(const Row &row, const Col &col, bool state)
{
    _status[row][col] = state;
    _spiTransfer(row + 1, _status[row]);
}

// Set all LEDs in a row to a new state
void CoreMax72xx::setRow(const Row &row, buint8_t value)
{
    _status[row] = value;
    _spiTransfer(row + 1, _status[row]);
}

// Set all LEDs in a column to a new state
void CoreMax72xx::setCol(const Col &col, buint8_t value)
{
    for(auto &row: _rows) {
        set(row, col, value[row]);
    }
}

//
// Getters:
//

// Get state of LED point on matrix
bool CoreMax72xx::get(const Row &row, const Col &col) const
{
    // Return binary value at the intersection of row and column
    return _status[row][col];
}

// Get the values on row of LED-matrix
buint8_t CoreMax72xx::getRow(const Row &row) const
{
    return _status[row];
}

// Get the values on colomn of LED-matrix
buint8_t CoreMax72xx::getCol(const Col &col) const
{
    buint8_t rez = 0;
    for(auto &row: _rows) {
        rez[row] = get(row, col);
    }
    return rez;
}

//
// Private methods:
//

// SPI transaction
void CoreMax72xx::_spiTransfer(uint8_t opcode, uint8_t data) const
{
    //Create an array with the data to shift out
    const uint8_t offset=_index * 2;
    const uint16_t maxbytes = _cascadeSize * 2;

    // The array for shifting the data to the devices
    uint8_t _spidata[maxbytes];

    for(uint8_t i = 0; i < maxbytes; i++) {
        _spidata[i]=0;
    }
    
    //put our device data into the array
    _spidata[offset+1] = opcode;
    _spidata[offset]   = data;
    
    //enable the line 
    _pins.enable();

    //Shift out the data
    if(_isHardwareSPI) {
        SPI.beginTransaction(SPISettings(100000000, MSBFIRST, SPI_MODE0));
        for(uint8_t i = maxbytes; i > 0; i--) {
            SPI.transfer(_spidata[i-1]);
        }
        SPI.endTransaction();
    } else {
        for(uint8_t i = maxbytes; i > 0; i--) {
            // Software SPI transfer
            _pins.transfer(_spidata[i-1]);
        }
    }

    //latch the data onto the display
    _pins.latch();
}


void CoreMax72xx::_setScanLimit(uint8_t limit) const
{
    _spiTransfer(OP_SCANLIMIT, max(limit, _limit-1));
}