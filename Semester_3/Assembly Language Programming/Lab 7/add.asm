cseg segment para public 'code'
overlay proc
    assume cs:cseg
    push ds
    
    add ax, cx
    jno ALLIsOK

Error:
    mov ah, 02h
    mov dl, 'E'
    int 21h
    mov ah, 02h
    mov dl, 'r'
    int 21h
    mov ah, 02h
    mov dl, 'r'
    int 21h
    mov ah, 02h
    mov dl, 'o'
    int 21h
    mov ah, 02h
    mov dl, 'r'
    int 21h
    mov ah, 02h
    mov dl, '!'
    int 21h
    
    mov ah, 4Ch
    int 21h

ALLIsOK:
    pop ds
    retf
    overlay endp
    cseg ends
end