

#include "LedMatrix.h"
#include "MatrixRotator.h"


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
   Serial.println( "LedMatrix::LedMatrix" );
    _cs.on();

    for(int i=0; i < _size; i++) 
        _status[i]=0x00;

    _spiTransfer(OP_DISPLAYTEST, 0);
    //scanlimit is set to max on startup
    _setScanLimit(_limit - 1);
    //decode is done in source
    _spiTransfer(OP_DECODEMODE, 0);

    //To clear display on startup
    clear();
    //we go into wakeup-mode on startup
    wakeup();
}

void LedMatrix::shutdown()
{
    Serial.println( "shutdown" );
    _spiTransfer(OP_SHUTDOWN,0);
}

void LedMatrix::wakeup()
{
    Serial.println( "wakeup" );
    _spiTransfer(OP_SHUTDOWN,1);
}

void LedMatrix::_setScanLimit(uint8_t limit)
{
    Serial.println( "_setScanLimit" );
    if(limit >= 0 && limit < _limit)
        _spiTransfer(OP_SCANLIMIT, limit);
}

void LedMatrix::setIntensity(uint8_t intensity)
{
    Serial.println( "setIntensity" );
    if(intensity >= 0 && intensity < _maxIntensity)	
        _spiTransfer(OP_INTENSITY, intensity);
}

void LedMatrix::clear() {
    Serial.println( "clear" );
    for(uint8_t i = 0; i < _size; i++) {
        _status[i] = 0;
        _spiTransfer(i + 1, _status[i]);
    }
}

void LedMatrix::set(Row row, Col col, bool state)
{
    MatrixRotator coords(row, col, _rotate, _size);
    _set(coords.row(), coords.col(), state);
}

void LedMatrix::setRow(Row row, uint8_t value)
{
    MatrixRotator coords(row, 0, _rotate, _size);
    if( coords.isSwaped() )
        _setCol(coords.col(), value);
    else
        _setRow(coords.row(), value);
}

void LedMatrix::setCol(Col col, uint8_t value)
{
    MatrixRotator coords(0, col, _rotate, _size);
    if( coords.isSwaped() )
        _setRow(coords.row(), value);
    else
        _setCol(coords.col(), value);
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
    for(int row = 0; row < _size; row++) {
        val = value >> (_size - 1 - row);
        val = val & 0x01;
        set(row, col, val);
    }
}

void LedMatrix::_spiTransfer(volatile uint8_t opcode, volatile uint8_t data)
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

    //Now shift out the data 
    for(uint8_t i = maxbytes; i > 0; i--) {
        _mosi.shiftOut(_clk, _spidata[i-1]);
    }

    //latch the data onto the display
    _cs.on();
}
