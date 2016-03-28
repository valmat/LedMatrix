# LedMatrix
**LedMatrix** is a flexible and powerful *Arduino C++11* library to control LED matrixes on chips MAX7219 and MAX7221.

- [Main features](#main-features)
- [Single matrix](#single-matrix)
	- [Basic methods](#basic-methods)
	- [Matrix rotation](#matrix-rotation)
	- [Setters](#setters)
	- [Getters](#getters)
	- [Inversion](#inversion)
	- [Shifting](#shifting)
- [Syntactic sugar](#syntactic-sugar)
- [Cascades of matrices](#cascades-of-matrices)
	- [Basic methods of MatrixCascade](#basic-methods-of-matrixcascade)
	- [Supercascades](#supercascades)
- [Additionally](#additionally)


## Main features

With the **LedMatrix** library, you can flexibly control LED matrixes are connected via chips **MAX7219** and **MAX7221**. As well as cascades of such matrices. And whole groups of cascades.
It can work via software SPI, using any three free pins or through hardware SPI.
Hardware SPI of course is faster.

## Single matrix
First of all, you need to connect the header file: `#include <LedMatrix.h>`.
Further, as is customary in the Arduino sketches, you need to create a global object:

```c
#include "LedMatrix.h"
// pin 11 is connected to the DataIn
// pin 13 is connected to the CLK
// pin 10 is connected to LOAD (cs)
// Software-SPI
LedMatrix matrix(11, 13, 10);
```
or so:
```c
#include "LedMatrix.h"
//Hardware-SPI
LedMatrix matrix(10);
```
Now the matrix is ready to use.


The library provides two constructors.

One constructor creates a matrix that operates through software SPI:
```c
// Software-SPI Constructor
// @param dataPin   pin on the Arduino where data gets shifted out (DIN)
// @param clockPin  pin for the clock  (CLK)
// @param csPin     pin for selecting the device   (CS - chip select pin)
LedMatrix(uint8_t data, uint8_t clk, uint8_t cs);
```

The other creates by using hardware SPI:
```c
// HardWare-SPI Constructor
// @param csPin pin for selecting the device   (CS -- chip select pin)
LedMatrix(uint8_t cs);
```
The choice of the using SPI depends on the invoked constructor.

### Basic methods

Below are the main methods:

```c
// Set the shutdown (power saving) mode for the device
void shutdown() const;
```
The method `shutdown()` turns off the power of the matrix, in order to save energy. By default, at startup, the matrix power is turned on.

```c
// Set the wakeup mode for the device
void wakeup() const;
```
The method `wakeup()` turns on the power of the matrix if it was previously turned off.

```c
// Set the brightness of the display.
// @param intensity the brightness of the display. (0..15)
void setIntensity(uint8_t intensity) const;
```
The method `setIntensity()` sets the brightness of the LEDs. Possible values are from 0 to 15.


```c
// Switch all LEDs on the display to off.
void clear();
```
The method `clear()` "cleans" the screen by turning off all points on the matrix.

```c
// Switch all LEDs on the display to on.
void fill();
```
The method `fill()` "fills" the screen by turning on all points on the matrix.

### Matrix rotation

As I said before, the matrix may be combined in a cascade. I believe that when they are combined in a cascade is necessary to proceed first and foremost from the ease of installation. In this case, some matrices may be rotated. For this, I added the ability to programmatically rotation matrices.

The following methods implement this feature:

```c   
// Set how many times to rotate the matrix clockwise
// @param From 0 to 3
void setRotation(uint8_t times = 1);

// Reset rotation flag to default
void resetRotation();

// Get how many times the matrix was rotated clockwise
uint8_t getRotation() const;
```

To know which index has the matrix in the cascade will help the following method:
```c
// get device index in cascade
uint16_t index() const;
```

### Setters

Now let's talk about how to "fill" matrixes.

To fill a matrix, use the following methods:
```c
// Set the status of a single LED.
// @param Row row   the row of the Led (0..7)
// @param Col col   the column of the Led (0..7)
// @param state If true the led is switched on, if false it is switched off
void set(const Row &row, const Col &col, bool state);

// Turn on LED at a point
// @param Row row   the row of the Led (0..7)
// @param Col col   the column of the Led (0..7)
void on(const Row &row, const Col &col);

// Turn off LED at a point
// @param Row row   the row of the Led (0..7)
// @param Col col   the column of the Led (0..7)
void off(const Row &row, const Col &col);

// Set all LEDs in a row to a new state
// @param  row which is to be set (0..7)
// @param  value each bit set to 1 will light up the corresponding LED.
void set(const Row &row, buint8_t value);

// Set all LEDs in a column to a new state
// @param  col -- column which is to be set (0..7)
// @param  value -- each bit set to 1 will light up the corresponding LED.
void set(const Col &col, buint8_t value);

// Set all LEDs in a row to a new state
// @param  row which is to be set (0..7)
// @param  value each bit set to 1 will light up the corresponding LED.
void setRow(const Row &row, buint8_t value);

// Set all LEDs in a column to a new state
// @param  col -- column which is to be set (0..7)
// @param  value -- each bit set to 1 will light up the corresponding LED.
void setCol(const Col &col, buint8_t value);

// Allows to initialize the values of all points of the matrix
// @param  initializer_list instance
template <typename T>
void set(const std::initializer_list<T> &disp);

// Allows to initialize the values of all points of the matrix
// Attention. If you pass an array to this function, strictly follow its length
// @param  raw array
void set(const uint8_t arr[]);
```

In the list of arguments you can see here the types `Row`, `Col` and `buint8_t`.
Do not be alarmed. They were introduced for convenience. What they can do for you I will write [below](#syntactic-sugar).
In the meantime, you need to know that these types are automatically converted to numbers such as `uint8_t` and back.
In fact, these types are the `uint8_t` + a little sugar.
Then the record `matrix.on(3, 5);` is absolutely correct.

I will not describe use of all these setters, because their naming and prototypes speak for themselves.

More focus on two.
```c
template <typename T>
void set(const std::initializer_list<T> &disp);
```
This method allows you to fill the matrix on place. Right at compile time, without creating intermediate arrays or anything else.

Here is an example:
```c
matrix.set({0b00000000,
            0b01100110,
            0b10011001,
            0b10000001,
            0b01000010,
            0b00100100,
            0b00011000,
            0b00000000});
```

The method 
```c
void set(const uint8_t arr[])
```
allows to fill the matrix with a previously created array:
```c
uint8_t arr[8] = {0b00000000,
                  0b00100000,
                  0b00000000,
                  0b01100000,
                  0b00100000,
                  0b00100000,
                  0b00100000,
                  0b01110000};
matrix.set(arr);
```
### Getters

The following group of methods is to retrieve information from the matrix:
```c
// Get state of LED point on matrix
// @param row   the row of the Led (0..7)
// @param col   the column of the Led (0..7)
bool get(const Row &row, const Col &col) const;

// Get the values on row of LED-matrix
// @param row   the row of the Led (0..7)
buint8_t get(const Row &row) const;

// Get the values on colomn of LED-matrix
// @param col   the column of the Led (0..7)
buint8_t get(const Col &col) const;

// Get the values on row of LED-matrix
// @param row   the row of the Led (0..7)
buint8_t getRow(const Row &row) const;

// Get the values on colomn of LED-matrix
// @param col   the column of the Led (0..7)
buint8_t getCol(const Col &col) const;
```
I think any additional comments are not needed.

### Inversion

The points of the matrix, as well as individual rows and columns may be inverted. To do this, use the following methods:
```c
// Invert all points of matrix
void invert();

// Invert current point on matrix
// @param row   the row of the LED (0..7)
// @param col   the column of the LED (0..7)
void invert(const Row &row, const Col &col);

// Invert row on matrix
// @param row   the row of the LED (0..7)
void invert(const Row &row);

// Invert colomn on matrix
// @param col   the column of the LED (0..7)
void invert(const Col &col);

// Invert row on matrix
// @param row   the row of the LED (0..7)
void invertRow(const Row &row);

// Invert colomn on matrix
// @param col   the column of the LED (0..7)
void invertCol(const Col &col);
```
### Shifting

```c
// Shift matrix
// @param value is shifting value
// @return shifted value
buint8_t shiftUp(buint8_t value = 0);
buint8_t shiftDown(buint8_t value = 0);
buint8_t shiftLeft(buint8_t value = 0);
buint8_t shiftRight(buint8_t value = 0);
```
These methods shift a matrix in one direction or another.
The return value is an extracted row or column.
As an argument you can pass the value of the replaced row or column.


## Syntactic sugar

A few words about the types of `Row`, `Col` and `buint8_t`.

`Row` and `Col` are declared in the header file [RowCol.h](src/RowCol.h). Both these types can be used as a numeric, but they have additional features.


-   The variables of `Row` and `Col` is always in the range 0..7.
-   They serve as an iterator and allow a nice overdrive.


That is, instead of the awkward code:
```c
uint8_t foo(/*...*/) {/*...*/}

for(uint8_t row = 0; row < 8; ++row) {
    matrix.setRow(row, foo(row));
}
```

you can write concise code:
```c
uint8_t foo(/*...*/) {/*...*/}

for(auto &row: matrix.rows()) {
    matrix.set(row, foo(row));
}
```
There are two methods to get `Row` and `Col`
```c
// Make rows and colomns iterable
RowsIterator rows() const;
ColsIterator cols() const;
```
These methods return iterators for the rows and columns, respectively.

The type `buint8_t` is defined in the header file [BitInt.h](src/BitInt.h).
Its definition is just a specialization of template class `BitInt`:
```c
// Types predefinition
using buint8_t  = BitInt<uint8_t>;
// ...
```

It behaves as uint8_t, but allows you to easily access their binary representation.
```c
buint8_t x = 88; // 01011000
x[2] = 1;        // 01111000
x[3] = false;    // 01101000
bool a = x[4];   // true
bool a = x[7];   // false

// Iteration:
for(auto v: x) {
    Serial.print(v ? "{I}" : "{O}");
}
```
## Cascades of matrices
Matrixes may be combined in a cascade.

Wiring scheme like this:
```
 -> VVC  ->  VVC  ->   
 -> GND  ->  GND  ->   
 -> DIN      DOUT ->   
    DOUT ->  DIN      
 -> CS   ->  CS   ->  
 -> CLK  ->  CLK  ->   
```
As a single matrix, the cascade matrix can be controlled by using software SPI and by hardware SPI.

Like single matrix case, software SPI allows you to use any three free pins, the hardware SPI leaves only one free pin (CS):
```
//   Hardware-SPI wiring scheme:
//   CLK => SCLK      (Arduino UNO/Nano/Mini pin 13)
//   DIN => MOSI      (Arduino UNO/Nano/Mini pin 11)
//   CS  =>           (Arduino any pin)
```
but the hardware SPI is noticeably faster.

Software-SPI:
```c
#include <MatrixCascade.h>

// pin 11 is connected to the DataIn
// pin 13 is connected to the CLK
// pin 10 is connected to LOAD (cs)
const uint8_t CascadeSize = 3;
// Software-SPI
MatrixCascade<CascadeSize> cascade(11, 13, 10);
```
Hardware-SPI:
```c
#include <MatrixCascade.h>

// pin 11 is connected to the DataIn
// pin 13 is connected to the CLK
// pin 10 is connected to LOAD (cs)
const uint8_t CascadeSize = 3;
// HardWare-SPI
MatrixCascade<CascadeSize> cascade(10);
```
Note,  The class `MatrixCascade` is template. And you need to explicitly specify the size of the cascade (`MatrixCascade<3>`) at compile time.


To use cascades of matrixes and groups of cascades include the header file [MatrixCascade.h](src/MatrixCascade.h)

### Basic methods of `MatrixCascade`

The familiar methods, which in this case are the group:
```c
// Set the shutdown (power saving) mode for all devices
void shutdown() const;

// Set the wakeup mode for all devices
void wakeup() const;

// Set the brightness of all displays.
// @param intensity the brightness of the display. (0..15)
void setIntensity(uint8_t intensity) const;

// Switch all LEDs on all displays to off. 
void clear();

// Switch all LEDs on all displays to on.
void fill();

// Invert all points of all matrixes
void invert();

// How many times to rotate all matrixes clockwise
// @param From 0 to 3
void setRotation(uint8_t times = 1);

// Reset rotation flag for all matrixes to default
void resetRotation();
```

The method allowing to know the size of the cascade:
```c
// Returns the number of devices on this MatrixCascade
constexpr uint16_t size() const;
```

Access to the matrix by index:
```c
LedMatrix& get(uint16_t index);
```

Class `MatrixCascade` has a traits of an array. Contained matrixes can be accessed through the operator `[]`:
```c
cascade[0].setRotation(3);
cascade[1].setRotation(1);
```

Class `MatrixCascade` is iterable:
```c
for(auto &matrix: cascade) {
    matrix.shiftUp();
}
```
### Supercascades


Cascades of matrices may, in turn, combined into a super cascades.
The difference between a cascade and a supercascade is only in the way of constructing any object. In fact it is the same `MatrixCascade`.

To create a supercascade, you need to use the function `combineCascades()`. 
Example:
```c
auto cascade = combineCascades(
    MatrixCascade<5>(10), 
    MatrixCascade<8>(12), 
    MatrixCascade<7>(1, 2, 3),
    MatrixCascade<8>(4, 5, 6),
    MatrixCascade<8>(7, 8, 9),
    MatrixCascade<3>(14), 
    MatrixCascade<6>(15), 
);
```
Variable `cascade` is the object of type `MatrixCascade<45>`.
Accordingly, it will control the 45-th matrices.
This makes it possible to lift the restrictions *8* matrices per cascade imposed chips **MAX7219** and **MAX7221**
The actual limitation is the number of free pins.

## Additionally

More detailed information is available in the [source code](src), which I tried to provide comments, and in the [examples](examples).

---
The library does not implement the means to print a text string on the cascade of matrices. This is intentional.
Since the matrix can be mounted in an arbitrary manner.
And entering  code into the library involving a particular type of installation would be a violation of integrity. 
Especially to write any superstructure library with the desired functionality is not difficult.
All the necessary functions are in the library.

A couple of examples how to make a running line: [1](examples/MultiShift/MultiShift.ino), [2](examples/HelloHabr/HelloHabr.ino)

---
Initially, the library was a fork of the library [LedControl](https://github.com/wayoda/LedControl) library.
I completely reworked the original library. From the original library code has remained just a couple of lines. So it was moved to a separate repository.

---
Feel free to report bugs and send your suggestions.

---
[The MIT License](LICENSE)


[Russian version](README.RU.md)


