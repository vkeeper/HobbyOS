#ifndef PAGEING_H
#define PAGING_H

#include "common.h"
#include "mem_layout.h"

#define PMM_MAX_SIZE    0x20000000
#define PMM_PAGE_SIZE   0x1000
#define MAX_PAGES   (PMM_MAX_SIZE/PMM_PAGE_SIZE)
#define PHY_PAGE_MASK   0xFFFFF000

void init_pmm();

u32 alloc_page();

void free_page();

#endif
