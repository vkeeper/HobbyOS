org 0x7C00

main:
;    call clearScreen
;    mov si, initSegStr
;    call showStr
    ;mov ax, 0x0003
    ;int 10h
    call initSeg
    call loadDisk
    mov si, loadDiskOver
    call printStr
    call newLine
	jmp 0x900:0

showStr:
    mov ax, 0xB000
    mov es, ax

    mov ax, 0x8000
    mov bp ,ax 
    loopShow:
        xor ax, ax
        mov ax, [si]
        xor ax, 0
        jz end 
        inc si

        mov [es:bp],ax
        inc bp

        mov ax, 0x002a
        mov [es:bp], ax
        inc bp

        jmp loopShow


clearScreen:
    mov al, 0x0
    mov ah, 0x06
    mov cx, 0
    mov dx, 0x2580
    int 0x10
    ret

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
	xor ax, ax
	mov ax, 0x900
	mov es, ax
	xor bx, bx
	; ah=02H(function code) al= sectors to read count
	mov ax, 0x0201
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
    mov bx, 0x0F
    mov ah, 0xE
    int 0x10
    jmp printStr

end:
    ret

initSegStr: dw "Begin to init segment address",0
loadDiskStr: dw "Begin to load kernel from disk",0
loadDiskOver: dw "load kernel from disk success",0
errorMsg: dw "load disk error!",0
newLineStr: db 0xD, 0xA

times 510-($-$$) db 0
dw 0xaa55
