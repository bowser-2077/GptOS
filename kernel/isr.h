#pragma once
#include <stdint.h>

typedef void (*isr_t)();

// ISR générique
extern "C" void isr_handler();
extern "C" void irq_handler(int irq);

// Installer un handler pour les IRQ
extern "C" void irq_install_handler(int irq, isr_t handler);

// Initialisation ISR
void isr_install();
