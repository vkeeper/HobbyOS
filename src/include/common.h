#ifndef COMMON_H
#define COMMON_H

#include <stdlib.h>

typedef u_int8_t  u8;
typedef u_int16_t u16;
typedef u_int32_t u32;
typedef u_int64_t u64;

void outb(u16 port, u8 value);

u8 inb(u16 port);

u16 inw(u16 port);

#endif
