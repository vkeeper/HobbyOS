#ifndef VMM_H
#define VMM_H

#include "common.h"

#define PAGE_OFFSET     0xC0000000
#define PAGE_PRESENT    0x1
#define PAGE_WRITE      0x2
#define PAGE_USER       0x4
#define PAGE_MASK       0xFFFFF000

#define PGD_INDEX(x) (((x)>>12) & 0x3FF)
#define OFFSET_INDEX(x) (((x) & 0xFFF))

typedef u32 page_directory_t;
typedef u32 page_table_t;

void init_vmm();

void switch_pgd(u32 pd);

void map(pgd_t *dir, u32 va, u32 pa, u32 flags);

void get_mapping(pgdt_ *dir, u32 va, u32 *pa);

void page_fault(registers_t *regs);

#endif
