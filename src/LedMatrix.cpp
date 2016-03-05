

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
   Serial.println( "LedMatrix::LedMatrix" );
    _cs.on();

    for(int i=0; i < 64; i++) 
        _status[i]=0x00;

    spiTransfer(OP_DISPLAYTEST, 0);
    //scanlimit is set to max on startup
    setScanLimit(7);
    //decode is done in source
    spiTransfer(OP_DECODEMODE, 0);
    clear();
    //we go into shutdown-mode on startup
    shutdown();
}

void LedMatrix::shutdown() {
    Serial.println( "shutdown" );
    spiTransfer(OP_SHUTDOWN,0);
}

void LedMatrix::wakeup() {
    Serial.println( "wakeup" );
    spiTransfer(OP_SHUTDOWN,1);
}

void LedMatrix::setScanLimit(int limit) {
    Serial.println( "setScanLimit" );
    if(limit>=0 && limit<8)
        spiTransfer(OP_SCANLIMIT,limit);
}

void LedMatrix::setIntensity(int intensity) {
    Serial.println( "setIntensity" );
    if(intensity>=0 && intensity<16)	
        spiTransfer(OP_INTENSITY, intensity);
}

void LedMatrix::clear() {
    Serial.println( "clear" );
    uint8_t offset = _index * 8;
    for(int i = 0; i < 8; i++) {
        _status[offset+i] = 0;
        spiTransfer(i+1, _status[offset+i]);
    }
}

void LedMatrix::set(Row row, Col col, bool state) {
    uint8_t offset =_index * 8 + row;
    uint8_t val    = B10000000 >> col;

    if(state)
        _status[offset] = _status[offset]|val;
    else {
        val = ~val;
        _status[offset] = _status[offset]&val;
    }
    spiTransfer(row+1, _status[offset]);
}

void LedMatrix::setRow(Row row, uint8_t value) {
    
    uint8_t offset =_index * 8;
    _status[offset+row]=value;
    spiTransfer(row+1,_status[offset+row]);
}

void LedMatrix::setCol(Col col, uint8_t value) {
    uint8_t val;
    for(int row=0; row < _size; row++) {
        val=value >> (_size - 1 - row);
        val=val & 0x01;
        set(row, col, val);
    }
}

void LedMatrix::spiTransfer(volatile uint8_t opcode, volatile uint8_t data) {
    //Create an array with the data to shift out
    int offset=_index * 2;
    int maxbytes = _cascadeSize*2;

    for(int i=0; i<maxbytes; i++)
        _spidata[i]=0;
    //put our device data into the array
    _spidata[offset+1] = opcode;
    _spidata[offset]   = data;
    //enable the line 
    _cs.off();
    //Now shift out the data 
    for(int i=maxbytes; i>0; i--)
        shiftOut(_mosi, _clk,MSBFIRST, _spidata[i-1]);
    //latch the data onto the display
    _cs.on();
}    


