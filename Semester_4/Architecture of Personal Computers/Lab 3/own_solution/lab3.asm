;LABA 3. FULL EDITION. 
;VARIANT 11(1). "Fur elise" - Ludwig van Beethoven
;@AUTHOR - Klimovich Alexei, 150501

.model small
.stack 100h
.data

;divOfFreq = CR = 1193183/frequancy
frequancy    dw 659, 622, 659, 622, 659, 493, 622, 523, 440
divOfFreq    dw 712h,77Eh,712h,77Eh,712h,974h,77Eh,8E9h,0A97h   
div_factor   dw ?
value_of_ce  db ?
amountOfFreq equ 9 
symbol       db ?
counter      db 9
\n           db 0dh, 0ah, '$'

;MENU:
invite_msg  db "CHOOSE AN OPTION:", 0dh, 0ah, '$'
option_1    db "1. Listen to music.", 0dh, 0ah, '$'
option_2    db "2. Read state word and print on the screen in binary form.", 0dh, 0ah, '$'
option_3    db "3. Calculate division coefficient.", 0dh, 0ah,'$'
option_4    db "4. Calculate CE and print it in hex form", 0ah, 0dh, '$'
option_5    db "5. Exit.", 0dh, 0ah, '$'

;INFORMATION STRINGS:
chanal_0     db "40h - $"
chanal_1     db "41h - $"
chanal_2     db "42h - $"
music_mode   db ' ',0Eh,' ',0Eh,' ',0Eh,'$' 
error_msg    db "ERROR!", 0dh, 0ah, '$'
continue_msg db 0ah, 0dh, "Press any key to continue...", 0ah, 0dh, '$'
           
.code
;=======================================
;MACROS:
;---------------------------------------
PUSH_ALL MACRO
    push ax
    push bx
    push dx
    push cx
ENDM

POP_ALL MACRO
    pop cx
    pop dx
    pop bx
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
    mov ah, 08h       ;;or you can use 01h too
    int 21h
    mov symbol, al
    POP_ALL
ENDM

SET_FREQUENCY MACRO indexOfNota
    push ax                     
    mov al, BYTE ptr divOfFreq[indexOfNota]
    out 42h, al
    mov al, BYTE ptr divOfFreq[indexOfNota+1]
    out 42h, al 
    pop ax
ENDM

GET_DIV_FACTOR MACRO freq
    PUSH_ALL
    mov ax, 04DFh   ;;1234DF = 1193183 Gz
    mov dx, 0123h
    mov bx, freq
    div bx
    mov div_factor, ax 
    POP_ALL 
ENDM 

;---------------------------------------
;FUNCTIONS:                              
;=======================================
PRINT_DIV_FACTOR PROC
    PUSH_ALL 
    mov ax, div_factor  ;our number
    mov bx,16   ;base of counting system
    xor cx,cx   ;amount of digits in hex-number
        L1:  
            xor dx,dx
            div bx      ;div number on 16
            push dx     ;save ostatok in stack
            inc cx      ;increment amoount of digits
            test ax,ax  ;does stay zero after division? 
            jnz L1      ;if not, then continue
        L2:  
            pop ax      ;take digit from stack
            cmp al, 9   ;if digit > 9 (without sign)
            ja isLetter
            jmp isDigit
            isLetter:
                add al, 55  ;to letter
                jmp print_digit
            isDigit: 
                add al,'0'  ;transfer digit to ASCII symbol
            print_digit:
            PUTCHAR al      ;print digit
            loop L2         ;all digits    
    POP_ALL
    ret
ENDP

;=======================================
PRINT_REGISTER_CE PROC
    PUSH_ALL 
    xor ax, ax
    mov al,value_of_ce ;our number
    mov bx,16   ;base of counting system
    mov cx, 2   ;digits number is 2
        LoopCE_1:  
            xor dx,dx
            div bx      ;div number on 16
            push dx     ;save ostatok in stack 
            loop LoopCE_1
        mov cx, 2
    jmp L2 
    ret
ENDP

;=======================================
PRINT_BINARY_NUMBER PROC
    PUSH_ALL 
    mov ax, bx  ;our number
    mov bx,2    ;base of counting system
    xor cx,cx   ;amount of digits in hex-number
    mov cx, 8
        Loop1:  
            xor dx,dx
            div bx      ;div number on 2
            push dx     ;save ostatok in stack 
            loop Loop1
        mov cx, 8
        Loop2:  
            pop ax      ;take digit from stack
            add al,'0'  ;transfer digit to ASCII symbol
            PUTCHAR al  ;print digit
            loop Loop2  ;all digits    
    POP_ALL
    ret
ENDP

;=======================================
PAUSE PROC
    PUSH_ALL       ;200000 mks = 30D40 mks
    mov dx, 0D40h     
    mov cx, 3h        
    mov ah, 86h
    int 15h
    POP_ALL
    ret
ENDP

;=======================================        
CLEAR_SCREEN proc  ;This proc clears the user's screen
    PUSH_ALL
    mov ax, 0600h
    mov bh, 07h
    xor cx, cx
    mov dx, 184Fh
    int 10h 
    
    ;set cursor at (0;0)
    xor dx, dx
    xor bx, bx 
    xor ax, ax
    mov ah, 2  ;Interrupt service 10h to change cursor position 
    int 10h 
    POP_ALL
    ret
endp

;=======================================
SPEAKER_ON PROC
    push ax
    in al, 61h         ;read state of port
    or al, 00000011b   ;set 1 in the first and second bits 
    out 61h, al        ;turn on system speaker
    pop ax
    ret
