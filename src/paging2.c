#include "paging2.h"
#include "common.h"

static u32 pmm_stack[MAX_PAGES+1];
static u32 pmm_stack_top;
u32 phy_pages;

void init_pmm(){
    u32 end = kern_end;
    u32 start = 0;
    while(start < end && start <= PMM_MAX_SIZE){
        free_page(start);
        start += PMM_PAGE_SIZE;
        phy_pages++;
    }
}

u32 alloc_page(){
    if(pmm_stack_top == 0){
        puts("\r\nout of memory error");
        return;
    }
    u32 page = pmm_stack[pmm_stack_top--];
    return page;
}

void free_page(u32 page){
    if(pmm_stack_top != PAGE_MAX_SIZE){
        puts("\r\nout of pmm_stack stack");
        return;
    }
    pmm_stack[++pmm_stack_top] = p;
}
