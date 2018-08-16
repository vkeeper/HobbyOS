#include "paging.h"
#include "common.h"
#include "mm.h"

u32 *frames; // frame pointer

u32 nframes; // num of frame 

page_directory_t *kernel_directory = 0;

page_directory_t *current_directory = 0;

extern u32 placement_address;

#define NO_FRAME  -1
#define INDEX_OF(a) (a/32)
#define OFFSET_OF(a) (a%32)

static void set_frame(u32 frame_addr){
    u32 frame = frame_addr / 0x1000;
    u32 idx = INDEX_OF(frame);
    u32 off = OFFSET_OF(frame);
    frames[idx] |= (0x1 << off);
}

static void clear_frame(u32 frame_addr){
    u32 frame = frame_addr / 0x1000;
    u32 idx = INDEX_OF(frame);
    u32 off = OFFSET_OF(frame);
    frames[idx] &= ~(0x1 << off);
}

static u32 test_frame(u32 frame_addr){
    u32 frame = frame_addr / 0x1000;
    u32 idx = INDEX_OF(frame);
    u32 off = OFFSET_OF(frame);
    return (frames[idx] & (0x1 << off)); 
}

static u32 first_frame(){
    u32 i, j;
    for(i = 0; i < INDEX_OF(nframes); i++){
        if(frames[i] != 0xFFFFFFFF){
            for(j = 0; j < 32; j++){
                u32 test = 0x1 << j;
                if(!(frames[i] & test)){
                    return i * 32 + j;
                }
            }
        }
    }
    return NO_FRAME;
}


void init_paging(u64 memory){
    u32 max = memory;

    nframes = max / 0x1000;
    frames = (u32 *)kmalloc_a(INDEX_OF(nframes)+1);
    memset(frames, 0, INDEX_OF(nframes)+1);

    kernel_directory = (page_directory_t *)kmalloc_a(sizeof(page_directory_t));
    current_directory = kernel_directory;

    u32 limit = max;
    u32 i = 0;
    while(limit > 0){
        alloc_frame(get_page(i, 1, kernel_directory), 0, 1);
        i += 0x1000;
        limit -= 0x1000;
    }

    register_interrupt_handler(14, page_fault); 
    switch_page_directory(kernel_directory);
}

void page_fault(registers_t regs){
    u32 fault_addr;
    asm volatile ("mov %%cr2, %0" : "=r"(fault_addr));
    int present = !(regs.err_code & 0x1);
    int rw      = regs.err_code & 0x2;
    int us      = regs.err_code & 0x4;
    int reserved= regs.err_code & 0x8;
    int id      = regs.err_code & 0x10;

    puts("\r\npage fault happened");
    if(present){ puts(" present"); }
    if(rw){ puts(" read-only");}
    if(us){ puts(" user-mode");}
    if(reserved){ puts(" reserved");}
    puts(" at 0x");
    putInt(fault_addr);
}

void switch_page_directory(page_directory_t *dir){
    current_directory = dir;
    /*
    asm volatile("mov %0, %%cr3":: "r"(&dir->tablesPhysical));
    u32 cr0;
    asm volatile("mov %%cr0, %0": "=r"(cr0));
    cr0 |= 0x80000000;
    asm volatile("mov %0, %%cr0":: "r"(cr0));
    */

    write_cr3(&dir->tablesPhysical);
    write_cr0(read_cr0()|0x80000000);
}

page_t *get_page(u32 address, int make, page_directory_t *dir){
    address /= 0x1000;
    u32 table_idx = address / 1024;
    if(dir->tables[table_idx]){
        return &dir->tables[table_idx]->pages[address % 1024];
    }

    if(make){
        u32 temp;
        dir->tables[table_idx] = (page_table_t *)kmalloc_ap(sizeof(page_table_t), &temp);
        dir->tablesPhysical[table_idx] = temp | 0x3;
        return &dir->tables[table_idx]->pages[address%1024];
    }

    puts("\r\n get page failed");
    return 0;
}

void alloc_frame(page_t *page, u8 is_kernel, u8 is_writeable){
    if(page->frame != 0){
        return;
    }else{
        u32 idx = first_frame();
        if(idx == -1){
            puts("\r\nalloc frame failed!");
            return;
        }
        set_frame(idx * 0x1000);
        page->present = 1;
        page->rw = is_writeable?1:0;
        page->us = is_kernel?0:1;
        page->frame = idx;
    }
}

void free_frame(page_t *page){
    u32 frame;
    if(!(frame=page->frame)){
        return;
    }else{
        clear_frame(frame);
        page->frame = 0;
    }
}
