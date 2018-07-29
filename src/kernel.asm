org 0x9000

%include "pm.inc"

;TODO enable interrupt vector

;TODO enable second-level page memory management
[BITS 16]
entry:
    call probeMem
	call enableA20
	call enablePM

; detect memory
probeMem:
    xor cx, cx
    xor dx, dx

    mov ax, MemTableAddr
    mov es, ax
    mov di, ARDSAddrOffset
    mov dword [es:ARDSNum], 0
    mov ebx, 0
    .loop:
        ; This is ASCII: "SMAP"
        mov edx, 0x534D4150
        mov eax, 0xE820
        mov ecx, 20
        int 0x15
        jc .fail
        add di, 20
        inc dword [es:ARDSNum]
        or ebx, ebx
        jnz .loop
        jmp .ok

    .fail:
        mov si, memCheckError
        call printByInt
        cli
        hlt
    .ok:
        ret

printByInt:
    mov al, [si]
    xor al, 0
    jz end 
    inc si
    mov bx, 0x000F
    mov ah, 0xE 
    int 0x10
    jmp printByInt 


; Fast A20 Gate
enableA20:	
	in al, 0x92
	or al, 2
	out 0x92, al
	ret

; enable protected mode
enablePM:
    xor eax, eax
    mov ax, ds

    shl ax, 4
    add eax, SegmentNone
    mov dword [GdtPtr+2], eax
	lgdt [GdtPtr]

	cli
	mov eax, cr0
	or al, 1
	mov cr0, eax

    jmp dword SEL_FLAT_CODE:pmEntry

SegmentNone:	Descriptor	0,		0,				0
SegmentCode:	Descriptor	0,		0xFFFFF,		SDA_FLAT_CODE
SegmentData:	Descriptor	0,		0xFFFFF,		SDA_FLAT_DATA
SegmentVideo:   Descriptor  0xB8000,0x0FFFF,        SDA_FLAT_DATA

;GdtPtr:
;	GdtPointer	SegmentNone+0x9000, $-SegmentNone
GdtPtr: dw  $-SegmentNone-1
        dd  0

SEL_FLAT_DATA   equ SegmentData - SegmentNone
SEL_FLAT_CODE   equ SegmentCode - SegmentNone
SEL_VIDEO       equ SegmentVideo- SegmentNone

[BITS 32]
pmEntry:
    call initReg

    mov esi, enablePMStr 
    call printByGS

initReg:
	mov ax, SEL_FLAT_DATA 
	mov ds, ax
	mov es, ax
    mov ss, ax
    mov ax, SEL_VIDEO
    mov gs, ax
    ret

printByGS:
    xor eax, eax
    mov ah, 0x0F

    mov edi, (80*2+0)*2
    .loopShow:
        mov byte al, [esi]
        xor al, 0
        jz end 
        inc esi
        
        mov word [gs:edi], ax
        inc edi
        inc edi

        jmp .loopShow

end:
    hlt

enablePMStr: dw "Success enable Protected mode",0xA,0
memCheckError: dw "Detect memory error happend",0
