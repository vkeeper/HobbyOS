#include "print.h"
#include "common.h"

char* dispPos = (char*)0xB8000;

u8 digits[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

void putc(u8 c){
    if(c==13){
        dispPos = dispPos - (((unsigned int)dispPos)%160-64);
    }else if(c==10){
        dispPos += 160;
    }else{
        *(dispPos++)=c;
        *(dispPos++)=0x0F;
    }
}

void putByte(u8 byte){
    u8 h = byte >> 4;
    u8 l = byte & 0x0F;
    putc(digits[h]);
    putc(digits[l]);
}

void putInt(u32 integer){
    u8* bytes = (u8*)&integer;
    putByte(bytes[3]);
    putByte(bytes[2]);
    putByte(bytes[1]);
    putByte(bytes[0]);
}

void puts(u8* value){
    const u8* str=value;
    u8 c;
    while((c=*str++)!=0){
        putc(c);
    }
}
