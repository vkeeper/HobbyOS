SECTIONS
{
    PROVIDE( kern_start = 0xC0009000);
    . = 0x9000;

    .init.text :
    {
        *(.init.text)    
    }

    .init.data :
    {
        *(.init.data)
    }

    . += 0xC0000000;
    .text : AT(ADDR(.text) - 0xC0000000)
    { 
        *(.text*) 
    }

    .data : AT(ADDR(.data) - 0xC0000000)
    {
        *(.data) 
        *(.rodata*)
    }

    .bss : AT(ADDR(.bss) - 0xC0000000)
    {
        *(.bss)
        *(COMMON)
    }
    .stab : AT(ADDR(.stab) - 0xC0000000)
    {
        *(.stab)
    }

    .stabstr : AT(ADDR(.stabstr) - 0xC0000000)
    {
        *(.stabstr)
    }

    PROVIDE( kern_end = .);
    /DISCARD/ : { *.* }
}
/* 紧凑内存结构 */
