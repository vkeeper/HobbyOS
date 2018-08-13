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
/*
void enablePaging(u64 total){
    u32 pageCount = total / 4096;
    puts("\r\ntotal page num ");
    putInt(pageCount);

    u32 *pageDir =(u32 *)0x2000;
    u32 *pageTable = (u32 *)0x3000;
    u32 offset = 0;
    u32 i=0;
    for(;i<1024;i++){
        pageTable[i]=offset|3;
        offset += 4096;
    }

    u32 pageDirCount = pageCount/1024;
    if(pageCount%1024!=0){
        pageDirCount +=1;
    }

    pageDir[0]=pageTable;
    pageDir[0]=pageDir[0]|3;

    for(i=1;i<pageDirCount;i++){
        pageDir[i]=0|2;
    }
    write_cr3(pageDir);
    write_cr0(read_cr0()|0x80000000);
}
*/

void cmain(){
    u64 mem = getPhysicalMemory();    
    //enablePaging(mem);
    init_idt();
    asm volatile ("int $0x3");
    asm volatile ("int $0x4");

    init_paging(mem);
    /**
    asm volatile ("sti");
    init_timer(100);
    */
}

