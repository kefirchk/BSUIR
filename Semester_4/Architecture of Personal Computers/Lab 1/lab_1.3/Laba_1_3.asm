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
INIT_COM_PORT proc
    PUSH_ALL
    mov al,10000000b  		 ; '10' - length of word = 7 bits
                             ; '0'  - amount of stopbits = 1
                             ; '00' - NoParitet
                             ; '0'  - fraquency
                             ; '0'  - BREAK
                             ; '0'  - usual using(for writing)
    mov dx,3FBh
    out dx,al			     ; Set options 
	
    mov dx,3F8h 			 ; Port is used for writing
    mov al,10000000b
    out dx,al		
    			
    mov al,11000000b   		 ; Permission for interrupts for ready giving data, break 
    mov dx,3F9h
    out dx,al
    
    mov al,00000000b 
    mov dx,3FBh
    out dx,al 
    
    xor ax,ax
    mov al,11000000b 
    mov dx,2FBh
    out dx,al

    mov al,00000000b
    mov dx,2F8h 
    out dx,al

    ;access interapt by ready to get data,access interapt after giving bite
    mov al,11000000b
    mov dx,2F9h
    out dx,al

    mov al,00000000b 
    ;line control register
    mov dx,2FBh
    out dx,al 
    				 
    POP_ALL
    ret
endp

WRITE_TO_PORT proc  
    PUSH_ALL
    xor al,al
    ;mov dx,3FDh 			 ; port is ready for write
    ;in al,dx
    ;test al,00100000b 		 ; register is empty, u can write some information to it
    ;jnz ERROR_write
    
    mov dx,3F8h              ; writing
    mov al,buff_1
    out dx,al				 ; load data in COM1
    POP_ALL
    ret
endp

READ_FROM_PORT proc
    PUSH_ALL
    xor al,al                ; zero for reading
    mov dx,2FDh
    in al,dx
    test al,00001110b 		 ; check on errors
    jnz ERROR_read
    
    mov dx,2F8h              ; read
    in al,dx
    mov buff_2,al 			 ; load data from COM1
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
    mov ax,@data
    mov ds,ax
    
    PUTS_STRING invite_msg
    GETCHAR buff_1      
    
    call INIT_COM_PORT
    call WRITE_TO_PORT
    call READ_FROM_PORT
    
    PUTS_STRING received_symbol_msg 
    PUTCHAR buff_2
    call EXIT
end start 