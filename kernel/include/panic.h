#ifndef PANIC_H_
#define PANIC_H_

#include <utils/printk.h>

void dump_registers();

void halt_catchfire(void);
void disable_interrupts(void);

void kpanic(const char *fmt, ...);

#endif
