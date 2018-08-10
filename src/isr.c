#include "common.h"
#include "isr.h"


void isr_handler(registers_t regs){
    puts("\r\nreceived interrupts:");
    putInt(regs.err_code);
    puts(" ");
    putInt(regs.int_no);
}
