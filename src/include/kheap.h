#ifndef KHEAP_H
#define KHEAP_H

#include "common.h"
#include "ordered_array.h"

#define KHEAP_START         0xC0000000
#define KHEAP_INIT_SIZE     0x100000

#define HEAP_INDEX_SIZE     0x20000
#define HEAP_MAGIC          0x123890AB
#define HEAP_MIN_SIZE       0x70000


typedef struct{
    u32 magic;
    u32 is_hole;
    u32 size;
} header_t;


typedef struct{
    u32 magic;
    header_t *header;
} footer_t;

typedef strcut{
    ordered_array_t index;
    u32 start_addr;
    u32 end_addr;
    u32 max;
    u8 supervisor;
    u8 readonly;
} heap_t;

heap_t *create_heap(u32 start, u32 end, u32 max, u8 supervisor, u8 readonly);

void *alloc(u32 size, u8 page_align, heap_t *heap);

void free(void *p, heap_t *heap);

#endif
