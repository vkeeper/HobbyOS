org 0x9000

%include "pm.inc"

;TODO enable interrupt vector

;TODO enable second-level page memory management


SegmentNone:	Descriptor	0,		0,				0
SegmentData:	Descriptor	0,		0xFFFFFFFF,		SDA_FLAT_DATA
SegmentCode:	Descriptor	0,		0xFFFFFFFF,		SDA_FLAT_CODE

GdtPtr:
	GdtPointer	SegmentNone+0x20000, $-SegmentNone

main:
	call enableA20
	call enablePM
	call initReg

	mov esi, enablePMStr
	call printStr
	jmp $

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
	or eax, 1
	mov cr0, eax
	ret

initReg:
	mov ax, SDA_FLAT_DATA 
	mov gs, ax
	mov ds, ax
	mov es, ax
	mov ss, ax
	ret

printStr:
	push ebp
	mov ebp,0xB8000 
	mov ah, 0xF
	.loop:
		mov al, [esi]
		inc esi
		or esi, 0
		jz end
		cmp al, 10
		je .10
		mov [ebp], ax
		inc ebp
		inc ebp
		jmp .loop

	.10:
		add ebp, 160
		jmp .loop

	ret

end:
	jmp $

enablePMStr dw "Success into Protected mode", 0xA,0
