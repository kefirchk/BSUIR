.model tiny 
.code
org 100h

start:
    in al, 61h         ;set gate and lock at 1
    or al, 00000011b   ;write in port 61h
    out 61h, al        
    
    mov al, 10110110b  ;initialization word
    out 43h, al        ;write in port 43h 
    
;;;first friquenci    
    mov al, 11100011b  ;write lower byte of frequency divider
    out 42h, al        ;set lower byte
    mov al, 00001011b  ;write higher byte of frequency divider
    out 42h, al        ;set higher byte     
    
    mov ah, 86h        ;bios function(wait)
    mov dx, 3500h      ;write in dx lower two bytes of number 800ms
    mov cx, 0ch        ;write in cx higer two bytes
    int 15h            ;start waiting 
         
;;;second friquenci   
    mov al, 11100011b  
    out 42h, al        
    mov al, 00001011b  
    out 42h, al             
    
    mov ah, 86h        
    mov dx, 1A80h      
    mov cx, 06h        
    int 15h             
    
;;;third friquenci
    mov al, 11101000b  
    out 42h, al        
    mov al, 00001111b  
    out 42h, al             
    
    mov ah, 86h        
    mov dx, 1A80h      
    mov cx, 06h        
    int 15h                 

;;;fourth friquenci
    mov al, 11000111b  
    out 42h, al        
    mov al, 00010111b  
    out 42h, al             
    
    mov ah, 86h        
    mov dx, 1A80h      
    mov cx, 06h        
    int 15h                 
                                       
;;;fifth friquenci    
    mov al, 11000111b  
    out 42h, al        
    mov al, 00010111b  
    out 42h, al             
    
    mov ah, 86h        
    mov dx, 1A80h      
    mov cx, 06h        
    int 15h               

;;;sixth friquenci    
    mov al, 11100011b  
    out 42h, al        
    mov al, 00001011b  
    out 42h, al             
    
    mov ah, 86h        
    mov dx, 1A80h      
    mov cx, 06h        
    int 15h              
    
;;;seventh friquenci    
    mov al, 11100011b  
    out 42h, al        
    mov al, 00001011b  
    out 42h, al             
    
    mov ah, 86h        
    mov dx, 1A80h      
    mov cx, 06h        
    int 15h             
    
;;;eigth friquenci
    mov al, 11101000b  
    out 42h, al        
    mov al, 00001111b  
    out 42h, al            
    
    mov ah, 86h        
    mov dx, 1A80h      
    mov cx, 06h        
    int 15h           

;;;ninth friquenci   
    mov al, 11000111b  
    out 42h, al        
    mov al, 00010111b  
    out 42h, al            
    
    mov ah, 86h        
    mov dx, 1A80h      
    mov cx, 06h        
    int 15h       
                                         
    in al, 61h          ;set gate and lock at 0
    and al, 11111100b   ;write in port 61h
    out 61h, al   

;output first channel    
mov ah, 09h 
mov dx, offset first
int 21h  

mov al, 11000010b       ;controll word for get registr of 0 channel
out 43h, al
in al, 40h
call output_bytes

mov ah, 09h             ;friquenci devider
mov dx, offset ce
int 21h  

mov al, 00000000b       ;set controll word to get ce
out 43h, al             ;send controll word
in al, 40h              ;get higher byte
mov di, offset buf+2    ;get string with hex code of divider
call byte_to_hex_str    
in al, 40h
mov di, offset buf 
call byte_to_hex_str  

mov ah, 09h
mov dx, offset buf
int 21h
mov ah, 09h
mov dx, offset next
int 21h

  
;output second channel
mov ah, 09h 
mov dx, offset second
int 21h  

mov al, 11000100b
out 43h, al
in al, 41h
call output_bytes  

mov ah, 09h             ;friquenci devider
mov dx, offset ce
int 21h  

mov al, 01000000b       ;set controll word to get ce
out 43h, al             ;send controll word
in al, 41h              ;get higher byte
mov di, offset buf+2    ;get string with hex code of divider
call byte_to_hex_str    
in al, 41h
mov di, offset buf 
call byte_to_hex_str  

mov ah, 09h
mov dx, offset buf
int 21h
mov ah, 09h
mov dx, offset next
int 21h

;output third channel
mov ah, 09h 
mov dx, offset third
int 21h  

mov al, 11001000b
out 43h, al
in al, 40h
call output_bytes  

mov ah, 09h             ;friquenci devider
mov dx, offset ce
int 21h  

mov al, 10000000b       ;set controll word to get ce
out 43h, al             ;send controll word
in al, 42h              ;get higher byte
mov di, offset buf+2    ;get string with hex code of divider
call byte_to_hex_str    
in al, 42h
mov di, offset buf 
call byte_to_hex_str  

mov ah, 09h
mov dx, offset buf
int 21h
mov ah, 09h
mov dx, offset next
int 21h

      
    mov ax,4C00h   ;retutn to operation system		
    int 21h   
    
output_bytes proc  
      mov cx, 08
  loop1:
      rol al, 1
      jc write1
      push ax
      mov ah, 06h
      mov dl, 30h
      int 21h
      jmp finish
  write1:
      push ax       
      mov ah, 06h
      mov dl, 31h
      int 21h
  finish:
      pop ax
loop loop1
    ;mov ah, 09h
    ;mov dx, offset next
    ;int 21h
    ret
    output_bytes endp

byte_to_hex_str proc
    push ax
    mov ah,al               ;?????????? ???????? AL ? AH
    shr al,4                ;????????? ??????? ???????
    call to_hex_digit       ;?????????????? ? ????????????????? ?????
    mov [di],al             ;?????????? ??????? ? ??????
    inc di                  ;????????? DI
    mov al,ah               ;?????????????? AL
    and al,0Fh              ;????????? ??????? ???????
    call to_hex_digit       ;?????????????? ? ????????????????? ?????
    mov [di],al             ;?????????? ??????? ? ??????
    inc di                  ;????????? DI
    pop ax
    ret
    byte_to_hex_str endp

to_hex_digit proc
    add al,'0'              ;?????????? ?????? '0' (??? 0x30)
    cmp al,'9'              ;????????? ? ???????? '9' (??? 0x39)
    jle thd_end             ;???? ?????????? '0'-'9', ?? ?????
    add al,7                ;?????????? ??? 7 ??? ???????? 'A'-'F'
thd_end:
    ret
    to_hex_digit endp
    

ret  
 
first db "0_channel:", 20h, "$"  
second db "1_channel:", 20h, "$"  
third db "2_channel:", 20h, "$"
ce db 20h, 20h, "ce:", 20h, "$"
next db 0dh, 0ah, "$"
buf db 4 dup(?), "$"
 
end start  
    


      
 