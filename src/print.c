#include "print.h"
#include "common.h"

u16* dispPos = (u16*)0xB8000;

u8 cursor_x = 0;
u8 cursor_y = 0;

u8 digits[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

static void move_cursor(){
    u16 cursor_location = cursor_y * 80 + cursor_x;
    outb(0x3D4, 14);
    outb(0x3D5, cursor_location >> 8);
    outb(0x3D4, 15);
    outb(0x3D5, cursor_location);
}

static void scroll(){
    u8 attr = (0 << 4) | (15 & 0x0F);
    u16 blank = 0x20 | (attr << 8);
    if(cursor_y >= 25){
        int i;
        for(i = 0*80; i<24*80;i++){
            dispPos[i] = dispPos[i+80];
        }

        for(i = 24*80; i<25*80; i++){
            dispPos[i] = blank;
        }
        cursor_y = 24;
    }
}

void putc(u8 c){
    u8 color = 0x0F;
    u16 value = color<<8|c;
    if(c == '\r'){
//        dispPos = dispPos - (((unsigned int)dispPos%160)-64);
        cursor_x = 0;
    }else if(c == '\n'){
//        dispPos += 160;
        cursor_y++;
    }else if(c >= ' '){
        u16 *addr;
        addr = dispPos + (cursor_y*80+cursor_x);
        *addr = value;
        cursor_x++;
    }

    if(cursor_x >= 80){
        cursor_x = 0;
        cursor_y++;
    }

    scroll();
    move_cursor();
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
