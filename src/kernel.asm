org 0x9000

%include "pm.inc"

;TODO enable interrupt vector

;TODO enable second-level page memory management
entry:
    call initMReg
	call enableA20
	call enablePM

;    mov si, enablePMStr
;    call showStr

    hlt
    jmp $

initMReg:
    mov ax, cs
    mov ds, ax
    mov es, ax
    ret

; Fast A20 Gate
enableA20:	
	in al, 0x92
	or al, 2
	out 0x92, al
	ret

; enable protected mode
enablePM:
	cli
	lgdt [GdtPtr]
	mov eax, cr0
	or al, 1
	mov cr0, eax
;    jmp dword 0x08:(pmEntry)
    jmp SEL_FLAT_CODE:0 

SegmentNone:	Descriptor	0,		0,				0
SegmentCode:	Descriptor	0,		0xFFFFF,		SDA_FLAT_CODE
SegmentData:	Descriptor	0,		0xFFFFF,		SDA_FLAT_DATA

GdtPtr:
	GdtPointer	SegmentNone+0x20000, $-SegmentNone

SEL_FLAT_DATA   equ SegmentData - SegmentNone
SEL_FLAT_CODE   equ SegmentCode - SegmentNone

[BITS 32]
pmEntry:
	mov ax, SEL_FLAT_DATA 
	mov ds, ax
	mov es, ax
	mov ss, ax
	ret

showStr:
    xor eax, eax
    mov eax, 0xB8000
    mov ebp, eax 
    .loopShow:
        xor ax, ax
        mov al, [si]
        xor al, 0
        jz end 
        inc si

        mov ah, 0x2a
        mov word [ebp], ax
        inc ebp 
        inc ebp
        jmp .loopShow


end:
    ret

enablePMStr dw "Success into Protected mode", 0xA,0
msg: db "This is print by 0XB8000",0