ENDP                                    

;=======================================
SPEAKER_OFF PROC
    push ax
    in al, 61h         ;read state of port
    and al, 11111100b  ;set 0 in the first and second bits 
    out 61h, al        ;turn off system speaker
    pop ax             
    ret                                      
ENDP 

;=======================================
PLAY_SOUND PROC
    cli                ;block interruptions
    call SPEAKER_ON
    call PAUSE
    call SPEAKER_OFF
    sti
    ret
ENDP

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
    choice_loop:
        PUTS_STRING invite_msg
        PUTS_STRING option_1    ;Listen to music
        PUTS_STRING option_2    ;Read state word and print on the screen in binary form
        PUTS_STRING option_3    ;Calculate division coefficient
        PUTS_STRING option_4    ;Calculate CE and print it in hex form
        PUTS_STRING option_5    ;Exit.
      GETCHAR symbol
      mov al, symbol
        cmp al, '1'
        je music_option
        cmp al, '2'
        je stateWord_option
        cmp al, '3'
        je divCoeff_option
        cmp al, '4'
        je valueOfCE_option
        cmp al, '5'
        je exit_option
      PUTS_STRING error_msg
    loopne choice_loop
    
;------------------------
    music_option:
        call CLEAR_SCREEN
        PUSH_ALL             ;initialization:
        mov al, 10110110b    ;10 - third chanel
        out 43h, al          ;11 - read/write little byte, then high byte of CR(control register?)
        xor bx, bx           ;011 - mode of generetion meadra, positive and negative output signal take part on the coordinate line 
        xor cx, cx           ;0 - data presetation format(binary or hex)       
        mov cl, amountOfFreq
        Next_nota:
            PUTS_STRING music_mode
            SET_FREQUENCY bx
            call PLAY_SOUND
            PUTS_STRING \n
            inc bx
            inc bx
        loop Next_nota    
        call PAUSE
        POP_ALL 
        call CLEAR_SCREEN
    jmp choice_loop
;------------------------    
    stateWord_option:
        call CLEAR_SCREEN
        PUSH_ALL
            
        PUTS_STRING chanal_0
        mov al, 11000010b       ;TABLE 10.5 (Nesvizhskiy V.)
        out 43h, al             ;11 -command of reading registers of the chanels
        in al, 40h              ;0 - fix value of counter
        mov bl, al              ;0 - to get state of chanel
        call PRINT_BINARY_NUMBER;001 - number of chanel (now chanel number is 0)
        PUTS_STRING \n          ;0 - not used.
     
        PUTS_STRING chanal_1
        mov al, 11000100b       ;TABLE 10.5 (Nesvizhskiy V.)
        out 43h, al             ;Analogically to the first chanel, 
        in al, 41h              ;but number of chanel is
        mov bl, al              ;010 (now chanel number is 1)
        call PRINT_BINARY_NUMBER
        PUTS_STRING \n
        
        PUTS_STRING chanal_2
        mov al, 11001000b       ;TABLE 10.5 (Nesvizhskiy V.)
        out 43h, al             ;Analogically. Number of chanel is
        in al, 42h              ;100 (now chanel number is 2)
        mov bl, al
        call PRINT_BINARY_NUMBER
        jmp end_of_operation
;------------------------    
    divCoeff_option:
        call CLEAR_SCREEN
        PUSH_ALL  
        xor bx, bx
        mov counter, 9
        mov cl, amountOfFreq 
        print_coeff:
            mov div_factor, 00000h
            GET_DIV_FACTOR frequancy[bx]    
            call PRINT_DIV_FACTOR
            PUTCHAR 20h  ;space
            inc bx
            inc bx
            dec counter
            mov al, counter
            cmp al, 0
            je end_of_operation
        jmp print_coeff
;------------------------
    valueOfCE_option:
        call CLEAR_SCREEN
        PUSH_ALL  
        xor ax, ax
        PUTS_STRING chanal_0
        mov al, 00000000b       ;TABLE 10.2-10.4 and 10.6
        out 43h, al             ;00 - chanel number (now is 0), other must be zero
        in al, 40h              ;little part of CE      
        push ax                   
        in al, 40h              ;high part of CE     
        mov value_of_ce, al
        call PRINT_REGISTER_CE
        pop ax
        mov value_of_ce, al
        call PRINT_REGISTER_CE
        PUTS_STRING \n
                    
        PUTS_STRING chanal_1
        mov al, 01000000b       ;TABLE 10.2-10.4 and 10.6
        out 43h, al             ;01 - chanel number (now is 1), other must be zero
        in al, 41h              ;little part of CE      
        push ax                   
        in al, 41h              ;high part of CE     
        mov value_of_ce, al
        call PRINT_REGISTER_CE
        pop ax
        mov value_of_ce, al
        call PRINT_REGISTER_CE
        PUTS_STRING \n        
          
        PUTS_STRING chanal_2
        mov al, 10000000b       ;TABLE 10.2-10.4 and 10.6
        out 43h, al             ;10 - chanel number (now is 2), other must be zero
        in al, 42h              ;little part of CE      
        push ax                  
        in al, 42h              ;high part of CE     
        mov value_of_ce, al
        call PRINT_REGISTER_CE
        pop ax
        mov value_of_ce, al
        call PRINT_REGISTER_CE
        
        end_of_operation:
           PUTS_STRING continue_msg
           GETCHAR symbol
           POP_ALL  
           call CLEAR_SCREEN
    jmp choice_loop  
;------------------------    
    exit_option:
    call CLEAR_SCREEN     
    call EXIT
end start 