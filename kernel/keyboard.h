#pragma once
#include <stdint.h>
#include <stdbool.h>

extern "C" void keyboard_init();
extern "C" bool keyboard_get_char(char* c);
