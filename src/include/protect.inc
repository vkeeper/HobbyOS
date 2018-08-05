;-------------------------------------------------------
; base, limit, attr 
;-------------------------------------------------------
%macro Descriptor 3
    dw %2 & 0xFFFF
    dw %1 & 0xFFFF
    db (%1>>16) & 0xFF
    dw (%3 & 0xF0FF)|((%2>>8) & 0x0F00)
    db (%1>>24) & 0xFF
%endmacro

%macro GdtPointer 2
    dw   %2-1
    dd   %1
%endmacro

;-------------------------------------------------------
; selector,offset,dcount,attr
;-------------------------------------------------------
%macro GateDescriptor 3
    dw (%2 & 0xFFFF)
    dw %1
    dw (%3&0x1F)|((%4<<8)&0xFF00)
    dw ((%2>>16)&0xFFFF)
%endmacro

;--------------------------------------------------------
; Segment Descriptor Attribute
;--------------------------------------------------------

DA_32     equ     0x4000
DA_DPL0   equ     0
DA_DPL1   equ     0x20
DA_DPL2   equ     0x40
DA_DPL3   equ     0x60

DA_DR     equ     0x90
DA_DRW    equ     0x92
DA_DRWA   equ     0x93

DA_C      equ     0x98
DA_CR     equ     0x9A
DA_CCO    equ     0x9C
DA_CCOR   equ     0x9E

;--------------------------------------------------------
; system segment descriptor
;--------------------------------------------------------
DA_LDT          equ     0x82
DA_TaskGate     equ     0x85
DA_386TSS       equ     0x89
DA_386CGate     equ     0x8C
DA_386IGate     equ     0x8E
DA_386TGat      equ     0x8F

;--------------------------------------------------------
;selector attribute
;--------------------------------------------------------
SA_RPL0         equ     0x0
SA_RPL1         equ     0x1
SA_RPL2         equ     0x2
SA_RPL3         equ     0x3

SA_TIG          equ     0x0
SA_TIL          equ     0x4 ; Local Descriptor


SDA_FLAT_CODE   equ     DA_32|DA_CR
SDA_FLAT_DATA   equ     DA_DRW

;--------------------------------------------------------
; Detect Mem Address
;--------------------------------------------------------
MemTableAddr    equ     0x50
ARDSNum         equ     0x0
ARDSAddrOffset  equ     ARDSNum + 0x4

;--------------------------------------------------------
; paging memory management
;--------------------------------------------------------
PDAddr  equ     0x2000
PTAddr  equ     0x3000


