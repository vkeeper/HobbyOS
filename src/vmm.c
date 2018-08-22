#include "common.h"
#include "isr.h"
#include "vmm.h"

page_directory_t *pgd;

void init_vmm(){

}

void switch_pgd(u32 pd){

}

void map(pgd_t *dir, u32 va, u32 pa, u32 flags){

}

void get_mapping(pgdt_ *dir, u32 va, u32 *pa){

}

void page_fault(registers_t *regs){
    u32 fault_addr;
    asm volatile ("mov %%cr2, %0" : "=r"(fault_addr));
    int present = !(regs->err_code & 0x1);
    int rw      = regs->err_code & 0x2;
    int us      = regs->err_code & 0x4;
    int reserved= regs->err_code & 0x8;
    int id      = regs->err_code & 0x10;

    puts("\r\npage fault happened");
    if(present){ puts(" present"); }
    if(rw){ puts(" read-only");}
    if(us){ puts(" user-mode");}
    if(reserved){ puts(" reserved");}
    puts(" at 0x");
    putInt(fault_addr);
    
    asm volatile ("hlt");
}
