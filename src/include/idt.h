#ifndef IDT_H
#define IDT_H

#define PIC1            0x20
#define PIC2            0xA0
#define PIC1_COMMAND    PIC1
#define PIC1_DATA       (PIC1+1)
#define PIC2_COMMAND    PIC2
#define PIC2_DATA       (PIC2+1)

#define INT_VECTOR_IRQ0     32
#define INT_VECTOR_IRQ8     INT_VECTOR_IRQ0+8

#define ICW1_M            0x11
#define ICW1_S            0x11
#define ICW2_M            INT_VECTOR_IRQ0
#define ICW2_S            INT_VECTOR_IRQ8
#define ICW3_M            0x4
#define ICW3_S            0x2
#define ICW4_M            0x1
#define ICW4_S            0x1

typedef struct idt_entry{
    u16 base_low;
    u16 selector;
    u8 zeros;
    u8 flags;
    u16 base_high;
} __attribute__((packed)) idt_entry_t; 

typedef struct idt_ptr{
    u16 limit;
    u32 base;
}__attribute__((packed)) idt_ptr_t; 


void init_idt();

#define IRQ0    32
#define IRQ0    33
#define IRQ0    34
#define IRQ0    35
#define IRQ0    36
#define IRQ0    37
#define IRQ0    38
#define IRQ0    39
#define IRQ0    40
#define IRQ0    41
#define IRQ0    42
#define IRQ0    43
#define IRQ0    44
#define IRQ0    45
#define IRQ0    46
#define IRQ0    47

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

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

void isr255();

#endif
