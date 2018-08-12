#include "common.h"
#include "isr.h"

isr_t interrupt_handlers[256];

void isr_handler(registers_t regs){
    puts("\r\nreceived interrupts:");
    putInt(regs.err_code);
    puts(" ");
    putInt(regs.int_no);
}

void irq_handler(registers_t regs){
//    puts("\r\n start req_handler");
    if(regs.int_no >= 40){
        outb(0xA0, 0x20);
  //      puts("\r\n req_handler >= 40");
    }

    outb(0x20, 0x20);
    if(interrupt_handlers[regs.int_no] != 0){
        isr_t handler = interrupt_handlers[regs.int_no];
    //    puts("\r\n interrupt_handler find");
        handler(regs);
    }
    //puts("\r\n req_handler over");
}

void register_interrupt_handler(u8 n, isr_t handler){
    interrupt_handlers[n] = handler;
}
