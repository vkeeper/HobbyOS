#include "common.h"
#include "print.h"
#include "mm.h"
#include "idt.h"
#include "timer.h"
#include "paging.h"

// #pragma pack(1)
typedef struct{
    u64 base;
    u64 limit;
    u32 type;
} ARDSItem;

typedef struct{
    u32 len;
    ARDSItem items[0];
} BootParam;

u64 getPhysicalMemory(){
    BootParam* bp = (BootParam*)0x500;
    u32 bplen = bp->len;
    u64 max = 0;
    
    putInt(bplen);
    puts("\r\n");
    ARDSItem* item = bp->items;
    for(;bplen>0;bplen--,item++){
        putInt(item->type);
        putc(' ');

        putInt(item->base);
        putc(' ');

        putInt(item->limit); puts("\r\n"); 
        switch(item->type){
            case 1: 
               //puts("Avaliable\r\n"); 
                break;
            case 3:
                //puts("ACPI\r\n");
                break;
            case 4:
                //puts("NVS");
                break;
            case 5:
                //puts("Unusable\r\n");
                continue;
            case 6:
                //puts("Disable\r\n");
                continue;
            default:
                //puts("Reserved\r\n");
                continue;
        }
        max = item->base + item->limit;
    } 
    puts("Memory: 0x");
    putInt(max/1024/1024);
    puts(" MB");
    return max;
}


void cmain(){
    init_idt();
    asm volatile ("int $0x3");
    asm volatile ("int $0x4");

    u64 mem = getPhysicalMemory();    

    init_paging(mem);
    puts("\r\npaging success!");
    u32 *ptr = (u32*)0xFF000;
    u32 do_page_fault = *ptr;
    asm volatile ("hlt");
    
    //asm volatile ("sti");
    //init_timer(100);
}
