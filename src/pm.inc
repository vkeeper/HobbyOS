; 3 Arguments
; Descriptor (Base, Limit, Attribute)

%macro Descriptor 3
    dw %2 & 0xFFFF
    dw %1 & 0xFFFF
    db (%1>>16) & 0xFF
    dw (%3 & 0xF0FF)|((%2>>16) & 0x0F00)
    db (%1>>24) & 0xFF
%endmacro

%macro GdtPointer 2
    dw   %2-1
    dd   %1
%endmacro

; Segment Descriptor Attribute
DPL_0   equ     0
DPL_1   equ     0x20
DPL_2   equ     0x40
DPL_3   equ     0x60

; Segment Type
TYPE_CODE  equ     0x8 ; defulat can execute
TYPE_DATA  equ     0x0 ; default can read

; access flag of type
TYPE_A     equ     0x1

; data segment only
TYPE_W     equ     0x2    
TYPE_E     equ     0x4 

; code segment only
TYPE_R     equ     0x2
TYPE_C     equ     0x4

S_G     equ     0x8000
S_P     equ     0x80
S_S     equ     0x10
S_DB    equ     0x4000
S_AVL   equ     0x1000

SDA_FLAT_CODE   equ     TYPE_CODE|S_DB|S_P|S_S|TYPE_C|TYPE_R|TYPE_A
SDA_FLAT_DATA   equ     TYPE_DATA|S_DB|S_P|S_S|TYPE_W|TYPE_A

; Detect Mem Address
MemTableAddr    equ     0x50
ARDSNum         equ     0x0
ARDSAddrOffset  equ     ARDSNum + 0x4


;memCheckError dw "detect memory map by INT 0x15 failed......",0xD, 0xA, 0

