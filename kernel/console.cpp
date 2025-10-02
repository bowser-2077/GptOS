#include "console.h"

uint16_t* Console::buffer = (uint16_t*)0xB8000;
uint8_t Console::color = 0x0F;
size_t Console::row = 0;
size_t Console::col = 0;

void Console::init() {
    clear();
}

void Console::clear() {
    for (size_t i = 0; i < 80 * 25; i++) {
        buffer[i] = (color << 8) | ' ';
    }
    row = 0; col = 0;
}

void Console::setColor(uint8_t c) {
    color = c;
}

void Console::putChar(char c) {
    if (c == '\n') {
        row++;
        col = 0;
    } else {
        buffer[row * 80 + col] = (color << 8) | c;
        col++;
        if (col >= 80) { col = 0; row++; }
    }
    if (row >= 25) row = 0; // simple scroll
}

void Console::write(const char* str) {
    for (size_t i = 0; str[i] != '\0'; i++) {
        putChar(str[i]);
    }
}

void Console::writeHex(uint32_t num) {
    const char* hex = "0123456789ABCDEF";
    write("0x");
    for (int i = 28; i >= 0; i -= 4) {
        putChar(hex[(num >> i) & 0xF]);
    }
}
