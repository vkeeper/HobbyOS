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
