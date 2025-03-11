;LABA 4. 
;@AUTHOR - Klimovich Alexei, 150501
            
.model tiny
.code
org 100h
jmp start
;=======================================
;MACROS:
;---------------------------------------
PUSH_ALL MACRO
    push ax
    push bx
    push dx
    push cx
ENDM
;---------------------------------------
POP_ALL MACRO
    pop cx
    pop dx
    pop bx
    pop ax
ENDM
;---------------------------------------
PUTS_STRING MACRO str
    push ax
    push dx
    mov dx, offset str
    mov ah, 09h
    int 21h
    pop dx
    pop ax
ENDM
;---------------------------------------
GETS_STRING MACRO str
    push ax
    push dx
    mov ah, 0ah
    mov dx, offset str
    int 21h
    pop dx
    pop ax
ENDM
;---------------------------------------
PUTCHAR MACRO symbol
    push ax
    push dx
    mov ah, 02h
    mov dl, symbol
    int 21h
    pop dx
    pop ax
ENDM
;---------------------------------------
GETCHAR MACRO symbol
    push ax
    mov ah, 08h       ;;or you can use 01h too
    int 21h
    mov symbol, al
    pop ax
ENDM
;---------------------------------------  
WRITE_PORT MACRO number_of_func source 
    call CHECK_DOMAIN
    cli
    mov al, number_of_func
    out 70h, al 
    mov al, source
    jmp short $+2
    out 71h, al             ;;end stop updating 
    sti
ENDM
;---------------------------------------
READ_PORT MACRO number_of_func 
;al-result 
    call CHECK_DOMAIN
    cli
    mov al, number_of_func
    out 70h, al 
    jmp short $+2
    in al, 71h             ;;end stop updating 
    sti
ENDM
;---------------------------------------    
PRINT_DATE_OR_TIME MACRO value
    push ax
    xor ax, ax
    mov al, value
    mov number_digit, ax
    call PRINT_ZERO_IF_NEED
    call PRINT_NUMBER
    push ax
ENDM
 
;---------------------------------------
;FUNCTIONS:                              
;=======================================
CHECK_DOMAIN PROC 
    push ax
    check_time_on_domain:
        mov al, 0Ah
        out 70h, al
        jmp short $+2
        in al, 71h
        mov ah, 10000000b
        and ah, al
        cmp ah, 10000000b
    je check_time_on_domain
    pop ax
    ret
ENDP  

;=======================================
PRINT_ZERO_IF_NEED PROC
    push bx
    mov bl, 9
    cmp al, bl
    jbe zero_is_need
    jmp zero_is_not_need
       zero_is_need:
           PUTCHAR 30h  ;'0'
    zero_is_not_need:
    pop bx
    ret
ENDP

;=======================================        
CLEAR_SCREEN PROC  ;This proc clears the user's screen
    PUSH_ALL
    mov ax, 0600h
    mov bh, 07h
    xor cx, cx
    mov dx, 184Fh
    int 10h 
    xor dx, dx     ;set cursor at (0;0)
    xor bx, bx 
    xor ax, ax
    mov ah, 2  ;Interrupt service 10h to change cursor position 
    int 10h 
    POP_ALL
    ret
ENDP    

;=======================================
GET_CURRENT_DATE_AND_TIME PROC
    push ax              
    READ_PORT 32h         ;get century
    mov century_value, al
    READ_PORT 09h         ;get year
    mov year_value, al 
    READ_PORT 08h         ;get month
    mov month_value, al 
    READ_PORT 07h         ;get day
    mov day_value, al 
    READ_PORT 04h         ;get hours
    mov hours_value, al 
    READ_PORT 02h         ;get minutes
    mov minutes_value, al 
    READ_PORT 00h         ;get seconds  
    mov seconds_value, al 
    pop ax
    ret
ENDP  

