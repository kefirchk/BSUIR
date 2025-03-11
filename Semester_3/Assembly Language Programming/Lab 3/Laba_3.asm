;.model small
;.stack 100h
;;========================================
;.data
;msg1 db "Enter elements of the array:", 10, 13, '$'
;msg2 db 0dh, 0ah, "Result(after sorting): $"
;msg3 db 0dh, 0ah, "Error! Try again", 10, 13, '$'
;msg4 db 0dh, 0ah, "Median of elements: $"
;;----------------------------------------
;array db 10 dup('$')
;size EQU 10
;;========================================
;.code
;main proc
;;========================================
;;MACROS
;;----------------------------------------    
;puts macro str
;mov ah, 09h
;lea dx, str 
;int 21h
;endm
;
;putchar macro symbol
;push ax
;mov ah, 02h
;mov dl, symbol
;int 21h
;pop ax
;endm
;
;;========================================
;;INITIALIZATION
;;----------------------------------------
;mov ax, @data
;mov ds, ax
;    
;;========================================
;;INPUT OF THE ELEMENTS
;;----------------------------------------
;puts msg1
;mov cx, size
;xor si, si
;;----------------------------------------
;INPUT:
;mov ah, 08h
;int 21h
;cmp al, 20h  ;code of space key
;je SPACE
;
;cmp al, '0'  ;numbers checking 
;jb ERROR
;cmp al, '9'
;ja ERROR
;;----------------------------------------                          
;;output of symbol:
;mov array[2+si], al
;inc si 
;putchar al
;loop INPUT
;;========================================
;;SORTING OF THE ARRAY
;;----------------------------------------
;call SORT 
;;========================================
;;OUTPUT OF THE SORTED ARRAY
;;---------------------------------------- 
;puts msg2
;xor si, si
;mov cx, size
;
;ARRAY_OUTPUT:
;putchar array[2+si]
;putchar 20h
;inc si
;loop ARRAY_OUTPUT
;;========================================
;;MEDIANA BE LIKE:
;;----------------------------------------
;puts msg4
;xor ax, ax
;mov al, size
;mov bl, 2
;div bl
;xor ah, ah
;mov si, ax
;putchar array[2+si]
;;======================================== 
;call EXIT
;endp main
;
;;========================================
;;==========My functions==================
;;========================================      
;SPACE: 
;putchar 20h       ;put the space key
;jmp INPUT         
;
;ERROR:
;puts msg3
;jmp INPUT          
;
;EXIT:
;mov ah, 4ch
;int 21h
;ret
;
;;========================================
;;SORT OF NUMBERS FUNCTION
;;----------------------------------------
;SORT:
;mov cx, size     
;xor si, si              ;i = 0
;   L1:                  ;for(i = 0; ...)
;   mov al, array[2+si]
;   mov bx, cx
;   push cx
;   push si
;   mov cx, bx
;   mov di, si           ;j = i                   
;      L2:               ;for(j = i; ...)
;      mov ah, array[2+di]
;      cmp ah, al
;      jl SWAP
;      jmp CONTINUE
;         SWAP:                            
;         xchg ah, al             
;         mov array[2+si], al     
;         mov array[2+di], ah     
;         ends SWAP
;
;      CONTINUE:
;      inc di            ;j++
;      loop L2
;   pop si
;   pop cx
;   inc si               ;i++
;   loop L1
;ret
;;========================================     




.model small
.stack 100h
;========================================
.data
msg1 db "Enter elements of the array:", 10, 13, '$'
msg2 db 0dh, 0ah, "Result(after sorting): $"
msg3 db 0dh, 0ah, "Error! Try again", 10, 13, '$'
msg4 db 0dh, 0ah, "Median of elements: $"
;----------------------------------------
array db 10 dup('$')
size EQU 10
;========================================
.code
main proc
;========================================
;MACROS
;----------------------------------------    
puts macro str
mov ah, 09h
lea dx, str 
int 21h
endm

putchar macro symbol
push ax
mov ah, 02h
mov dl, symbol
int 21h
pop ax
endm

;========================================
;INITIALIZATION
;----------------------------------------
mov ax, @data
mov ds, ax
    
;========================================
;INPUT OF THE ELEMENTS
;----------------------------------------
puts msg1
mov cx, size
xor si, si
;----------------------------------------
INPUT:
mov ah, 08h
int 21h
cmp al, 20h  ;code of space key
je SPACE

cmp al, '0'  ;numbers checking 
jb ERROR
cmp al, '9'
ja ERROR
;----------------------------------------                          
;output of symbol:
mov array[2+si], al
inc si 
putchar al
loop INPUT
;========================================
;SORTING OF THE ARRAY
;----------------------------------------
call SORT 
;========================================
;OUTPUT OF THE SORTED ARRAY
;---------------------------------------- 
puts msg2
xor si, si
mov cx, size

ARRAY_OUTPUT:
putchar array[2+si]
putchar 20h
inc si
loop ARRAY_OUTPUT
;========================================
;MEDIANA BE LIKE:
;----------------------------------------
puts msg4
xor ax, ax
mov al, size
mov bl, 2
div bl
cmp ah, 0
je TWO_NUMBERS
jne ONE_NUMBER

TWO_NUMBERS:
xor ah, ah
mov si, ax
mov di, ax
dec di

xor ax, ax
mov al, array[2+si]
sub al, 48
add al, array[2+di]
sub al, 48
div bl

push ax
mov al, ah
mov bl, 10
mul bl
mov bl, 2
div bl
mov bh, al 
pop ax 
mov ah, bh

add al, 48
add ah, 48
putchar al
putchar 2eh 
mov bh, ah
putchar bh
call EXIT
ends TWO_NUMBERS

ONE_NUMBER:
xor ah, ah
mov si, ax
putchar array[2+si]
call EXIT
ends ONE_NUMBER


;======================================== 
;call EXIT
endp main

;========================================
;==========My functions==================
;========================================      
SPACE: 
putchar 20h       ;put the space key
jmp INPUT         

ERROR:
puts msg3
jmp INPUT          

EXIT:
mov ah, 4ch
int 21h
ret

;========================================
;SORT OF NUMBERS FUNCTION
;----------------------------------------
SORT:
mov cx, size     
xor si, si              ;i = 0
   L1:                  ;for(i = 0; ...)
   mov al, array[2+si]
   mov bx, cx
   push cx
   push si
   mov cx, bx
   mov di, si           ;j = i                   
      L2:               ;for(j = i; ...)
      mov ah, array[2+di]
      cmp ah, al
      jl SWAP
      jmp CONTINUE
         SWAP:                            
         xchg ah, al             
         mov array[2+si], al     
         mov array[2+di], ah     
         ends SWAP

      CONTINUE:
      inc di            ;j++
      loop L2
   pop si
   pop cx
   inc si               ;i++
   loop L1
ret
;========================================