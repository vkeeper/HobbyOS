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

void isr0(); // divide 0
void isr1(); // debug error
void isr2(); // nmi
void isr3(); // break point error
void isr4(); // overheap
void isr5(); // index out 
void isr6(); // not defined
void isr7(); // device error
void isr8(); // double error
void isr9(); // 
void isr10(); // invalid tss
void isr11(); // segment fault
void isr12(); // stack error
void isr13(); // protect
void isr14(); // page fault
void isr15(); // remain
void isr16(); // float handler error
void isr17(); // align check
void isr18(); // machine check
void isr19(); // float error

// remain
void isr20();
void isr21();
void isr22();
void isr23();
void isr24();
void isr25();
void isr26();
void isr27();
void isr28();
void isr29();
void isr30();
void isr31();

void isr255();

#endif
