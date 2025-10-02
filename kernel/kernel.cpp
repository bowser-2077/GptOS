#include "console.h"
#include "keyboard.h"
#include "shell.h"

extern "C" {

// Multiboot header
struct multiboot_header {
    uint32_t magic;
    uint32_t flags;
    uint32_t checksum;
};

__attribute__((section(".multiboot"))) 
multiboot_header mb_header = {
    0x1BADB002,
    0,
    0xE4524DFD
};

}

extern "C" void kernel_main() {
    Console::init();
    Console::setColor(0x0A);
    Console::write("Bienvenue sur GptOS !\n");
    Console::write("> ");

    keyboard_init();
    shell_loop();
}
