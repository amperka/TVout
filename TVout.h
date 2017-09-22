#ifndef TVOUT_H
#define TVOUT_H

#include <Arduino.h>
#include "video_gen.h"
#include "fontALL.h"

#define PAL             1
#define	NTSC            0
#define _PAL            1
#define _NTSC           0

#define WHITE           1
#define BLACK           0
#define INVERT          2

#define UP              0
#define DOWN            1
#define LEFT            2
#define RIGHT           3

#define DEC             10
#define HEX             16
#define OCT             8
#define BIN             2
#define BYTE            0

class TVout {
public:
    uint8_t* screen;
    uint8_t begin(uint8_t mode);
    uint8_t begin(uint8_t mode, uint8_t x, uint8_t y);
    void end();

    // accessor functions
    unsigned int hres();
    unsigned int vres();
    char charLine();

    // flow control functions
    void delay(unsigned int x);
    void delayFrame(unsigned int x);
    unsigned long millis();

    // basic rendering functions
    void clearScreen();
    void invert();
    void fill(uint8_t color);
    void setPixel(uint8_t x, uint8_t y, char c);
    bool getPixel(uint8_t x, uint8_t y);
    void drawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, char c);
    void drawRow(uint8_t line, uint16_t x0, uint16_t x1, uint8_t c);
    void drawColumn(uint8_t row, uint16_t y0, uint16_t y1, uint8_t c);
    void drawRect(uint8_t x0, uint8_t y0, uint8_t w, uint8_t h, char c, char fc = -1); 
    void drawCircle(uint8_t x0, uint8_t y0, uint8_t radius, char c, char fc = -1);
    void bitmap(uint8_t x, uint8_t y, const unsigned char* bmp, uint16_t i = 0, uint8_t width = 0, uint8_t lines = 0);
    void shift(uint8_t distance, uint8_t direction);

    // printing functions
    void printChar(uint8_t x, uint8_t y, unsigned char c);
    void setCursor(uint8_t x, uint8_t y);
    void selectFont(const unsigned char* f);

    void write(uint8_t);
    void write(const char* str);
    void write(const uint8_t* buffer, uint8_t size);

    void print(const char[]);
    void print(char, int = BYTE);
    void print(unsigned char, int = BYTE);
    void print(int, int = DEC);
    void print(unsigned int, int = DEC);
    void print(long, int = DEC);
    void print(unsigned long, int = DEC);
    void print(float, int = 2);

    void print(uint8_t, uint8_t, const char[]);
    void print(uint8_t, uint8_t, char, int = BYTE);
    void print(uint8_t, uint8_t, unsigned char, int = BYTE);
    void print(uint8_t, uint8_t, int, int = DEC);
    void print(uint8_t, uint8_t, unsigned int, int = DEC);
    void print(uint8_t, uint8_t, long, int = DEC);
    void print(uint8_t, uint8_t, unsigned long, int = DEC);
    void print(uint8_t, uint8_t, float, int = 2);

    void println(uint8_t, uint8_t, const char[]);
    void println(uint8_t, uint8_t, char, int = BYTE);
    void println(uint8_t, uint8_t, unsigned char, int = BYTE);
    void println(uint8_t, uint8_t, int, int = DEC);
    void println(uint8_t, uint8_t, unsigned int, int = DEC);
    void println(uint8_t, uint8_t, long, int = DEC);
    void println(uint8_t, uint8_t, unsigned long, int = DEC);
    void println(uint8_t, uint8_t, float, int = 2);
    void println(uint8_t, uint8_t);

    void println(const char[]);
    void println(char, int = BYTE);
    void println(unsigned char, int = BYTE);
    void println(int, int = DEC);
    void println(unsigned int, int = DEC);
    void println(long, int = DEC);
    void println(unsigned long, int = DEC);
    void println(float, int = 2);
    void println(void);

    void printPGM(const char[]);
    void printPGM(uint8_t, uint8_t, const char[]);

    void printNumber(unsigned long, uint8_t);
    void printFloat(float, uint8_t);

    // tone functions
    void tone(unsigned int frequency, unsigned long durationMS);
    void tone(unsigned int frequency);
    void noTone();


private:
    // hook setup functions
    void setVBIHook(void (*func)());
    void setHBIHook(void (*func)());

    // override setup functions
    void forceVscale(char sfactor);
    void forceOutStart(uint8_t time);
    void forceLineStart(uint8_t line);
    void incTxtLine();

    uint8_t _cursorX, _cursorY;
    const unsigned char* font;
};

static void inline sp(uint8_t x, uint8_t y, char c); 
#endif
