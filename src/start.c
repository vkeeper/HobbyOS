#include "common.h"
#include "print.h"
#include "mm.h"
#include "idt.h"
#include "timer.h"
#include "paging2.h"
#include "mem_layout.h"

__attribute__((section(".init.data"))) u32 *tables_temp =(u32*)0x3000;
__attribute__((section(".init.data"))) u32 *tables=(u32*)0x4000;
__attribute__((section(".init.data"))) u32 *dir=(u32*)0x2000;


__attribute__((section(".init.text"))) void cmain(){
    // 0x0 ~ 0x400000 : 0xC0000000 ~ 0xC0400000
    u32 i;
    for(i = 0; i < 1024; i++){
        tables_temp[i] = (i << 12) | 0x3;
    }
    dir[0] = (u32)tables_temp|0x3;

    for(i = 0; i< 1024; i++){
        tables[i] = (i << 12) | 0x3;
    }
    u32 table_index = 0xC0000000/0x1000/1024;
    dir[table_index] =(u32)tables|0x3;

    write_cr3(dir);
    write_cr0(read_cr0()|0x80000000);
    kern_entry();
}

void kern_entry(){
    puts("\r\nenable vmm start");
    init_vmm();

    init_idt();
    asm volatile ("int $0x3");
    asm volatile ("int $0x4");

    u64 mem = getPhysicalMemory();    
    init_pmm(mem);
    
    puts("\r\npaging success!");
    u32 addr = alloc_page();
    puts("\r\nsuccess alloc page ");
    putInt(addr);

    addr = alloc_page();
    puts("\r\nsuccess alloc page ");
    putInt(addr);

    addr = alloc_page();
    puts("\r\nsuccess alloc page ");
    putInt(addr);
/*
    u32 *ptr = (u32*)0xDFF0000;
    u32 do_page_fault = *ptr;
    asm volatile ("sti");
    init_timer(100);
*/
}
