#include "keyboard.h"
#include "console.h"
#include "isr.h"
#include <stdint.h>

#define BUFFER_SIZE 128
static char keybuffer[BUFFER_SIZE];
static size_t write_pos = 0;
static size_t read_pos = 0;

static const char keymap[128] = {
    0, 27,'1','2','3','4','5','6','7','8','9','0','-','=','\b',
    '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n',
    0,'a','s','d','f','g','h','j','k','l',';','\'','`',0,
    '\\','z','x','c','v','b','n','m',',','.','/',0,0,0,0,0,
};

extern "C" void keyboard_irq_handler() {
    uint8_t scancode;
    asm volatile("inb %1, %0" : "=a"(scancode) : "Nd"(0x60));

    if (!(scancode & 0x80)) { // touche pressée
        char c = keymap[scancode];
        if (c && write_pos < BUFFER_SIZE) {
            keybuffer[write_pos++] = c;
            Console::putChar(c);
        }
    }

    uint8_t eoi = 0x20;
    if (scancode >= 8) asm volatile("outb %0, %1" : : "a"(eoi), "Nd"(0xA0));
    asm volatile("outb %0, %1" : : "a"(eoi), "Nd"(0x20));
}

extern "C" void keyboard_init() {
    irq_install_handler(1, keyboard_irq_handler);
}

extern "C" bool keyboard_get_char(char* c) {
    if (read_pos < write_pos) {
        *c = keybuffer[read_pos++];
        if (read_pos == write_pos) read_pos = write_pos = 0;
        return true;
    }
    return false;
}
