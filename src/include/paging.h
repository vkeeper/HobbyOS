#ifndef PAGING_H
#define PAGING_H
#include "isr.h"
#include "common.h"

#define PAGE_OFFSET 0xC0000000
#define PD_INDEX(addr)(addr/0x1000/1024)

typedef struct page{
    u32 present     :1;
    u32 rw          :1;
    u32 us          :1;
    u32 accessed    :1;
    u32 dirty       :1;
    u32 unused      :7;
    u32 frame       :20;
} __attribute__((packed)) page_t;

typedef struct page_table{
    page_t pages[1024];
} __attribute__((packed)) page_table_t;

typedef struct page_directory{
    page_table_t *tables[1024];
    u32 tablesPhysical[1024];
    u32 physicalAddr;
}__attribute__((packed)) page_directory_t;
/*
void set_frame(u32 frame_addr);

void clear_frame(u32 frame_addr);

u32 test_frame(u32 frame_addr);

u32 first_frame();
*/
void init_paging(u64 memory);

void switch_page_directory(page_directory_t *dir);

page_t *get_page(u32 address, int make, page_directory_t *dir);

void alloc_frame(page_t *page, u8 is_kernel, u8 is_writeable);

void free_frame(page_t *page);

void page_fault(registers_t regs);

#endif