;=======================================
SET_CURRENT_TIME PROC
    PUSH_ALL  
    xor cx, cx
    mov di, offset hours_value+2
    mov cl, hours_value+1
    call CONVERT_STR_TO_DECIMAL 
    mov hours_value, al
    
    xor cx, cx
    mov di, offset minutes_value+2
    mov cl, minutes_value+1
    call CONVERT_STR_TO_DECIMAL
    mov minutes_value, al
    
    xor cx, cx
    mov di, offset seconds_value+2
    mov cl, seconds_value+1
    call CONVERT_STR_TO_DECIMAL
    mov seconds_value, al
      
    READ_PORT 0Bh        ;stop updating clock
    mov ah, al           
    or ah, 10000000b
    WRITE_PORT 0Bh ah    ;end stop updating 
    WRITE_PORT 04h hours_value
    WRITE_PORT 02h minutes_value
    WRITE_PORT 00h seconds_value
    READ_PORT 0Bh        ;start clock
    mov ah, al           ;start updating clock
    and ah, 01111111b
    WRITE_PORT 0Bh ah    ;end start updating
    
    POP_ALL
    ret
ENDP 

;=======================================
SET_CURRENT_DATE PROC
    PUSH_ALL  
    xor cx, cx
    mov di, offset century_value+2
    mov cl, century_value+1
    call CONVERT_STR_TO_DECIMAL
    mov century_value, al
    
    xor cx, cx
    mov di, offset year_value+2
    mov cl, year_value+1
    call CONVERT_STR_TO_DECIMAL
    mov year_value, al
    
    xor cx, cx
    mov di, offset month_value+2
    mov cl, month_value+1
    call CONVERT_STR_TO_DECIMAL
    mov month_value, al
    
    xor cx, cx
    mov di, offset day_value+2
    mov cl, day_value+1
    call CONVERT_STR_TO_DECIMAL
    mov day_value, al
    
    READ_PORT 0Bh        ;stop updating clock
    mov ah, al           
    or ah, 10000000b
    WRITE_PORT 0Bh ah    ;end stop updating
    WRITE_PORT 32h century_value
    WRITE_PORT 09h year_value
    WRITE_PORT 08h month_value
    WRITE_PORT 07h day_value
    READ_PORT 0Bh        ;start clock
    mov ah, al           ;start updating clock
    and ah, 01111111b
    WRITE_PORT 0Bh ah    ;end start updating
    
    POP_ALL
    ret
ENDP      

;=======================================                          
SET_ALARM_TIME PROC
    PUSH_ALL     
    mov ax,2570h                 ;set interrapt vector for alarm 
    mov dx, offset ALARM_HANDLER
    int 21h 
    
    xor cx, cx
    mov di, offset hours_value+2
    mov cl, hours_value+1
    call CONVERT_STR_TO_DECIMAL 
    mov hours_value, al
    
    xor cx, cx
    mov di, offset minutes_value+2
    mov cl, minutes_value+1
    call CONVERT_STR_TO_DECIMAL
    mov minutes_value, al
    
    xor cx, cx
    mov di, offset seconds_value+2
    mov cl, seconds_value+1
    call CONVERT_STR_TO_DECIMAL
    mov seconds_value, al
        
    READ_PORT 0Bh        ;stop updating clock
    mov ah, al           
    or ah, 10000000b
    WRITE_PORT 0Bh ah    ;end of stop update
    
    WRITE_PORT 05h hours_value
    WRITE_PORT 03h minutes_value
    WRITE_PORT 01h seconds_value
    
    READ_PORT 0Bh        ;start updating clock
    mov ah, al           
    and ah, 01111111b
    WRITE_PORT 0Bh ah    ;end start updating
       
    READ_PORT 0Bh        ;enable interrupt of alarm
    mov ah, al
    or ah, 00100000b
    and ah, 10101111b
    WRITE_PORT 0Bh ah
    
    POP_ALL
    ret
ENDP  

