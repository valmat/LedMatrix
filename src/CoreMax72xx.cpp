#include "CoreMax72xx.h"


//the opcodes for the MAX7221 and MAX7219
#define OP_NOOP   0
#define OP_DIGIT0 1
#define OP_DIGIT1 2
#define OP_DIGIT2 3
#define OP_DIGIT3 4
#define OP_DIGIT4 5
#define OP_DIGIT5 6
#define OP_DIGIT6 7
#define OP_DIGIT7 8
#define OP_DECODEMODE  9
#define OP_INTENSITY   10
#define OP_SCANLIMIT   11
#define OP_SHUTDOWN    12
#define OP_DISPLAYTEST 15


// Constructor
CoreMax72xx::CoreMax72xx(Pino data, Pino clk, Pino cs, uint8_t ind, uint8_t cascadeSize) :
    _mosi(data, Pino::Mode::out),
    _clk(clk, Pino::Mode::out),
    _cs(cs, Pino::Mode::out),
    _index(ind),
    _cascadeSize(cascadeSize)
{
    _cs.on();

    _spiTransfer(OP_DISPLAYTEST, 0);
    //scanlimit is set to max on startup
    _setScanLimit(_limit - 1);
    //decode is done in source
    _spiTransfer(OP_DECODEMODE, 0);

    //To clear display on startup
    // And fill the _status array by zeros
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
    for(auto &row: RowsIterator()) {
        _status[row] = 0;
        _spiTransfer(row + 1, _status[row]);
    }
}

// Switch all LEDs on the display to on.
void CoreMax72xx::fill()
{
    for(auto &row: RowsIterator()) {
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
    uint8_t val = 0b10000000 >> col;

    if(state)
        _status[row] = _status[row] | val;
    else {
        val = ~val;
        _status[row] = _status[row] & val;
    }
    _spiTransfer(row + 1, _status[row]);
}

// Set all LEDs in a row to a new state
void CoreMax72xx::setRow(const Row &row, uint8_t value)
{
    _status[row] = value;
    _spiTransfer(row + 1, _status[row]);
}

// Set all LEDs in a column to a new state
void CoreMax72xx::setCol(const Col &col, uint8_t value)
{
    uint8_t val;
    for(auto &row: RowsIterator()) {
        val = value >> !row;
        val = val & 1;
        set(row, col, val);
    }
}

// Get state of LED point on matrix
bool CoreMax72xx::get(const Row &row, const Col &col) const
{
    // Binary position of colomn
    uint8_t pos = (1 << !col);
    // Return binary value at the intersection of row and column
    return _status[row] & pos;
}

// Get the values on row of LED-matrix
uint8_t CoreMax72xx::getRow(const Row &row) const
{
    return _status[row];
}

// Get the values on colomn of LED-matrix
uint8_t CoreMax72xx::getCol(const Col &col) const
{
    uint8_t rez = 0;
    for(auto &row: RowsIterator()) {
        if(get(row, col)) {
            rez |= (1 << !row);
        }
    }
    return rez;
}



//
// Private methods:
//


// SPI transaction
void CoreMax72xx::_spiTransfer(volatile uint8_t opcode, volatile uint8_t data) const
{
    //Create an array with the data to shift out
    const uint8_t offset=_index * 2;
    const uint8_t maxbytes = _cascadeSize*2;

    // The array for shifting the data to the devices
    uint8_t _spidata[maxbytes];

    for(uint8_t i = 0; i < maxbytes; i++) {
        _spidata[i]=0;
    }
    
    //put our device data into the array
    _spidata[offset+1] = opcode;
    _spidata[offset]   = data;
    
    //enable the line 
    _cs.off();

    //Shift out the data
    for(uint8_t i = maxbytes; i > 0; i--) {
        _mosi.shiftOut(_clk, _spidata[i-1]);
    }

    //latch the data onto the display
    _cs.on();
}

void CoreMax72xx::_setScanLimit(uint8_t limit) const
{
    _spiTransfer(OP_SCANLIMIT, max(limit, _limit-1));
}