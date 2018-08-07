#ifndef KHEAP_H
#define KHEAP_H

#include "common.h"

u_int32_t kmalloc_int(u_int32_t size, int align, u_int32_t *phys);

u_int32_t kmalloc_a(u_int32_t size);

u_int32_t kmalloc_p(u_int32_t size, u_int32_t *phys);

u_int32_t kmalloc_ap(u_int32_t size, u_int32_t *phys);

u_int32_t kmalloc(u_int32_t size);

#endif
