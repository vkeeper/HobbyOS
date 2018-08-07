#include <stdlib.h>


char* dispPos = (char*)0xB8000;

u_int8_t digits[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

void putc(u_int8_t c){
    if(c==13){
        dispPos = dispPos - (((unsigned int)dispPos)%160-64);
    }else if(c==10){
        dispPos += 160;
    }else{
        *(dispPos++)=c;
        *(dispPos++)=0x0F;
    }
}

void putByte(u_int8_t byte){
    u_int8_t h = byte >> 4;
    u_int8_t l = byte & 0x0F;
    putc(digits[h]);
    putc(digits[l]);
}

void putInt(u_int32_t integer){
    u_int8_t* bytes = (u_int8_t*)&integer;
    putByte(bytes[3]);
    putByte(bytes[2]);
    putByte(bytes[1]);
    putByte(bytes[0]);
}

void puts(u_int8_t* value){
    const u_int8_t* str=value;
    u_int8_t c;
    while((c=*str++)!=0){
        putc(c);
    }
}

// #pragma pack(1)
typedef struct{
    u_int64_t base;
    u_int64_t limit;
    u_int32_t type;
} ARDSItem;

typedef struct{
    u_int32_t len;
    ARDSItem items[0];
} BootParam;

u_int64_t getPhysicalMemory(){
    BootParam* bp = (BootParam*)0x500;
    u_int32_t bplen = bp->len;
    u_int64_t max = 0;
    
    putInt(bplen);
    putc('\r');
    putc('\n');
    ARDSItem* item = bp->items;
    for(;bplen>0;bplen--,item++){
        putInt(item->type);
        putc(' ');

        putInt(item->base);
        putc(' ');

        putInt(item->limit);
        puts("\r\n");

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

void enablePaging(u_int64_t total){
    u_int32_t pageCount = total / 4096;
    puts("\r\ntotal page num ");
    putInt(pageCount);

    u_int32_t *pageDir =(u_int32_t *)0x2000;
    u_int32_t *pageTable = (u_int32_t *)0x3000;
    u_int32_t offset = 0;
    u_int32_t i=0;
    for(;i<1024;i++){
        pageTable[i]=offset|3;
        offset += 4096;
    }

    u_int32_t pageDirCount = pageCount/1024;
    if(pageCount%1024!=0){
        pageDirCount +=1;
    }

    pageDir[0]=pageTable;
    pageDir[0]=pageDir[0]|3;
    puts("\r\ntotal page dir ");
    putInt(pageDirCount);
    for(i=1;i<pageDirCount;i++){
        pageDir[i]=0|2;
    }
    write_cr3(pageDir);
    write_cr0(read_cr0()|0x80000000);
    puts("\r\nenable page memory success");
}

void cmain(){
    u_int64_t mem = getPhysicalMemory();    
    enablePaging(mem);
}