;=======================================
ALARM_HANDLER PROC FAR    ;IRQ8 - interrupt for alarm                
    mov ax,0B88Ch         ;adress of video memory, 14x160, where 14 is line
    mov es,ax             
    mov cx,20
    xor di,di                  
    output:
    mov al, 0Eh           ;music symbol 
    mov es:[di],al
    inc di
    mov al,11001001b      ;7 - miganie, 6-4 - background color, 3 - miganie, 0-2 - symbol color  
    mov es:[di],al
    inc di                            
    loop output 
  
    READ_PORT 0Ch        ;end start updating  
   
    mov al, 20h          ;clear interrupt conroller ISR(master)
    out 0a0h, al
    mov al, 20h          ;clear interrupt conroller ISR(slave)
    out 20h, al
    iret 
ENDP
                             
;=======================================
GET_ALARM_TIME PROC
    push ax               
    READ_PORT 05h         ;get hours
    mov hours_value, al 
    READ_PORT 03h         ;get minutes
    mov minutes_value, al 
    READ_PORT 01h         ;get seconds  
    mov seconds_value, al
    pop ax
    ret
ENDP 
 
;=======================================
SET_DELAY PROC
    PUSH_ALL
    mov ax, 2570h                 ;set interrupt vector for delay 
    mov dx, offset DELAY_HANDLER
    int 21h
    
    xor cx, cx
    mov di, offset delay_value+2
    mov cl, delay_value+1
    call CONVERT_STR_TO_DECIMAL 
    mov bx, ax
    
    READ_PORT 0Bh
    mov ah, al
    or ah, 01000000b    ;enable to period interruptions
    and ah, 11001111b   ;stop clock, enable to period interruptions, unenable alarm, unenable interrupt about change of time
    WRITE_PORT 0Bh ah
    
    delay_loop:
        cmp bx, 0
        jbe stop_delay
    jmp delay_loop
    
    stop_delay:
        READ_PORT 0Bh      ;enable interrupt
        mov ah, al
        and ah, 10111111b
        WRITE_PORT 0Bh, ah
     
    POP_ALL
    ret
ENDP  

;=======================================
DELAY_HANDLER proc       ;IRQ8 - handler for delay
    dec bx 
    READ_PORT 0Ch           
    mov al, 20h          ;clear interrapt conroller ISR(master)
    out 0a0h, al
    mov al, 20h          ;clear interrapt conroller ISR(slave)
    out 20h, al 
    iret
ENDP	
 
;=======================================
CONVERT_STR_TO_DECIMAL PROC
;di-string offset
;ax-result number
;cx-len of string
    push bx
    push dx
    xor ax,ax
    xor bx,bx                                                  
    mov si,10                                                  
m1:
    mul si                      
    mov bl,[di]                 
    sub bl,30h                  
    add ax,bx               
    inc di                 
loop m1                      
    pop dx
    pop bx    
    ret 
ENDP

;=======================================
PRINT_NUMBER PROC
    PUSH_ALL 
    mov ax,number_digit  ;our number
    mov bx,10   ;base of counting system
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

print_error:
    POP_ALL
    PUTS_STRING error_msg
    jmp choice_loop 
 
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
    mov al, 00000000b    ;set mask for first conroller of int(permit all interrapts) 
    out 21h, al 
    mov al, 00000000b    ;set mask for second conroller of int (permit all interrapts) 
    out 0a1h, al   
    WRITE_PORT 0Bh al    ;set binary instead of bsd-code                         
    mov ah, al
    or ah, 00000100b
    WRITE_PORT 0Bh ah 
   
    choice_loop: 
        PUTS_STRING invite_msg
        PUTS_STRING options
      GETCHAR bl
        cmp bl, '1'
        je get_date_and_time_option
        cmp bl, '2'
        je set_time_option
        cmp bl, '3'
        je set_date_option
        cmp bl, '4'
        je set_alarm_option
        cmp bl, '5'
        je get_alarm_option
        cmp bl, '6'
        je set_delay_option
        cmp bl, '7'
        je get_delay_option
        cmp bl, '8'
        je set_frequancy_option
        cmp bl, '9'
        je get_frequancy_option
        cmp bl, '0'
        je exit_option
      PUTS_STRING error_msg
    loopne choice_loop
 
 ;options:   
