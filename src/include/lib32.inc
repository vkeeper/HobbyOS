printByGS:
    xor eax, eax 
    mov ah, 0x0F
    ;mov edi, (80*2+0)*2

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
