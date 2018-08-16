%include "protect.inc"

section .init.text
[BITS 16]
kernelEntry:
    call enablePM 
    jmp dword SelectorCode32:Seg32Entry

enablePM:
    ; fast enable A20
    in al, 0x92
    or al, 2
    out 0x92, al
   
    ; save gdt
    xor eax, eax
    mov ax, ds
    shl ax, 4
    add eax, LabelGDT
    mov dword [GdtPtr+2], eax
    lgdt [GdtPtr]
    
    ; enable protectd mode
    cli
    mov eax, cr0
    or  eax, 1
    mov cr0, eax
    ret

;------------------------- Global Descriptor Init ------------------------
LabelGDT:			Descriptor  0,          0,              0
LabelDescCode32:    Descriptor  0,          0xFFFFF,        DA_32|DA_C
LabelDescData:      Descriptor  0,          0xFFFFF,        DA_32|DA_DRW
LabelDescVideo:     Descriptor  0xB8000,    0x0FFFF,        DA_DRW

GdtPtr: dw  $-LabelGDT-1
        dd  0

SelectorCode32  equ     LabelDescCode32 - LabelGDT
SelectorData    equ     LabelDescData   - LabelGDT
SelectorVideo   equ     LabelDescVideo  - LabelGDT
;---------------------------------------------------------------------------


[BITS 32]
Seg32Entry:
    ; --- init segment register ---
    mov ax, SelectorData
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov ax, SelectorVideo
    mov gs, ax

    ; --- init stack --- 
	;mov ebp, 0x60000
    ;mov esp, 0x9F000

    extern cmain
    call cmain
	hlt


;--------------------------------------------
global idt_flush
idt_flush:
	mov eax, [esp+4]
	lidt [eax]
	ret

global read_cr0
global write_cr0
global read_cr3
global write_cr3

read_cr0:
	mov eax, cr0
	retn

write_cr0:
	push ebp
	mov ebp, esp
	mov eax, [ebp+8]
	mov cr0, eax
	pop ebp
	retn

read_cr3:
	mov eax, cr3
	retn

write_cr3:
	push ebp
	mov ebp, esp
	mov eax, [ebp+8]
	mov cr3, eax
	pop ebp
	retn
