# LedMatrix

**LedMatrix** -- это гибкая и мощная Arduino-*C++11* библиотека для управления светодиодными матрицами на чипах MAX7219 и MAX7221.

- [Основные особенности](#Основные-особенности)
- [Работа с одиночной матрицей](#Работа-с-одиночной-матрицей)
	- [Основные методы](#Основные-методы)
	- [Поворот матриц](#Поворот-матриц)
	- [Сеттеры](#Сеттеры)
	- [Геттеры](#Геттеры)
	- [Инверсия](#Инверсия)
	- [Сдвиг](#Сдвиг)
- [Синтаксический сахар](#Синтаксический-сахар)
- [Каскады матриц](#Каскады-матриц)
	- [Основные методы MatrixCascade](#Основные-методы-matrixcascade)
	- [Суперкаскады](#Суперкаскады)
- [Дополнительно](#Дополнительно)


## Основные особенности
С помощью библиотеки **LedMatrix** вы можете гибко управлять светодиодными матрицами подключенными с помощью чипов  **MAX7219** и **MAX7221**. А так же каскадами таких матриц. И целыми группами каскадов.
Она может работать как через программный SPI, используя для подключения любые три свободные пина, так и через аппаратный интерфейс SPI. 
Аппаратный SPI, естественно быстрее.

Теперь по порядку.

## Работа с одиночной матрицей
Прежде всего, необходимо подключить заголовочный файл: `#include <LedMatrix.h>`.
Далее, как это принято в программах для Ардуино, необходимо создать глобальный объект:

```c
#include "LedMatrix.h"
// pin 11 is connected to the DataIn
// pin 13 is connected to the CLK
// pin 10 is connected to LOAD (cs)
// Software-SPI
LedMatrix matrix(11, 13, 10);
```
или так:
```c
#include "LedMatrix.h"
//Hardware-SPI
LedMatrix matrix(10);
```
Теперь с матрицей можно работать.

Предусмотрено два конструктора.

Один конструктор создает матрицу, работающую через программный интерфейс SPI:
```c
// Software-SPI Constructor
// @param dataPin   pin on the Arduino where data gets shifted out (DIN)
// @param clockPin  pin for the clock  (CLK)
// @param csPin     pin for selecting the device   (CS - chip select pin)
LedMatrix(uint8_t data, uint8_t clk, uint8_t cs);
```
другой через аппаратный:
```c
// HardWare-SPI Constructor
// @param csPin pin for selecting the device   (CS -- chip select pin)
LedMatrix(uint8_t cs);
```
Выбор используемого интерфейса SPI зависит от вызванного конструктора.

### Основные методы

Перечислю доступные методы.

```c
// Set the shutdown (power saving) mode for the device
void shutdown() const;
```
Метод `shutdown()` отключает питание матрицы, в целях энергосбережения. По умолчанию, при старте, питание матрицы включено.

```c
// Set the wakeup mode for the device
void wakeup() const;
```
Метод `wakeup()` включает питание матрицы, если оно было ранее выключено.


```c
// Set the brightness of the display.
// @param intensity the brightness of the display. (0..15)
void setIntensity(uint8_t intensity) const;
```
Метод `setIntensity()` устанавливает яркость светодиодов. Возможные значения от 0 до 15.


```c
// Switch all LEDs on the display to off.
void clear();
```
Метод `clear()` "очищает" экран, выключая все точки матрицы.


```c
// Switch all LEDs on the display to on.
void fill();
```
Метод `fill()` "заполняет" экран, включая все точки матрицы.

### Поворот матриц

Как я уже говорил, матрицы могут быть объединены в каскад. Я считаю, что при их объединении в каскад нужно исходить в первую очередь из удобства монтажа. В этом случае, некоторые матрицы могут оказаться повернутыми или даже перевернутыми. На этот случай, я добавил возможность программного поворота матриц.

Следующие методы реализуют эту возможность:

```c   
// Set how many times to rotate the matrix clockwise
// @param From 0 to 3
void setRotation(uint8_t times = 1);

// Reset rotation flag to default
void resetRotation();

// Get how many times the matrix was rotated clockwise
uint8_t getRotation() const;
```

Узнать, какой индекс имеет матрица в каскаде поможет следующий метод:
```c
// get device index in cascade
uint16_t index() const;
```

### Сеттеры

Теперь о том как "заполнять" матрицы.

Для заполнения матрицы доступны следующие методы:

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

В списках аргументов вы можете видеть здесь типы `Row`, `Col` и `buint8_t`.
Не пугайтесь. Они были введены для удобства. Чем они могут быть вам полезны я напишу ниже.
А пока вам достаточно знать, что эти типы автоматически преобразуются в числа типа `uint8_t` и обратно.
По сути, эти типы и есть `uint8_t` + немного сахара.

То есть такая запись:
```c
matrix.on(3, 5);
```
абсолютно корректна.

Расписывать назначения всех сеттеров не буду, поскольку их называния и прототипы говорят сами за себя.
Подробно остановлюсь на двух.

```c
template <typename T>
void set(const std::initializer_list<T> &disp);
```
Этот метод позволяет вам заполнить матрицу на месте. Прямо во время компиляции, не создавая промежуточных массивов или чего то еще.
Вот пример использования:
```c
matrix.set({0b00000000, 0b01100110, 0b10011001, 0b10000001, 0b01000010, 0b00100100, 0b00011000, 0b00000000});
```

Метод `void set(const uint8_t arr[])` позволяет заполнить матрицу предварительно созданным массивом:
```c
uint8_t arr[8] = {0b00000000, 0b00100000, 0b00000000, 0b01100000, 0b00100000, 0b00100000, 0b00100000, 0b01110000};
matrix.set(arr);
```
### Геттеры

Для извлечения информации из матрицы предназначена следующая группа методов:

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
Я думаю, дополнительные комментарии не нужны.

### Инверсия

Точки матрицы, а так же отдельные строки и столбцы можно инвертировать. Для этого предназначены следующие методы:

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
### Сдвиг

```c
// Shift matrix
// @param value is shifting value
// @return shifted value
buint8_t shiftUp(buint8_t value = 0);
buint8_t shiftDown(buint8_t value = 0);
buint8_t shiftLeft(buint8_t value = 0);
buint8_t shiftRight(buint8_t value = 0);
```
Эти методы сдвигают матрицу в ту или иную сторону. Возвращаемым значением является вымещенная строка или столбец. В качестве аргумента можно передать значение замещаемой строки или столбца.

## Синтаксический сахар

Пару слов о типах `Row`, `Col` и `buint8_t`.

`Row`, `Col` объявлены в заголовочном файле `RowCol.h`. Оба эти типа могут быть использованы как числовые, но обладают дополнительными возможностями.

Переменные `Row`, `Col` всегда в диапазоне 0..7.

Они выполняют роль итератора и позволяют осуществить красивую перегрузку.
То есть вместо неуклюжего кода
```c
uint8_t foo(/*...*/) {/*...*/}

for(uint8_t row = 0; row < 8; ++row) {
    matrix.setRow(row, foo(row));
}
```

можно написать лаконичный код:
```c
uint8_t foo(/*...*/) {/*...*/}

for(auto &row: matrix.rows()) {
    matrix.set(row, foo(row));
}
```

Для их использования предусмотрено два метода:
```c
// Make rows and colomns iterable
RowsIterator rows() const;
ColsIterator cols() const;
```
которые возвращают итераторы для строк и столбцов, соответственно.


Тип `buint8_t` определен в заголовочном файле `BitInt.h`.
Его определение это просто специализация шаблонного класса `BitInt`:
```c
// Types predefinition
using buint8_t  = BitInt<uint8_t>;
// ...
```

Он ведет себя как uint8_t, но позволяет легко получить доступ к своему бинарному представлению.
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

## Каскады матриц

Матрицы могут быть объеденены в каскад.
Схема подключения вот такая:
```
 -> VVC  ->  VVC  ->   
 -> GND  ->  GND  ->   
 -> DIN      DOUT ->   
    DOUT ->  DIN      
 -> CS   ->  CS   ->  
 -> CLK  ->  CLK  ->   
```
Как и одиночные матрицы, каскад матриц может управляться как с помощью программного интерфейса SPI, так и с помощью аппаратного.
Точно так же, программный SPI позволяет использовать любые три свободные пина, аппаратный оставляет свободным только один пин (CS):
```
//   Hardware-SPI wiring scheme:
//   CLK => SCLK      (Arduino UNO/Nano/Mini pin 13)
//   DIN => MOSI      (Arduino UNO/Nano/Mini pin 11)
//   CS =>            (Arduino any pin)
```
но аппаратный SPI заметно шустрее.

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
Обратите внимание,  класс `MatrixCascade` шаблонный. И вам нужно явно указать размер каскада (`MatrixCascade<3>`) на этапе компиляции.


Что бы использовать каскады матриц и группы каскадов матриц, подключите заголовочный файл [MatrixCascade.h](src/MatrixCascade.h)

### Основные методы `MatrixCascade`

Уже знакомые нам методы, которые в данном случае являются групповыми:

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

Метод позволяющий получить размер каскада:
```c
// Returns the number of devices on this MatrixCascade
constexpr uint16_t size() const;
```

Получение доступа к матрице по индексу:
```c
LedMatrix& get(uint16_t index);
```
Класс `MatrixCascade` обладает свойствами массива. В частности доступ к содержащимся  в нем матрицам можно получить через оператор `[]`:

```c
cascade[0].setRotation(3);
cascade[1].setRotation(1);
```

А так же `MatrixCascade` является итерируемым:
```c
for(auto &matrix: cascade) {
    matrix.shiftUp();
}
```
### Суперкаскады

Каскады матриц можно, в свою очередь, объединять в суперкаскады.

Суперкаскад от каскада отличается только способом конструирования объекта. На самом деле это все тот же `MatrixCascade`.

Что бы создать суперкаскад, нужно использовать функцию `combineCascades()`. Пример:
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
Переменная `cascade` будет объектом типа `MatrixCascade<45>`. Соответственно она будет управлять 45-ю матрицами. Это позволяет снять ограничения *8* матриц на каскад, накладываемые чипами **MAX7219** и **MAX7221**. Фактическим ограничением является количество свободных пинов.

## Дополнительно
Более подробную информацию можно получить в [исходном коде](src), который я постарался снабдить комментариями, и в [примерах](examples).

---
Библиотека не реализует средств для печати текстовых строк на каскаде матриц. Это сделано специально. Поскольку матрицы могут быть смонтированы произвольным образом. И внесение в библиотеку кода предполагающего какой-то конкретный вид монтажа было бы нарушением целостности. Тем более написать надстроечную библиотеку с нужной функциональностью не составит труда.

Пара примеров как сделать бегущую строку: [1](examples/MultiShift/MultiShift.ino), [2](examples/HelloHabr/HelloHabr.ino)

---
Первоначально, библиотека была форком библиотеки [LedControl](https://github.com/wayoda/LedControl).
Я полностью переработал исходную библиотеку. Целю было получить более гибкий интерфейс, оптимизировать читаемость кода и производительность.
В настоящий момент от исходной библиотеки осталась всего пара строк, так что проект был вынесен в отдельный репозитарий.

---
Не стесняйтесь сообщать об найденных ошибках и присылать свои предложения.

Если вы хорошо знаете английский и в каком-то месте мой перевод показался вам корявым, feel free to report it.

---
[Лицензия](LICENSE)


[English version](README.md)


