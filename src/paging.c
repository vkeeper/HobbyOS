#include "paging.h"
#include <stdlib.h>


page_directory_t *kernel_directory = 0;
page_table_t     *kernel_table     = 0;

u_int32_t *frames;
u_int32_t nframes;

extern u_int32_t placement_address;

#define INDEX_FROM_BIT(a)(a/(8*4))
#define OFFSET_FROM_BIT(a)(a%(8*4))

static void set_frame(u_int32_t frame_addr){
    u_int32_t frame = frame_addr/0x1000;
    u_int32_t idx = INDEX_FROM_BIT(frame);
    u_int32_t off = OFFSET_FROM_BIT(frame);
    frames[idx] |= (0x1 << off);
}

static void clear_frame(u_int32_t frame_addr){
    u_int32_t frame = frame_addr/0x1000;
    u_int32_t idx = INDEX_FROM_BIT(frame);
    u_int32_t off = OFFSET_FROM_BIT(frame);
    frames[idx] &= ~(0x1 << off);
}

static u_int32_t test_frame(u_int32_t frame_addr){
    u_int32_t frame = frame_addr/0x1000;
    u_int32_t idx = INDEX_FROM_BIT(frame);
    u_int32_t off = OFFSET_FROM_BIT(frame);
    return (frames[idx] & (0x1 << off));
}

static u_int32_t first_frame(){
    u_int32_t i, j;
    for(i = 0; i < INDEX_FROM_BIT(nframes);i++){
        if(frames[i]!=0xFFFFFFFF){
            for(j = 0; j < 32; j++){
                u_int32_t toTest = 0x1 << j;
                if(!(frames[i] & toTest)){
                    return i*4*8+j;
                }
            }
        }
    }
}


void alloc_frame(page_t *page, int is_kernel, int is_writeable){
    if(page->frame != 0){
        return;
    }else{
        u_int32_t idx = first_frame();
        if(idx == (u_int32_t)-1){
            //PANIC("No free frames");
            return;
        }

        set_frame(idx * 0x1000);
        page->present = 1;
        page->rw = (is_writeable)?1:0;
        page->user = (is_kernel)?0:1;
        page->frame = idx;
    }
}

void free_frame(page_t *page){
    u_int32_t frame;
    if(!(frame=page->frame)){
        return;
    }else{
        clear_frame(frame);
        page->frame = 0x0;
    }
}

void initialise_paging(){
    

}
