#include "isr.h"
#include "console.h"
#include <stdint.h>

static isr_t interrupt_handlers[256];

extern "C" void isr_handler() {
    Console::write("Interrupt!\n");
}

extern "C" void irq_handler(int irq) {
    if (interrupt_handlers[irq]) interrupt_handlers[irq]();

    uint8_t eoi = 0x20;
    if (irq >= 8) asm volatile("outb %0, %1" : : "a"(eoi), "Nd"(0xA0));
    asm volatile("outb %0, %1" : : "a"(eoi), "Nd"(0x20));
}

extern "C" void irq_install_handler(int irq, isr_t handler) {
    interrupt_handlers[irq] = handler;
}

void isr_install() {
    // TODO: initialisation IDT
}
