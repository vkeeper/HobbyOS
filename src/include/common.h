#ifndef COMMON_H
#define COMMON_H

#include <stdlib.h>

typedef u_int8_t  u8;
typedef u_int16_t u16;
typedef u_int32_t u32;
typedef u_int64_t u64;

extern u8 kern_start[];
extern u8 kern_end[];

extern u64 read_cr3();
extern void write_cr3(u32 v);

extern u64  read_cr0();
extern void write_cr0();

void outb(u16 port, u8 value);

u8 inb(u16 port);

u16 inw(u16 port);


void memset(u8 *dest, u8 val, u32 len);

void memcpy(u8 *dest, const u8 *src, u32 len);

int strcmp(char *str1, char *str2);

void strcpy(char *dest, const char *src);

char *strcat(char *dest, const char *src);

#endif