;=======================================
    get_date_and_time_option:
        call CLEAR_SCREEN
        PUSH_ALL
        call GET_CURRENT_DATE_AND_TIME      
        PUTS_STRING date_msg
            PRINT_DATE_OR_TIME day_value     ;day
        PUTCHAR 2Eh        ; '.'
            PRINT_DATE_OR_TIME month_value   ;month
        PUTCHAR 2Eh        ; '.'
            PRINT_DATE_OR_TIME century_value ;century
            PRINT_DATE_OR_TIME year_value    ;year
        PUTS_STRING \n
        PUTS_STRING time_msg
            PRINT_DATE_OR_TIME hours_value   ;hours
        PUTCHAR 3Ah        ; ':'
            PRINT_DATE_OR_TIME minutes_value ;minutes
        PUTCHAR 3Ah        ; ':'
            PRINT_DATE_OR_TIME seconds_value ;seconds
        PUTS_STRING \n
        PUTS_STRING \n       
        POP_ALL
    jmp choice_loop
     
;---------------------------------------
    set_time_option:
        call CLEAR_SCREEN      
        PUTS_STRING hours_msg         ;hours
            GETS_STRING hours_value
        PUTS_STRING minutes_msg       ;minutes
            GETS_STRING minutes_value
        PUTS_STRING seconds_msg       ;seconds
            GETS_STRING seconds_value
        call SET_CURRENT_TIME       
        call CLEAR_SCREEN
    jmp choice_loop
    
;---------------------------------------
    set_date_option:
        call CLEAR_SCREEN
        PUTS_STRING century_msg       ;century
            GETS_STRING century_value
        PUTS_STRING \n 
        PUTS_STRING year_msg          ;year
            GETS_STRING year_value  
        PUTS_STRING month_msg         ;month
            GETS_STRING month_value     
        PUTS_STRING day_msg           ;day
            GETS_STRING day_value
        call SET_CURRENT_DATE            
        call CLEAR_SCREEN
    jmp choice_loop    
    
;---------------------------------------
    set_alarm_option:
        call CLEAR_SCREEN
        PUTS_STRING hours_msg
            GETS_STRING hours_value
        PUTS_STRING minutes_msg
            GETS_STRING minutes_value
        PUTS_STRING seconds_msg
            GETS_STRING seconds_value
        call SET_ALARM_TIME 
        call CLEAR_SCREEN
    jmp choice_loop
    
;---------------------------------------
    get_alarm_option:
        call CLEAR_SCREEN
        call GET_ALARM_TIME
        PUTS_STRING time_msg
            PRINT_DATE_OR_TIME hours_value   ;hours
        PUTCHAR 3Ah        ; ':'
            PRINT_DATE_OR_TIME minutes_value ;minutes
        PUTCHAR 3Ah        ; ':'
            PRINT_DATE_OR_TIME seconds_value ;seconds
        PUTS_STRING \n
        PUTS_STRING \n
    jmp choice_loop    
   
;---------------------------------------
    set_delay_option:
        call CLEAR_SCREEN
        PUSH_ALL
        PUTS_STRING delay_msg
        GETS_STRING delay_value
        call SET_DELAY
        POP_ALL
        call CLEAR_SCREEN
    jmp choice_loop  
    
;---------------------------------------
    get_delay_option:
        call CLEAR_SCREEN
        PUSH_ALL
        READ_PORT 0Bh
        mov ah, 10000000b
        mov cx, 8
    jmp output_register_bits
     
;---------------------------------------
    set_frequancy_option:
        call CLEAR_SCREEN
        PUSH_ALL
        PUTS_STRING frequancy_menu
        GETS_STRING choosing_freq
        
        xor cx, cx
        xor ax, ax
        mov di, offset choosing_freq+2
        mov cl, choosing_freq+1
        call CONVERT_STR_TO_DECIMAL
        mov di, offset possible_freq
        dec ax
        add di, ax 
        mov bl, [di]
        
        READ_PORT 0Ah
        mov ah, al
        and ah, 11110000b ;last 4 bits - our setting frequancy
        or ah, bl
        WRITE_PORT 0Ah ah
        READ_PORT 0Ah
        
        POP_ALL
        call CLEAR_SCREEN
    jmp choice_loop
    
