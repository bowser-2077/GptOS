#include "keyboard.h"
#include "console.h"
#include "utils.h"

extern "C" void shell_loop() {
    char input[64];
    size_t pos = 0;
    char c;

    Console::write("> ");

    while (1) {
        if (keyboard_get_char(&c)) {
            if (c == '\n') {
                input[pos] = 0;
                Console::write("\n");
                if (strcmp(input, "help") == 0)
                    Console::write("Commandes: help, about, cls\n");
                else if (strcmp(input, "about") == 0)
                    Console::write("GptOS, kernel en C++ par ChatGPT\n");
                else if (strcmp(input, "cls") == 0)
                    Console::clear();
                else
                    Console::write("Commande inconnue\n");
                pos = 0;
                Console::write("> ");
            } else if (c == '\b') {
                if (pos > 0) { pos--; Console::putChar('\b'); }
            } else {
                if (pos < 63) input[pos++] = c;
            }
        }
        asm("hlt"); // attendre interruption
    }
}
