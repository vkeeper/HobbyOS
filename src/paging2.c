#include "paging2.h"
#include "common.h"

static u32 *pmm_stack;
static u32 pmm_stack_top;
u32 phy_pages;

void init_pmm(u64 max){
    u64 end = max;
    u32 start = (u32)&kern_end;
    start &= 0xFFFFF000;
    start += 0x1000;

    while(start < end && start < PMM_MAX_SIZE){
        free_page(start);
        start += PMM_PAGE_SIZE;
        phy_pages++;
    }
}

u32 alloc_page(){
    if(pmm_stack_top == 0){
        puts("\r\nout of mmory error");
        return -1;
    }
    u32 page = pmm_stack[--pmm_stack_top];
    return page;
}

void free_page(u32 page){
    if(pmm_stack_top == MAX_PAGES){
        puts("\r\nout of pmm_stack stack");
        return;
    }
    pmm_stack[pmm_stack_top++] = page;
}
