%include "pm.inc"

[BITS 16]
entry:
    call probeMem
	call enableA20
	call enablePM
	call enableIDT
    jmp dword SEL_FLAT_CODE:pmEntry

%include "lib16.inc"

; detect memory
; save memory map at 0x500
probeMem:
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

	; init and save GdtPtr
    shl ax, 4
    add eax, SegmentNone
    mov dword [GdtPtr+2], eax
	lgdt [GdtPtr]
	cli

	; enable protected mode
	mov eax, cr0
	or  al, 1
	mov cr0, eax
	ret

; -------------------- init segment descriptors -----------------
SegmentNone:	Descriptor	0,		0,				0
SegmentCode:	Descriptor	0,		0xFFFFF,		SDA_FLAT_CODE
SegmentData:	Descriptor	0,		0xFFFFF,		SDA_FLAT_DATA
SegmentVideo:   Descriptor  0xB8000,0x0FFFF,        SDA_FLAT_DATA

GdtPtr: dw  $-SegmentNone-1
        dd  0

; init segment selectors
SEL_FLAT_DATA   equ SegmentData - SegmentNone
SEL_FLAT_CODE   equ SegmentCode - SegmentNone
SEL_VIDEO       equ SegmentVideo- SegmentNone

;-----------------------------------------------------------------

%include "idt.inc"
enableIDT:
	mov ax, ds
	shl ax, 4
	add eax, IDTTable
	mov dword [IdtPtr+2], eax
	lidt [IdtPtr]
	ret

;--------------------------init interrupt descriptors -------------
IDTTable:	GateDescriptor	SEL_FLAT_CODE,	int0funcAddr,	IDT_TYPE_INT|IDT_P
IdtPtr:	dw $-IDTTable-1
		dd 0

;-----------------------------------------------------------------

[BITS 32]
[section .text]

%include "lib32.inc"
extern cmain

pmEntry:
    call initReg
	call enablePaging
	int 0

int0func:
int0funcAddr	equ	int0func-$$+0x9000
	call cmain
	cli
	hlt

initReg:
	mov ax, SEL_FLAT_DATA 
	mov ds, ax
	mov es, ax
    mov ss, ax
    mov ax, SEL_VIDEO
    mov gs, ax
	; print message
    mov esi, enablePMStr 
	mov edi, (80*2+0)*2
    call printByGS
    ret

; directory:table = 1:1
enablePaging:
	;4*1024 byte page directory
	mov ebx, PTAddr
	mov eax, 0x3
	mov ecx, 1024
	.loop1:
		mov [ebx], eax
		add	ebx, 4
		add eax, 0x1000
		loop .loop1

	;4*1024 byte page table
	xor ebx, ebx
	mov ebx, PDAddr
	mov eax, PTAddr+0x3
	mov ecx, 1024
	.loop2:
		add [ebx], eax
		add ebx, 4
		loop .loop2
	
	;save page table address
	mov eax, PDAddr
	mov cr3, eax
	
	; use 4M Page
	mov eax, cr4
	or eax, 10000b
	mov cr4, eax

	; enable paging
	mov eax, cr0
	or eax, 0x80000000
	mov cr0, eax
	; print at 4th line
	mov edi, (80*3+0)*2
	mov esi, enablePageStr
	call printByGS
	ret

[section .data]
enablePMStr: dw "Success enable Protected mode",0
enablePageStr: dw "Success enable Paging",0
memCheckError: dw "Detect memory error happend",0
