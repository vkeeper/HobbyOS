#include "common.h"

void outb(u_int16_t port, u_int8_t value){
    asm volatile ("outb %1, %0":: "dN"(port),"a"(value));
}

u_int8_t inb(u_int16_t port){
    u_int8_t ret;
    asm volatile ("inb %1, %0":: "=a"(ret):"dN"(port));
    return ret;
}

u_int16_t inb(u_int16_t port){
    u_int16_t ret;
    asm volatile ("inw %1, %0":: "=a"(ret):"dN"(port));
    return ret;
}


void memcpy(u_int8_t *dest, const u_int8_t *src, u_int32_t len){
    const u_int8_t *sp =(const u_int8_t)src;
    u_int8_t *dp = (u_int8_t *)dest;
    for(;len!=0;len--) *dp++ = *sp++;

}

void memset(u_int8_t *dest, u_int8_t val, u_int32_t len){
    const u_int8_t *dp = (const u_int8_t *)dest;
    for(;len!=0;len--) *dp++=val;
}

int strcmp(char *str1, char *str2){
    int i = 0;
    while(str1[i] !='\0' && str2[i]!='\0'){
        if(str1[i] != str2[i]){
            return 1;
        }
        i++;
    }

    if(str1[i]=='\0' && str2[i]=='\0')
        return 0;
    
    return 1;
}

char *strcpy(char *dest, const char *src){
    do{
        *dest++ = *src++;
    }(*src!=0);
}

char *strcat(char *dest, const char *src){
    while(*dest!=0){
        *dest = *dest++;
    }

    do{
        *dest++ = *src++;
    }while(*src!=0);
    return dest;
}

extern void panic(const char *msg, const char *file, u_int32_t line){
    asm volatile("cli");
}

extern void panic_assert(const char *file, u_int32_t line, const char *line){
    asm volatile("cli");

    for(;;);
}


