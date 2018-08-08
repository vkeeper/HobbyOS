#include "common.h"
#include "mm.h"


u32 kmalloc(u32 size){
    u32 temp = placement_address;
    placement_address += size;
    return temp;
}

u32 kmalloc_a(u32 size){
    u32 temp = placement_address;
    placement_address += size;
    return temp;
}

u32 kmalloc_p(u32 size, u32 align){
    if(align == 1 && (placement_address & 0xFFFFF000)){
        placement_address &= 0xFFFFF000;
        placement_address += 0x1000;
    }
    
    u32 temp = placement_address;
    placement_address += size;
    return temp;
}

u32 kmalloc_ap(u32 size, u32 align, u32 *phys){
    if(align == 1 && (placement_address & 0xFFFFF000)){
        placement_address &= 0xFFFFF000;
        placement_address += size;
    }

    if(phys){
        *phys = placement_address;
    }

    u32 temp = placement_address;
    placement_address += size;
    return temp;
}
