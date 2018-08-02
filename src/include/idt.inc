; Interrupt Descriptor
; 0 - Selector
; 1 - offset
; 2 - attribute
%macro GateDescriptor 3
    dw  %2&0xFFFF
    dw  %1
    db  0
    db  %3
    dw  %2>>16
%endmacro

;-------------------- IDT Attribute -----------------
IDT_TYPE_TASK   equ     0x5
IDT_TYPE_INT    equ     0xE
IDT_TYPE_TRAP   equ     0xF

IDT_DPL1        equ     0x20
IDT_DPL2        equ     0x40
IDT_DPL3        equ     0x60

IDT_P           equ     0x80
IDT_S           equ     0x10
;---------------------------------------------------
