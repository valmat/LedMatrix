#include "LedMatrix.h"

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

LedMatrix::LedMatrix(Pino data, Pino clk, Pino cs, uint8_t ind, uint8_t cascadeSize) :
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
void LedMatrix::shutdown() const
{
    _spiTransfer(OP_SHUTDOWN,0);
}

// Set the wakeup mode for the device
void LedMatrix::wakeup() const
{
    _spiTransfer(OP_SHUTDOWN,1);
}

// Set the brightness of the display.
void LedMatrix::setIntensity(uint8_t intensity) const
{
    _spiTransfer(OP_INTENSITY, intensity % _maxIntensity);
}

// Switch all LEDs on the display to off.
void LedMatrix::clear()
{
    for(auto &row: _rows) {
        _status[row] = 0;
        _spiTransfer(row + 1, _status[row]);
    }
}

// Switch all LEDs on the display to on.
void LedMatrix::fill()
{
    for(auto &row: _rows) {
        _status[row] = B11111111;
        _spiTransfer(row + 1, _status[row]);
    }
}


void LedMatrix::set(Row row, Col col, bool state)
{
    // Set the value to the desired position depending on the seted rotation value
    if( 1 == _rotate ) {
        _set(col, _size - 1 - row, state);
    } else if( 2 == _rotate ) {
        _set(_size - 1 - row, _size - 1 - col, state);
    } else if( 3 == _rotate ) {
        _set(_size - 1 - col, row, state);
    } else { // If _rotate == 0
        _set(row, col, state);
    }
}

// Binary inverting (helper function)
static uint8_t _binInvert(uint8_t v)
{
    uint8_t r = 0;
    uint8_t pos = 1;
    uint8_t x, s = 8, s2 = 4; // s = sizeof(uint8_t)

    for(uint8_t i = 0; i < s2; i++) {
        x = v & (pos << i);
        r = r | ( x << (s-2*i-1) );
    }
    for(uint8_t i = 0; i < s2; i++) {
        x = v & ( pos << (s - i - 1) );
        r = r | ( x >> (s-2*i-1) );
    }
    return r;
}

// Set all LEDs in a row to a new state
void LedMatrix::set(Row row, uint8_t value)
{
    // Set the value to the desired position depending on the seted rotation value
    if( 1 == _rotate ) {
        _setCol(_size - 1 - row, value);
    } else if( 2 == _rotate ) {
        _setRow(_size - 1 - row, _binInvert(value));
    } else if( 3 == _rotate ) {
        _setCol(row, _binInvert(value));
    } else { // If _rotate == 0
        _setRow(row, value);
    }
}

// Set all LEDs in a column to a new state
void LedMatrix::set(Col col, uint8_t value)
{
    // Set the value to the desired position depending on the seted rotation value
    if( 1 == _rotate ) {
        _setRow(col, _binInvert(value));
    } else if( 2 == _rotate ) {
        _setCol(_size - 1 - col, _binInvert(value));
    } else if( 3 == _rotate ) {
        _setRow(_size - 1 - col, value);
    } else { // If _rotate == 0
        _setCol(col, value);
    }
}

void LedMatrix::_set(uint8_t row, uint8_t col, bool state)
{
    uint8_t val = B10000000 >> col;

    if(state)
        _status[row] = _status[row]|val;
    else {
        val = ~val;
        _status[row] = _status[row]&val;
    }
    _spiTransfer(row + 1, _status[row]);
}

void LedMatrix::_setRow(uint8_t row, uint8_t value)
{
    _status[row] = value;
    _spiTransfer(row + 1, _status[row]);
}

void LedMatrix::_setCol(uint8_t col, uint8_t value)
{
    uint8_t val;
    for(auto &row: _rows) {
        val = value >> (_size - 1 - row);
        val = val & 1;
        _set(row, col, val);
    }
}

// Allows to initialize the values of all points of the matrix
void LedMatrix::set(uint8_t arr[])
{
    for(auto &row: _rows) {
        set(row, arr[row]);;
    }
}

// Get state of LED point on matrix
bool LedMatrix::get(Row row, Col col)
{
    // Calculate binary position of colomn
    uint8_t pos = (1 << (_size - 1 - col));
    // Return binary value at the intersection of row and column
    return _status[row] & pos;
}

// Invert all points of matrix
void LedMatrix::invert()
{
    for(auto &row: _rows) {
        invert(row);
    }
}

// Invert current point on matrix
void LedMatrix::invert(Row row, Col col)
{
    _set(row, col, !get(row, col));
}

// Invert row on matrix
void LedMatrix::invert(Row row)
{
    _status[row] = ~_status[row];
    _spiTransfer(row + 1, _status[row]);
}

// Invert colomn on matrix
void LedMatrix::invert(Col col)
{
    for(auto &row: _rows) {
        invert(row, col);
    }
}

void LedMatrix::_spiTransfer(volatile uint8_t opcode, volatile uint8_t data) const
{
    //Create an array with the data to shift out
    uint8_t offset=_index * 2;
    uint8_t maxbytes = _cascadeSize*2;

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

void LedMatrix::_setScanLimit(uint8_t limit) const
{
    _spiTransfer(OP_SCANLIMIT, max(limit, _limit-1));
}
