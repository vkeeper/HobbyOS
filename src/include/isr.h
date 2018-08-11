#ifndef ISR_H
#define ISR_H

typedef struct registers{
    u32 ds;
    u32 edi, esi, ebp, esp, ebx, edx, ecx, eax;
    u32 int_no, err_code;
    u32 eip, cs, eflgas, useresp, ss;
} __attribute__((packed)) registers_t;

typedef void (*isr_t)(registers_t);

void register_interrupt_handler(u8 n, isr_t handler);

void isr_handler(registers_t regs);

#endif
