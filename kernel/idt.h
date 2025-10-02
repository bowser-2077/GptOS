#pragma once
#include <stdint.h>

struct IDTEntry {
    uint16_t base_low;
    uint16_t sel;
    uint8_t always0;
    uint8_t flags;
    uint16_t base_high;
} __attribute__((packed));

struct IDTPointer {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

void idt_init();
void idt_set_gate(int num, uint32_t base, uint16_t sel, uint8_t flags);
