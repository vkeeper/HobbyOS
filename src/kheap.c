#include "common.h"
#include "kheap.h"
#include "ordered_array.h"

static u32 find_smalleset_hol(u32 size, u8 page_align, heap_t *heap){
    u32 itr;
    while(itr < heap->index.size){
        headere_t *header =  (header_t *)lookup_ordered_array(itr, &heap->index);
        if(page_align){
            u32 location = (u32)header;
            u32 offset = 0;
            if((location + sizeof(header_t)) & 0xFFFFF000 != 0){
                offset = 0x1000 - (location+sizeof(header_t))%0x1000;
            }

            u32 hole_size = (u32)header->size - offset;
            if(hole_size >= (u32)size){
                break;
            }
        }else if( header->size >= size){
            break;
        }

        itr++;
    }

    if(itr == heap->index.size){
        return -1;
    }else{
        return itr;
    }
}

static u8 header_t_less_than(void *a, void *b){
    return (((header_t*)a)->size < ((header_t*)b)->size)?1:0;
}

heap_t *create_heap(u32 start, u32 end, u32 max, u8 user, u8 readonly){
    heap_t *heap = (heap_t *)kmalloc(sizeof(heap_t));
    heap->index = place_ordered_array((void*)start, HEAP_INDEX_SIZE, &header_t_less_than);
    start += sizeof(element_t)*HEAP_INDEX_SIZE;
    if(start & 0xFFFFF000 != 0){
        start &= 0xFFFFF000;
        start += 0x1000;
    }

}

