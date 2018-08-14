#include "common.h"
#include "print.h"
#include "mm.h"
#include "idt.h"
#include "timer.h"
#include "paging.h"
#include "mem_layout.h"


void cmain(){
    init_idt();
    /*
    asm volatile ("int $0x3");
    asm volatile ("int $0x4");
    */

    u64 mem = getPhysicalMemory();    
    init_paging(mem);
    puts("\r\npaging success!");
    /*
    u32 *ptr = (u32*)0xFF000;
    u32 do_page_fault = *ptr;
    */
    
    asm volatile ("sti");
    init_timer(100);
}
