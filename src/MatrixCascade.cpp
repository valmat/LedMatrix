#include "MatrixCascade.h"



/*
MatrixCascade::MatrixCascade(Pino data, Pino clk, Pino cs, int numDevices) :
    _mosi(data, Pino::Mode::out),
    _clk(clk, Pino::Mode::out),
    _cs(cs, Pino::Mode::out),
    _numDevices( (numDevices<=0 || numDevices>8 ) ? 8 : numDevices)
{
    _cs.on();

    for(int i=0; i < 64; i++) 
        status[i]=0x00;
    for(int i=0; i<_numDevices; i++) {
        spiTransfer(i, OP_DISPLAYTEST, 0);
        //scanlimit is set to max on startup
        setScanLimit(i, 7);
        //decode is done in source
        spiTransfer(i, OP_DECODEMODE, 0);
        clearDisplay(i);
        //we go into shutdown-mode on startup
        shutdown(i, true);
    }
}

int MatrixCascade::getDeviceCount() {
    return _numDevices;
}

void MatrixCascade::shutdown(int addr, bool b) {
    if(addr<0 || addr>=_numDevices)
        return;
    if(b)
        spiTransfer(addr, OP_SHUTDOWN,0);
    else
        spiTransfer(addr, OP_SHUTDOWN,1);
}

void MatrixCascade::setScanLimit(int addr, int limit) {
    if(addr<0 || addr>=_numDevices)
        return;
    if(limit>=0 && limit<8)
        spiTransfer(addr, OP_SCANLIMIT,limit);
}

void MatrixCascade::setIntensity(int addr, int intensity) {
    if(addr<0 || addr>=_numDevices)
        return;
    if(intensity>=0 && intensity<16)	
        spiTransfer(addr, OP_INTENSITY,intensity);
}

void MatrixCascade::clearDisplay(int addr) {
    int offset;

    if(addr<0 || addr>=_numDevices)
        return;
    offset=addr*8;
    for(int i=0; i<8; i++) {
        status[offset+i]=0;
        spiTransfer(addr, i+1,status[offset+i]);
    }
}

void MatrixCascade::setLed(int addr, int row, int column, boolean state) {
    int offset;
    uint8_t val=0x00;

    if(addr<0 || addr>=_numDevices)
        return;
    // If out of matrix range
    if(row < 0 || row >= _matrixSize || column < 0 || column > _matrixSize)
        return;
    offset=addr*8;
    val=B10000000 >> column;
    if(state)
        status[offset+row]=status[offset+row]|val;
    else {
        val=~val;
        status[offset+row]=status[offset+row]&val;
    }
    spiTransfer(addr, row+1,status[offset+row]);
}

void MatrixCascade::setRow(int addr, int row, uint8_t value) {
    int offset;
    if(addr<0 || addr>=_numDevices)
        return;
    if(row < 0 || row >= _matrixSize)
        return;
    offset=addr*8;
    status[offset+row]=value;
    spiTransfer(addr, row+1,status[offset+row]);
}

void MatrixCascade::setColumn(int addr, int col, uint8_t value) {
    uint8_t val;

    if(addr < 0 || addr >= _numDevices)
        return;
    if(col < 0 || col >= _matrixSize) 
        return;
    for(int row=0; row < _matrixSize; row++) {
        val=value >> (7-row);
        val=val & 0x01;
        setLed(addr,row,col,val);
    }
}

void MatrixCascade::setDigit(int addr, int digit, uint8_t value, boolean dp) {
    int offset;
    uint8_t v;

    if(addr<0 || addr>=_numDevices)
        return;
    if(digit<0 || digit>7 || value>15)
        return;
    offset=addr*8;
    v=pgm_read_byte_near(charTable + value); 
    if(dp)
        v|=B10000000;
    status[offset+digit]=v;
    spiTransfer(addr, digit+1,v);
}

void MatrixCascade::setChar(int addr, int digit, char value, boolean dp) {
    int offset;
    uint8_t index,v;

    if(addr<0 || addr>=_numDevices)
        return;
    if(digit<0 || digit>7)
        return;
    offset=addr*8;
    index=(uint8_t)value;
    if(index >127) {
        //no defined beyond index 127, so we use the space char
        index=32;
    }
    v=pgm_read_byte_near(charTable + index); 
    if(dp)
        v|=B10000000;
    status[offset+digit]=v;
    spiTransfer(addr, digit+1,v);
}

void MatrixCascade::spiTransfer(int addr, volatile uint8_t opcode, volatile uint8_t data) {
    //Create an array with the data to shift out
    int offset=addr*2;
    int maxbytes=_numDevices*2;

    for(int i=0;i<maxbytes;i++)
        spidata[i]=(uint8_t)0;
    //put our device data into the array
    spidata[offset+1]=opcode;
    spidata[offset]=data;
    //enable the line 
    _cs.off();
    //Now shift out the data 
    for(int i=maxbytes;i>0;i--)
        shiftOut(_mosi,_clk,MSBFIRST,spidata[i-1]);
    //latch the data onto the display
    _cs.on();
}

*/


