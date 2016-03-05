

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

LedMatrix::LedMatrix(Pino data, Pino clk, Pino cs, uint8_t ind) :
    _mosi(data, Pino::Mode::out),
    _clk(clk, Pino::Mode::out),
    _cs(cs, Pino::Mode::out),
    _index(ind)
{
    _cs.on();

    for(int i=0; i < 64; i++) 
        status[i]=0x00;

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
    spiTransfer(OP_SHUTDOWN,0);
}

void LedMatrix::wakeup() {
    spiTransfer(OP_SHUTDOWN,1);
}



void LedMatrix::setScanLimit(int limit) {
    if(limit>=0 && limit<8)
        spiTransfer(OP_SCANLIMIT,limit);
}

void LedMatrix::setIntensity(int intensity) {
    if(intensity>=0 && intensity<16)	
        spiTransfer(OP_INTENSITY, intensity);
}

void LedMatrix::clear() {
    uint8_t offset =_index * 8;
    for(int i = 0; i < 8; i++) {
        status[offset+i] = 0;
        spiTransfer(i+1, status[offset+i]);
    }
}

void LedMatrix::set(Row row, Col col, bool state) {
    uint8_t offset =_index * 8 + row;
    uint8_t val    = B10000000 >> col;

    if(state)
        status[offset] = status[offset]|val;
    else {
        val = ~val;
        status[offset] = status[offset]&val;
    }
    spiTransfer(row+1, status[offset]);
}

void LedMatrix::setRow(Row row, uint8_t value) {
    
    uint8_t offset =_index * 8;
    status[offset+row]=value;
    spiTransfer(row+1,status[offset+row]);
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
    // temporary
    int _numDevices = 1;

    int offset=_index * 2;
    int maxbytes=_numDevices*2;

    for(int i=0; i<maxbytes; i++)
        spidata[i]=0;
    //put our device data into the array
    spidata[offset+1] = opcode;
    spidata[offset]   = data;
    //enable the line 
    _cs.off();
    //Now shift out the data 
    for(int i=maxbytes; i>0; i--)
        shiftOut(_mosi, _clk,MSBFIRST, spidata[i-1]);
    //latch the data onto the display
    _cs.on();
}    


