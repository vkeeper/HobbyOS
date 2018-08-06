#include <stdlib.h>

u_32int_t kmalloc_a(u_32int_t size);
u_32int_t kmalloc_p(u_32int_t size, u_32int_t *phys);
u_32int_t kmalloc_ap(u_32int_t size, u_32int_t *phys);
u_32int_t kmalloc(u_32int_t size);

u_64int_t placement;

u_32int_t kmalloc_a(u_32int_t size){
    if(placement & 0xFFFF0000){
        placement &= 0xFFFF0000;
        placement += 0x1000;
    }
    u_32int_t temp=placement;
    placement += size;
    return temp;
}
u_32int_t kmalloc_p(u_32int_t size, u_32int_t *phys){
    if(placement & 0xFFFF0000){
        placement &= 0xFFFF0000;
        placement += 0x1000;
    }
    if(phys){
        *phys = placement;
    }

    u_32int_t temp=placement;
    placement += size;
    return temp;
}


u_32int_t kmalloc_ap(u_32int_t size, u_32int_t *phys){
    if(phys){
        *phys = placement;
    }
    u_32int_t temp=placement;
    placement += size;

    return temp;
}

u_32int_t kmalloc(u_32int_t size){
    u_32int_t temp=placement;
    placement += size;
    return temp;
    
}
