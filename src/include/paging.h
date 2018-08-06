#ifndef PAGING_H
#define PAGING_H

#include <stdlib.h>

typedef struct registers
{
    u32int ds;                  // Data segment selector
    u32int edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
    u32int int_no, err_code;    // Interrupt number and error code (if applicable)
    u32int eip, cs, eflags, useresp, ss; // Pushed by the processor automatically.
} registers_t;

typedef struct page{

    u_32int_t present;
    u_32int_t rw;
    u_32int_t user;
    u_32int_t accessed;
    u_32int_t dirty;
    u_32int_t unused;
    u_32int_t frame;
} page_t;

typedef struct page_table{
    page_table_t *tables[1024];

} page_table_t;

typedef struct page_directory{
    page_table_t *tables[1024];
    u_32int_t tablePhysical[1024];
    u_32int_t physicalAddr;
} page_directory_t;

void initialise_paging();

void switch_page_directory(page_directory_t *new);

page_t *get_page(u_32int_t address, int make, page_directory_t *dir);

//void page_fault(registers_t regs);

#endif
