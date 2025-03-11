org 100h

.data

sort_name_msg   db ">> Sort from Lowest to Highest <<",10,13,"$"
enter_msg       db "Enter a numbers from 0 to 9 without space:",10,13,"$"
before_sort_msg db 10,13,"Array before sorting: $"
after_sort_msg  db 10,13,"Array after sorting:  $"

size equ 20                             ;the capacity of the array (can be changed) 
array db size dup(0)
                                               
.code                                                          
jmp start

;=======================================
;MACROS:
;---------------------------------------
PRINT_STRING MACRO str
    pusha
    mov dx, offset str
    mov ah, 09h
    int 21h
    popa
ENDM

;=======================================
;PROCEDURES
;---------------------------------------
SORT PROC
    mov cx,size                         ;cx = size
    dec cx                              ;cx = size - 1
    next_scan:                             
        mov bx,cx                       ;bx = cx.
        mov si,0                        ;si is index number
        
        next_comp:
            mov al,array[si]            ;AL = array[si].
            mov dl,array[si+1]          ;DL = array[si+1]
            cmp al,dl                   ;AL ? DL
            jc no_swap                  ;if  (AL < DL) => no_swap
                                        
                                        ;else (AL > DL):
            mov array[si],dl            ;array[si] = DL
            mov array[si+1],al          ;array[si+1] = AL
    
        no_swap:
            inc si                      ;++si
            dec bx                      ;--bx
            jnz next_comp               ;if (bx != 0) go to next_comp, else go to next_scan
    loop next_scan                      ;while(--cx)
    ret
ENDP

ARRAY_INPUT PROC
    mov cx,size
    mov bx,offset array 
    mov ah,1           
    input:
        int 21h                      
        mov [bx],al                     ;*(array+bx) = AL
        inc bx                          ;++bx
        loop input                      ;while(--cx)
    ret 
ENDP

PRINT_ARRAY PROC
    pusha
    mov cx,size                         
    mov bx,offset array                 
    print:
        mov ah,2
        mov dl,[bx]
        int 21h
        inc bx
        loop print
    popa
    ret   
ENDP

EXIT PROC
    mov ax,4c00h			
    int 21h
    ret
ENDP

;=======================================
;MAIN
;---------------------------------------
start:
    PRINT_STRING sort_name_msg
    PRINT_STRING enter_msg                                                                                                              
    call ARRAY_INPUT
    
    PRINT_STRING before_sort_msg
    call PRINT_ARRAY
    
    call SORT

    PRINT_STRING after_sort_msg
    call PRINT_ARRAY
    
    call EXIT