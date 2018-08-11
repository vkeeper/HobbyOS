%include "protect.inc"

[BITS 16]
kernelEntry:
    call probeMemory
    call enablePM 
    jmp dword SelectorCode32:Seg32Entry

probeMemory:
    xor cx, cx
    xor dx, dx
    mov ax, MemTableAddr
    mov es, ax
    mov di, ARDSAddrOffset
    mov dword [es:ARDSNum], 0
    mov ebx, 0
    .loop:
        mov edx, 0x534D4150
        mov eax, 0xE820
        mov ecx, 20
        int 0x15
        jc .fail
        add di, 20
        inc dword [es:ARDSNum]
        or  ebx, ebx 
        jnz .loop
        jmp .ok 

    .fail:
        mov  si, memCheckError
        call printByInt10
        cli
        hlt
    .ok:
        ret

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

printByInt10:
     mov al, [si]
     xor al, 0
     jz printByInt10End
     inc si
     mov bx, 0x000F
     mov ah, 0xE 
     int 0x10
     jmp printByInt10

printByInt10End:
    ret

memCheckError: dw "check memory map error!",0

;------------------------- Global Descriptor Init ------------------------
LabelGDT:			Descriptor  0,          0,              0
LabelDescCode32:    Descriptor  0,          0xFFFFFFFF,        DA_32|DA_C
LabelDescData:      Descriptor  0,          0xFFFFFFFF,        DA_32|DA_DRW|DA_DPL0
LabelDescVideo:     Descriptor  0xB8000,    0x0FFFF,        DA_DRW

GdtPtr: dw  $-LabelGDT-1
        dd  0

SelectorCode32  equ     LabelDescCode32 - LabelGDT
SelectorData    equ     LabelDescData   - LabelGDT
SelectorVideo   equ     LabelDescVideo  - LabelGDT
;---------------------------------------------------------------------------


[SECTION .text]
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
	mov ebp, 0x80000
	mov esp, 0x9FBFF

    extern cmain
    call cmain
    hlt



global idt_flush
idt_flush:
	mov eax, [esp+4]
	lidt [eax]
	ret

idtStr: db "success flush idt"
;--------------------------------------------
printByGS:
    xor eax, eax 
    mov ah, 0x0F
    .loopShow:
        mov byte al, [esi]
        xor al, 0
        jz printByGSEnd 
        inc esi 
 
        mov word [gs:edi], ax
        inc edi 
        inc edi 
        jmp .loopShow

printByGSEnd:
    ret

;--------------------------------------------

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
