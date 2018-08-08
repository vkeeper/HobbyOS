#ifndef PAGING_H
#define PAGING_H

#include "common.h"
typedef struct page{
    u32 present;
    u32 rw;
    u32 us;
    u32 accessed;
    u32 dirty;
    u32 unused;
    u32 frame;
} page_t;

typedef struct page_table{
    page_t pages[1024];
} page_table_t;

typedef struct page_directory{
    page_table_t *tables[1024];
    u32 tablesPhysical[1024];
    u32 physicalAddr;
} page_directory_t;

void set_frame(u32 frame_addr);

void clear_frame(u32 frame_addr);

u32 test_frame(u32 frame_addr);

u32 first_frame();


void init_paging();

void switch_page_directory(page_directory_t *new);

page_t *get_page(u32 address, int make, page_directory_t *dir);

//void page_fault(registers_t regs);

void alloc_frame(page_t *page, u8 is_kernel, u8 is_writeable);

void free_frame(page_t *page);

#endif
