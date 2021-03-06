#include "timer.h"
#include "common.h"
#include "print.h"
#include "isr.h"

u32 tick = 0;

static void timer_callback(registers_t regs){
    tick++;
    puts("\r\nTick: ");
    putInt(tick);
}

void init_timer(u32 freq){
    register_interrupt_handler(IRQ0, &timer_callback);
    u32 divisor = 1193180 / freq;
    outb(0x43, 0x36);

    u8 l = (u8)(divisor & 0xFF);
    u8 h = (u8)((divisor>>8)&0xFF);
    outb(0x40, l);
    outb(0x40, h);

    puts("\r\ninit timer ok");
}
