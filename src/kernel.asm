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
   
    ; init selector address
    xor eax, eax
    mov ax,  cs
    shl ax,  0x4
    add eax, LabelStack
    mov word [LabelDescStack+2], ax
    mov byte [LabelDescStack+4], al
    mov byte [LabelDescStack+7], ah

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
LabelGDT:       Descriptor  0,          0,              0
LabelDescCode32:    Descriptor  0,          0xFFFFF,        DA_32|DA_C
LabelDescData:      Descriptor  0,          0xFFFFF,        DA_32|DA_DRW
LabelDescStack:     Descriptor  0,          TopOfStack,     DA_32|DA_DRW
LabelDescVideo:     Descriptor  0xB8000,    0x0FFFF,        DA_DRW

GdtPtr: dw  $-LabelGDT-1
        dd  0

SelectorCode32  equ     LabelDescCode32 - LabelGDT
SelectorData    equ     LabelDescData   - LabelGDT
SelectorStack   equ     LabelDescStack  - LabelGDT
SelectorVideo   equ     LabelDescVideo  - LabelGDT
;---------------------------------------------------------------------------

[BITS 32]
LabelStack:
    times 512 db 0

TopOfStack  equ     $-LabelStack-1


[SECTION .text]
[BITS 32]
Seg32Entry:
    ; --- init segment register ---
    mov ax, SelectorData
    mov ds, ax
    mov es, ax
    mov ax, SelectorVideo
    mov gs, ax
    mov ax, SelectorStack
    mov ss, ax
    mov esp,TopOfStack
    
    ; --- enable page memory management ---
    enablePaging:
        mov ebx, PTAddr
        mov eax, 0x3
        mov ecx, 1024
        .doPT:
            mov [ebx], eax
            add ebx, 4
            add eax, 0x1000
            loop .doPT

        xor ebx, ebx
        mov ebx, PDAddr
        mov eax, PTAddr + 0x3
        mov ecx, 1024
        .doPD:
            mov [ebx], eax
            add ebx, 4
            loop .doPD

        mov eax, PDAddr
        mov cr3, eax

        mov eax, cr4
        or  eax, 10000b
        mov cr4, eax

        mov eax, cr0
        or  eax, 0x80000000
        mov cr0, eax
    ; --- call c function ---
    extern cmain
    call cmain
    hlt

