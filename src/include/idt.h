#ifndef IDT_H
#define IDT_H

typedef struct idt_entry{

    u16 base_low;
    u16 selector;
    u8 zeros;
    u8 flags;
    u16 base_high;
} idt_entry_t;

typedef struct idt_ptr{

    u16 limit;
    u32 base;
} idt_ptr_t;

typedef pt_regs {
    u32 ds;
    u32 edi;
    u32 esi;
    u32 ebp;
    u32 esp;
    u32 ebx;
    u32 edx;
    u32 ecx;
    u32 eax;
    u32 int_no;
    u32 err_code;
    u32 eip;
    u32 cs;
    u32 eflags;
    u32 useresp;
    u32 ss;
} pt_regs_t;

typedef void (*interrupt_handler_t)(pt_regs_t *);

void register_interrupt_handler(u8 n, interrupt_handler_t h);

void isr_handler(pt_regs_t *regs);

extern void isr0 ();
extern void isr1 ();
extern void isr2 ();
extern void isr3 ();
extern void isr4 ();
extern void isr5 ();
extern void isr6 ();
extern void isr7 ();
extern void isr8 ();
extern void isr9 ();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

#endif
