#include "common.h"
#include "print.h"
#include "mm.h"
#include "idt.h"
#include "timer.h"
#include "paging.h"
#include "mem_layout.h"

#define STACK_SIZE 2048

__attribute__((section(".init.data"))) u32 *tables_temp = (u32 *)0x3000;
__attribute__((section(".init.data"))) u32 *tables = (u32 *)0x4000;

__attribute__((section(".init.data"))) u32 *dir =(u32 *)0x2000;

u8 kern_stack[STACK_SIZE];

__attribute__((section(".init.text"))) void cmain(){
    /**
     * 0xC0000000 ~ 0xC0400000 : 0x0 ~ 0x400000
     */
    u32 i;
    for(i = 0; i < 1024; i++){
        tables_temp[i] = i << 12 |0x3;
    }

    for(i = 0; i < 1024; i++){
        tables[i] = i << 12 | 0x3;
    }
    u32 frame_num = 0xC0000000/0x1000;
    u32 table_idx = frame_num/1024;
    dir[table_idx] = tables;
    dir[table_idx] |= 0x1;

    dir[0] = tables_temp;
    dir[0] |= 0x1;

    asm volatile("mov %0, %%cr3":: "r"(dir));
    u32 cr0;
    asm volatile("mov %%cr0, %0": "=r"(cr0));
    cr0 |= 0x80000000;
    asm volatile("mov %0, %%cr0":: "r"(cr0));
    
    u32 kern_stack_top = ((u32) kern_stack + STACK_SIZE) &0xFFFFFFF0;
    asm volatile("mov %0, %%esp\n\t"
                 "xor %%ebp, %%ebp" : : "r"(kern_stack_top));
    /*
    write_cr3(dir);
    write_cr0(read_cr0()|0x80000000);
    */
    kern_entry();
}

void kern_entry(){
    asm volatile ("hlt");
//    init_idt();
    /*
    asm volatile ("int $0x3");
    asm volatile ("int $0x4");
    */
/**
    u64 mem = getPhysicalMemory();    
    init_paging(mem);
    puts("\r\npaging success!");
    u32 *ptr = (u32*)0xFF000;
    u32 do_page_fault = *ptr;
    
    asm volatile ("sti");

    init_timer(100);
*/
}
