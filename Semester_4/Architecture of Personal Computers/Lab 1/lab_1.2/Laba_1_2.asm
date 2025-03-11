.model small
.stack 100h
.data

buff_1 db ?  ; buffer for writting
buff_2 db ?  ; buffer for reading

invite_msg           db "Enter a symbol:", 0dh, 0ah, '$'
received_symbol_msg  db 0dh, 0ah, "Received symbol: $"

error_write_msg  db 0dh, 0ah, "Write error!",0Dh,0Ah,'$'
error_read_msg   db 0dh, 0ah, "Read error!",0Dh,0Ah,'$'
           
.code
jmp start
;=======================================
;MACROS:
;---------------------------------------
PUSH_ALL MACRO
    push ax
    push dx
ENDM

POP_ALL MACRO
    pop dx
    pop ax
ENDM

PUTS_STRING MACRO str
    PUSH_ALL
    mov dx, offset str
    mov ah, 09h
    int 21h
    POP_ALL
ENDM

PUTCHAR MACRO symbol
    PUSH_ALL
    mov ah, 02h
    mov dl, symbol
    int 21h
    POP_ALL
ENDM

GETCHAR MACRO symbol
    PUSH_ALL
    mov ah, 01h
    int 21h
    mov symbol, al
    POP_ALL
ENDM   

;---------------------------------------
; Functions for ports
;=======================================
INIT_COM_PORT proc  ;set options
   PUSH_ALL   
   xor ax,ax            ; ah = 0 - function of opening port
   mov al, 10000010b    ; "111" - 9600 speed,
                        ; "00" - NoParitet,
                        ; "0" - length of stopbit = 1,
                        ; "10" - amount of bits in symbol = 7
   mov dx, 0            ; n-1, where n - port number
   int 14h    
   mov dx, 1
   int 14h
   POP_ALL
endm

;---------------------------------------
; Write/read information
;=======================================
WRITE_TO_COM1 PROC		
   mov al,buff_1	    ; Initialize symbol
   mov ah,01h	       	; ah = 1 - function of writing symbol to the port
   mov dx,0				; Intialize port name(number = 1)
   int 14h
   test ah, 00001110b   ; check on errors
   jnz ERROR_write
   ret 
ENDP

READ_FROM_COM2 proc
   PUSH_ALL
   mov ah,02h			; ah = 2 - function of reading symbol from the port
   mov dx,1			    ; Initialize port name(number = 2)
   int 14h
   test ah, 00001110b   ; check on errors					
   mov buff_2, al       ; al - symbol was read
   POP_ALL
   ret
endp                       

ERROR_write proc					
   PUTS_STRING error_read_msg
   call EXIT
   ret 
endp

ERROR_read proc
   PUTS_STRING error_read_msg
   call EXIT
   ret 
endp

;=======================================
EXIT proc
    mov ax,4C00h			
    int 21h
    ret
endp

;---------------------------------------
; MAIN FUNCTION
;=======================================
start:
   mov ax, @data
   mov ds, ax
   
   PUTS_STRING invite_msg
   GETCHAR buff_1
   
   call INIT_COM_PORT     
   call WRITE_TO_COM1
   call READ_FROM_COM2
   
   PUTS_STRING received_symbol_msg 
   PUTCHAR buff_2             
   call EXIT
end start    