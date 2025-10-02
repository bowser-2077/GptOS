#pragma once
#include <stddef.h>
#include <stdint.h>

class Console {
public:
    static void init();
    static void clear();
    static void setColor(uint8_t color);
    static void putChar(char c);
    static void write(const char* str);
    static void writeHex(uint32_t num);

private:
    static uint16_t* buffer;
    static uint8_t color;
    static size_t row, col;
};
