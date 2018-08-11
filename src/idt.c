#include "common.h"
#include "idt.h"

extern void idt_flush(u32 addr);

void init_idt();

void idt_set_gate(u8 num, u32 base, u16 selector, u8 flags);

idt_entry_t idt_entries[256];

idt_ptr_t idt_ptr;

void init_idt(){
    puts("\r\n begin to init IDT");
    idt_ptr.limit = sizeof(idt_entry_t) * 256 -1;
    idt_ptr.base  = (u32)&idt_entries;

    memset(&idt_entries, 0, sizeof(idt_entry_t) * 256);
    puts("\r\nidt start at ");
    putInt((u32)&idt_ptr);
    puts(" ");
    putInt(idt_ptr.base);
    
    // init 8259A
    outb(PIC1, ICW1_M); 
    outb(PIC2, ICW1_S);
    
    // init interrupt vector 
    outb(PIC1, 0x20);
    outb(PIC2, 0x28);

    // init cascade line
    outb(PIC1, ICW3_M);
    outb(PIC2, ICW3_S);

    // init 8086 mode
    outb(PIC1, ICW4_M);
    outb(PIC2, ICW4_S);

    outb(PIC1, 0x0);
    outb(PIC2, 0x0);

    u32 selector = 0x08;
    idt_set_gate( 0, (u32)isr0 , selector, 0x8E);
    idt_set_gate( 1, (u32)isr1 , selector, 0x8E);
    idt_set_gate( 2, (u32)isr2 , selector, 0x8E);
    idt_set_gate( 3, (u32)isr3 , selector, 0x8E);
    idt_set_gate( 4, (u32)isr4 , selector, 0x8E);
    idt_set_gate( 5, (u32)isr5 , selector, 0x8E);
    idt_set_gate( 6, (u32)isr6 , selector, 0x8E);
    idt_set_gate( 7, (u32)isr7 , selector, 0x8E);
    idt_set_gate( 8, (u32)isr8 , selector, 0x8E);
    idt_set_gate( 9, (u32)isr9 , selector, 0x8E);
    idt_set_gate(10, (u32)isr10, selector, 0x8E);
    idt_set_gate(11, (u32)isr11, selector, 0x8E);
    idt_set_gate(12, (u32)isr12, selector, 0x8E);
    idt_set_gate(13, (u32)isr13, selector, 0x8E);
    idt_set_gate(14, (u32)isr14, selector, 0x8E);
    idt_set_gate(15, (u32)isr15, selector, 0x8E);
    idt_set_gate(16, (u32)isr16, selector, 0x8E);
    idt_set_gate(17, (u32)isr17, selector, 0x8E);
    idt_set_gate(18, (u32)isr18, selector, 0x8E);
    idt_set_gate(19, (u32)isr19, selector, 0x8E);
    idt_set_gate(20, (u32)isr20, selector, 0x8E);
    idt_set_gate(21, (u32)isr21, selector, 0x8E);
    idt_set_gate(22, (u32)isr22, selector, 0x8E);
    idt_set_gate(23, (u32)isr23, selector, 0x8E);
    idt_set_gate(24, (u32)isr24, selector, 0x8E);
    idt_set_gate(25, (u32)isr25, selector, 0x8E);
    idt_set_gate(26, (u32)isr26, selector, 0x8E);
    idt_set_gate(27, (u32)isr27, selector, 0x8E);
    idt_set_gate(28, (u32)isr28, selector, 0x8E);
    idt_set_gate(29, (u32)isr29, selector, 0x8E);
    idt_set_gate(30, (u32)isr30, selector, 0x8E);
    idt_set_gate(31, (u32)isr31, selector, 0x8E);
    
    idt_set_gate( 0, (u32)irq0 , selector, 0x8E);
    idt_set_gate( 1, (u32)irq1 , selector, 0x8E);
    idt_set_gate( 2, (u32)irq2 , selector, 0x8E);
    idt_set_gate( 3, (u32)irq3 , selector, 0x8E);
    idt_set_gate( 4, (u32)irq4 , selector, 0x8E);
    idt_set_gate( 5, (u32)irq5 , selector, 0x8E);
    idt_set_gate( 6, (u32)irq6 , selector, 0x8E);
    idt_set_gate( 7, (u32)irq7 , selector, 0x8E);
    idt_set_gate( 8, (u32)irq8 , selector, 0x8E);
    idt_set_gate( 9, (u32)irq9 , selector, 0x8E);
    idt_set_gate(10, (u32)irq10, selector, 0x8E);
    idt_set_gate(11, (u32)irq11, selector, 0x8E);
    idt_set_gate(12, (u32)irq12, selector, 0x8E);
    idt_set_gate(13, (u32)irq13, selector, 0x8E);
    idt_set_gate(14, (u32)irq14, selector, 0x8E);
    idt_set_gate(15, (u32)irq15, selector, 0x8E);

    puts("\r\nidt init table success");
    idt_flush((u32)&idt_ptr);
    puts("\r\nlidt execute success ");
    putInt((u32)&idt_ptr);
}

void idt_set_gate(u8 num, u32 base, u16 selector, u8 flags){
    idt_entries[num].base_low  = base & 0xFFFF;
    idt_entries[num].base_high = (base >> 16) & 0xFFFF;
    idt_entries[num].selector  = selector;
    idt_entries[num].zeros     = 0;
    idt_entries[num].flags     = flags;
}
