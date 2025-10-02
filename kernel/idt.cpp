#include "idt.h"

extern "C" void idt_flush(uint32_t);

static IDTEntry idt[256];
static IDTPointer idtp;

void idt_set_gate(int num, uint32_t base, uint16_t sel, uint8_t flags) {
    idt[num].base_low = base & 0xFFFF;
    idt[num].base_high = (base >> 16) & 0xFFFF;
    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
}

void idt_init() {
    idtp.limit = (sizeof(IDTEntry) * 256) - 1;
    idtp.base = (uint32_t)&idt;
    for (int i = 0; i < 256; i++) {
        idt_set_gate(i, 0, 0, 0);
    }
    idt_flush((uint32_t)&idtp);
}
