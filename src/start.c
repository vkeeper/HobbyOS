#include <stdlib.h>

typedef struct{
    u_int64_t base;
    u_int64_t limit;
    u_int32_t type;
} ARDSItem;

typedef struct{
    u_int32_t len;
    ARDSItem items[0];
} BootParam;

char* dispPos = (char*)0xB8000;
void puts(char* str){
    unsigned int absolutePos = (80*3+0)*2;
    dispPos += absolutePos;
    unsigned char c;
    while((c=*(str++))!=0){
        if(c==13){
            dispPos -=((unsigned int)dispPos)%160-64;
        } else if(c==10){
            dispPos += 160;
        }else{
            *(dispPos++)=c;
            *(dispPos++)=0x0F;
        }
    }
    
}

void cmain(){
    puts("\nget memory info from 0x500");
    BootParam* bp = (BootParam*)0x500;
    u_int32_t bplen = bp->len;
    u_int64_t max = 0;

    puts("\nsuccess save memory info");
}

