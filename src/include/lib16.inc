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
