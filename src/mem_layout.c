#include "mem_layout.h"

u64 getPhysicalMemory(){
    BootParam* bp = (BootParam*)0x20000;
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

