org 0x7C00

main:
    call clearScreen
    call initSeg
    call probeMemory
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
loadDisk:
	xor ax, ax
	mov ax, 0x900
	mov es, ax
	xor bx, bx
	; ah=02H(function code) al= sectors to read count
	mov ax, 0x021F
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
    hlt
    jmp $

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

;--------------------------------------------------------
; Detect Mem Address
;--------------------------------------------------------
MemTableAddr    equ     0x50
ARDSNum         equ     0x0
ARDSAddrOffset  equ     ARDSNum + 0x4

errorMsg: dw "load disk error!",0

times 510-($-$$) db 0
dw 0xaa55
