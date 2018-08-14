#ifndef MEM_LAYOUT_H
#define MEM_LAYOUT_H

#include "common.h"

typedef struct{
    u64 base;
    u64 limit;
    u32 type;
} ARDSItem;

typedef struct{
    u32 len;
    ARDSItem items[0];
} BootParam;

u64 getPhysicalMemory();
#endif
