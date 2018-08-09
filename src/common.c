#include "common.h"

void outb(u16 port, u8 value)
{
    asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

u8 inb(u16 port)
{
   u8 ret;
   asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
}

u16 inw(u16 port)
{
   u16 ret;
   asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
}

void memset(u8 *dest, u8 val, u32 len){
    u8 *temp = (u8 *)dest;
    for(; len !=0; len--){
        *temp++ = val;
    }
}

void memcpy(u8 *dest, const u8 *src, u32 len){
    for(; len != 0; len--){
        *dest++ = *src++;
    }
}

int strcmp(char *str1, char *str2){
    u32 i = 0;
    while(str1[i] != 0 && str2[i] != 0){
        if(str1[i] != str2[i]){
            return 0;
        }
        i++;
    }
    
    if(str1[i] == 0 && str2[i] == 0){
        return 1;
    }
    return 0;
}

void strcpy(char *dest, const char *src){
    char *temp = src;
    while(*temp != 0){
        *dest++ = *temp++;
    }
}

char *strcat(char *dest, const char *src){
    while(*dest!=0){
        *dest = *dest++;
    }

    while(*src != 0){
        *dest++ = *src++;
    }
    return dest;
}
