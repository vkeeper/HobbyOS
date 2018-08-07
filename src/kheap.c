#include <stdlib.h>
#include "common.h"

extern u_int32_t max;
u_int32_t placement = (u_int32_t)&max;

u_int32_t kmalloc_a(u_32int_t size);
u_int32_t kmalloc_p(u_32int_t size, u_32int_t *phys);
u_int32_t kmalloc_ap(u_32int_t size, u_32int_t *phys);
u_int32_t kmalloc(u_32int_t size);

u_int64_t placement;

u_int32_t kmalloc_a(u_32int_t size){
    if(placement & 0xFFFF0000){
        placement &= 0xFFFF0000;
        placement += 0x1000;
    }
    u_int32_t temp=placement;
    placement += size;
    return temp;
}
u_int32_t kmalloc_p(u_32int_t size, u_32int_t *phys){
    if(placement & 0xFFFF0000){
        placement &= 0xFFFF0000;
        placement += 0x1000;
    }
    if(phys){
        *phys = placement;
    }

    u_int32_t temp=placement;
    placement += size;
    return temp;
}


u_int32_t kmalloc_ap(u_32int_t size, u_32int_t *phys){
    if(phys){
        *phys = placement;
    }
    u_int32_t temp=placement;
    placement += size;

    return temp;
}

u_int32_t kmalloc(u_32int_t size){
    u_int32_t temp=placement;
    placement += size;
    return temp;
}
