#ifndef COMMON_H
#define COMMON_H

void outb(u_int16_t port, u_int16_t value);
u_int8_t inb(u_int16_t port);
u_int16_t inw(u_int16_t port);

#define PANIC(msg) panic(msg, __FILE__, __LINE__);
#define ASSERT(b)((b)?(void)0:panice_assert(__FILE__, __LINE__, #b))

extern void panic(const char *msg, const char *file, u_int32_t line);
extern void panice_assert(const char *file, u_int32_t line, const char * desc);

#endif
