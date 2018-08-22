SECTIONS
{
    PROVIDE( kern_start = .);
    . = 0x9000;

    .init.text :
    {
        *(.init.text)    
    }

    .init.data :
    {
        *(.init.data)
    }

    .text : 
    { 
        *(.text*) 
    }

    .data : 
    {
        *(.data) 
        *(.rodata*)
    }

    .bss : 
    {
        *(.bss)
        *(COMMON)
    }
    .stab : 
    {
        *(.stab)
    }

    .stabstr : 
    {
        *(.stabstr)
    }

    PROVIDE( kern_end = .);
    /DISCARD/ : { *.* }
}
/* 紧凑内存结构 */
