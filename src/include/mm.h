#ifndef MM_H
#define MM_H

#include "common.h"

u32 kmalloc_a(u32 size);

u32 kmalloc_p(u32 size, u32 align);

u32 kmalloc_ap(u32 size, u32 align, u32 *phys);

u32 kmalloc(u32 size);

#endif