;---------------------------------------
    get_frequancy_option:
        call CLEAR_SCREEN
        PUSH_ALL
        READ_PORT 0Ah
        mov ah, 10000000b
        mov cx, 8
        output_register_bits:
            mov bl, al
            and bl, ah
            cmp bl, 0
            jne print_one_bit
            je print_zero_bit
            print_one_bit:
                PUTCHAR 31h
                jmp continue_output_register_bits    
            print_zero_bit:
                PUTCHAR 30h
            continue_output_register_bits:
            shr ah, 1
        loop output_register_bits
    jmp end_of_operation

;---------------------------------------
    exit_option:
    call CLEAR_SCREEN     
    call EXIT
    
;---------------------------------------
    end_of_operation:
        PUTS_STRING continue_msg
        GETCHAR bl
        POP_ALL  
        call CLEAR_SCREEN
    jmp choice_loop  

;=======================================
;DATA:
;---------------------------------------
number_digit dw 0
delay_value  db 10 dup('$')
\n           db 0dh, 0ah, '$'

century_value db 10 dup('$')
year_value    db 10 dup('$')
month_value   db 10 dup('$')
day_value     db 1000 dup(20h)
hours_value   db 10 dup('$')
minutes_value db 10 dup('$')
seconds_value db 10 dup('$')

choosing_freq db 5 dup('$')
possible_freq db 03h, 04h, 05h, 06h, 07h, 08h, 09h, 0Ah, 0Bh, 0Ch, 0Dh, 0Eh, 0Fh

;MENU:
invite_msg  db "CHOOSE AN OPTION:", 0dh, 0ah, '$'
options     db "1. Get date&time;", 0dh, 0ah
            db "2. Set time;", 0dh, 0ah
            db "3. Set date;", 0dh, 0ah
            db "4. Set alarm;", 0ah, 0dh
            db "5. Get alarm;", 0ah, 0dh
            db "6. Set delay;", 0ah, 0dh
            db "7. Get register 0Bh;", 0ah, 0dh
            db "8. Set frequancy;", 0ah, 0dh
            db "9. Get register 0Ah;", 0ah, 0dh
            db "0. Exit.", 0dh, 0ah, '$'

frequancy_menu db "1.  8 kHz;", 0ah, 0dh
               db "2.  4 kHz;", 0ah, 0dh
               db "3.  2 kHz;", 0ah, 0dh
               db "4.  1 kHz;", 0ah, 0dh
               db "5.  512 Hz;", 0ah, 0dh
               db "6.  256 Hz;", 0ah, 0dh    
               db "7.  128 Hz;", 0ah, 0dh
               db "8.  64 Hz;", 0ah, 0dh
               db "9.  32 Hz;", 0ah, 0dh
               db "10. 16 Hz;", 0ah, 0dh
               db "11. 8 Hz;", 0ah, 0dh
               db "12. 4 Hz;", 0ah, 0dh
               db "13. 2 Hz.", 0ah, 0dh, '$'

;INFORMATION STRINGS:
year_msg     db "Year: $" 
century_msg  db 0ah, 0dh, "Century: $"
month_msg    db 0ah, 0dh, "Month: $"
day_msg      db 0ah, 0dh, "Day: $"
hours_msg    db "Hours: $"
minutes_msg  db 0ah, 0dh, "Minuts: $"
seconds_msg  db 0ah, 0dh, "Seconds: $"
date_msg     db "Date: $"
time_msg     db "Time: $"
delay_msg    db "ENTER A DELAY (ms, <65s): $"
trnd_off_msg db "ALARM IS TURNED OFF.", 0ah, 0dh, 0ah, 0dh, '$' 
error_msg    db 0ah, 0dh, "ERROR!", 0dh, 0ah, '$'
continue_msg db 0ah, 0dh, "Press any key to continue...", 0ah, 0dh, '$'
                
end start 