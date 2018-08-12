org 0x7C00

main:
    call clearScreen
    call initSeg
    call loadDisk    
	jmp 0x900:0

clearScreen:
	mov ax, 0x0600
    mov cx, 0
    mov dx, 0x1950
    mov bh, 0x0F
    int 0x10

	; init cursor at top left
    mov ah, 0x02
    mov dx,0x0
    mov bh, 0x0
    int 0x10
    ret

; init segment address
initSeg:
    xor ax, ax
    mov cx, ax
    mov dx, ax
    mov ss, ax
    ret

loadDisk:
	xor ax, ax
	mov ax, 0x900
	mov es, ax
	xor bx, bx
	; ah=02H(function code) al= sectors to read count
	mov ax, 0x020F
	; ch=cylinder cl=sector
	mov cx, 0x0002
	; dh=head dl=drive
	mov dx, 0x0000
	int 0x13
    jc error
    ret

error:
    mov si, errorMsg
    call printStr
    call newLine
    hlt
    jmp $

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
    mov bx, 0x000F
    mov ah, 0xE
    int 0x10
    jmp printStr

end:
    ret

loadDiskStr: dw "Begin to load kernel from disk",0
errorMsg: dw "load disk error!",0
newLineStr: db 0xD, 0xA

times 510-($-$$) db 0
dw 0xaa55
