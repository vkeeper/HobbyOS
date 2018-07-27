org 0x7C00

main:
    call initSeg
    call loadDisk
	jmp 0x9000

; init segment address
initSeg:
    mov si,initSegStr
    call printStr
    call newLine

    xor ax, ax
    mov cx, ax
    mov dx, ax
    mov ss, ax
    ret

loadDisk:
    mov si, loadDiskStr
    call printStr
    call newLine
	xor bx, bx
	xor ax, ax
	mov ax, 0x900
	mov es, ax
	mov bx, 0
	; ah=02H(function code) al= sectors to read count
	mov ax, 0x0201
	; ch=cylinder cl=sector
	mov cx, 0x0002
	; dh=head dl=drive
	mov dx, 0
	int 0x13
    ret

newLine:
    mov si, newLineStr
    call printStr
    ret

; param: si = string
printStr:
    mov al, [si]
    xor al, 0
    jz end
    inc si
    mov bx, 0x0F
    mov ah, 0xE
    int 0x10
    jmp printStr

end:
    ret

initSegStr: dw "Begin to init segment address",0
loadDiskStr: dw "Begin to load kernel from disk",0
newLineStr: db 0xD, 0xA

times 510-($-$$) db 0
dw 0xaa55
