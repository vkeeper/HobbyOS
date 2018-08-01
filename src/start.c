#include <stdlib.h>

char* dispPos = (char*)0xB8280;

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

void cmain(){
    
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

        putc('\r');
        putc('\n');
        switch(item->type){
            case 1: puts("Avaliable\r\n"); break;
            case 3: puts("ACPI\r\n"); break;
            case 4: puts("NVS"); break;
            case 5: puts("Unusable\r\n");continue;
            case 6: puts("Disable\r\n");continue;
            default:
                puts("Reserved\r\n");
                continue;
        }
        max = item->base + item->limit;
    } 
    max /= 1024*1024;
    puts("The size of memory:");
    putInt(max);
    puts("MB");
}

