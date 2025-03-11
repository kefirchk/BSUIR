.model small
.stack 100h
.data

max_size    EQU 82
rows        EQU 4

filename1   db "input file.txt", 0 ;name of the file
filename2   db "output file.txt", 0
id_of_file  dw ?             ;identificator of the file
size_of_file dw ?

my_word     db max_size dup('$') 
symbol      db 1
buffer      db max_size dup('$')
buffer_2    db max_size dup('$')

text_buff   db max_size dup('$')
            db max_size dup('$')
            db max_size dup('$')
            db max_size dup('$')

num_str     db "0000$"

enter_txt_msg db "ENTER A TEXT:", 0dh, 0ah, '$'
enter_wrd_msg db "ENTER A WORD:", 0dh, 0ah, '$'
your_text_msg db 0dh, 0ah, "YOUR TEXT:", 0dh, 0ah, '$'
your_word_msg db 0dh, 0ah, "YOUR WORD:", 0dh, 0ah, '$'
equal_msg   db 0ah, 0dh, "LINE HAS SUCH WORD.", 0dh, 0ah, '$' 
\n db 0dh, 0ah, '$'

;MESSAGES FOR WORK WITH FILES
open_msg    db "FILE IS OPENED!", 0dh, 0ah, '$' 
create_msg  db "FILE IS CREATED!", 0dh, 0ah, '$'
write_msg   db "THE INFORMATION WAS WRITTEN IN A FILE!", 0dh, 0ah, '$'
close_msg   db "FILE IS CLOSED!", 0dh, 0ah, '$'
delete_msg  db "FILES ARE DELETED!", 0dh, 0ah, '$'
read_msg    db "THE INFORMATION OF THE FILE:", 0dh, 0ah, '$'
error_msg   db "ERROR!", 0dh, 0ah, '$'
error_create_msg db "ERROR CREATING FILE!", 0dh, 0ah, '$'
error_open_msg   db "ERROR OPENING FILE!", 0dh, 0ah, '$'
error_close_msg  db "ERROR CLOSING FILE!", 0dh, 0ah, '$'
error_delete_msg db "ERROR DELETING FILE!", 0dh, 0ah, '$'
error_read_msg   db "ERROR READING FILE!", 0dh, 0ah, '$'
error_write_msg  db "ERROR WRITING FILE!", 0dh, 0ah, '$'
error_find_msg   db "ERROR FINDING FILE!", 0dh, 0ah, '$'

;MENU:
invite_msg  db "CHOOSE AN OPTION:", 0dh, 0ah, '$'
option_1    db "1. Create files.", 0dh, 0ah, '$'
option_2    db "2. Write information to a file.", 0dh, 0ah, '$'
option_3    db "3. Read information from a file.", 0dh, 0ah, '$'
option_4    db "4. Delete files.", 0dh, 0ah, '$'
option_5    db "5. Perform a task", 0dh, 0ah, '$'
option_6    db "6. Exit.", 0dh, 0ah, '$'
option_to_read_from db "Choose file for reading:", 0dh, 0ah, '1 - input file', 0dh, 0ah, '2 - output file', 0dh, 0ah, '$'
     
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

GETS_STRING MACRO str
    PUSH_ALL
    mov ah, 0ah
    mov dx, offset str
    int 21h
    POP_ALL
ENDM

GETCHAR MACRO
    PUSH_ALL
    mov ah, 08h
    int 21h
    mov symbol, al
    POP_ALL
ENDM

;---------------------------------------
FIND_FILE MACRO filename
    PUSH_ALL
    mov ah, 4eh      ;find the first file
    mov al, 00h
    xor cx, cx
    lea dx, filename
    int 21h
    jc ERROR_find
    POP_ALL
ENDM 

;---------------------------------------
OPEN_FILE MACRO filename, read_mode     ;for writing/reading
    PUSH_ALL
    mov ah, 3dh       ;open the file
    mov al, read_mode ;access mode for reading = 0, for writing = 1
    xor cx, cx
    mov dx, offset filename
    int 21h
    jc ERROR_open
    mov id_of_file, ax   ;get id of file
    
    ;return to the begin of our file
    mov ah, 42h    ;moving function
    mov al, 00h    ;moving according to the begin of the file
    xor cx, cx     ;distance to move the pointer
    xor dx, dx     ;distance to move the pointer
    int 21h
    PUTS_STRING open_msg
    POP_ALL
ENDM


;=======================================
;MAIN FUCNTION:
;---------------------------------------
main PROC
    mov ax, @data
    mov ds, ax
    call MENU                 
    call EXIT   
ENDP

;=======================================
;FUNCTIONS:
;---------------------------------------
MENU PROC
    choice_loop:
    PUTS_STRING invite_msg
    PUTS_STRING option_1    ;Create files
    PUTS_STRING option_2    ;Write information to a file.
    PUTS_STRING option_3    ;Read information from a file.
    PUTS_STRING option_4    ;Delete files.
    PUTS_STRING option_5    ;Perform a task
    PUTS_STRING option_6    ;Exit.
    GETCHAR
    mov al, symbol
    cmp al, '1'
    je create_option
    cmp al, '2'
    je write_option
    cmp al, '3'
    je read_option
    cmp al, '4'
    je delete_option
    cmp al, '5'
    je perform_task_operation
    cmp al, '6'
    je exit_option
    PUTS_STRING error_msg
    loopne choice_loop
;------------------------
    create_option:
    call CLEAR_SCREEN
    
     ;creating of the output file
    mov bx, offset filename2   
    call CREATE_FILE
    ;creating of the input file
    mov bx, offset filename1   
    call CREATE_FILE
    
    PUTS_STRING \n 
    jmp choice_loop
;------------------------    
    write_option:
    call CLEAR_SCREEN
    FIND_FILE filename1
    
    PUTS_STRING enter_txt_msg
    call INPUT_TEXT
    
    PUTS_STRING \n
    
    OPEN_FILE filename1, 1   ;for writing
    call WRITE_TO_FILE
    call CLOSE_FILE
    PUTS_STRING \n
    jmp choice_loop
;------------------------    
    read_option:
    call CLEAR_SCREEN
    
    FIND_FILE filename1
    FIND_FILE filename2
    
    choose_file_for_read:
    PUTS_STRING option_to_read_from
    GETCHAR
    mov al, symbol
    cmp al, '1'
      je read_input
    cmp al, '2'
      je read_output
    loopne choose_file_for_read
    
    read_input:
    OPEN_FILE filename1, 0   ;for reading
    jmp reading
    
    read_output:
    OPEN_FILE filename2, 0   ;for reading
    
    reading:
    call READ_FROM_FILE
    call CLOSE_FILE
    PUTS_STRING \n
    jmp choice_loop
;------------------------    
    delete_option:
    call CLEAR_SCREEN
    call DELETE_FILES
    PUTS_STRING \n
    jmp choice_loop
;------------------------    
    perform_task_operation:
    call CLEAR_SCREEN
    FIND_FILE filename1
    FIND_FILE filename2
    
    PUTS_STRING enter_wrd_msg
    GETS_STRING my_word
    PUTS_STRING your_word_msg
    PUTS_STRING my_word+2
    PUTS_STRING \n
    PUTS_STRING \n
    
    OPEN_FILE filename1, 0   ;for reading
    call READ_FROM_FILE
    call CLOSE_FILE
    
    call SEARCH_FOR_WORD
    
    ;creating of the output file
    mov bx, offset filename2   
    call CREATE_FILE
    
    OPEN_FILE filename2, 1   ;for writing
    call WRITE_TO_OUTPUT_FILE
    call CLOSE_FILE
    
    PUTS_STRING \n
    jmp choice_loop
;------------------------    
    exit_option:
    call CLEAR_SCREEN
     
    ret
ENDP

;---------------------------------------

SEARCH_FOR_WORD PROC
    PUSH_ALL
    
    mov cx, 4
    xor di, di
    l1:
    mov num_str[di], '0'
    inc di
    loop l1
    
    mov cx, size_of_file
    xor si, si
    xor di, di
    xor bx, bx  ;num of str
    mov dh, '1'
    main_loop:
        search_letter:
        mov ah, my_word[2] 
           
           mov al, 0dh
           cmp al, buffer[di]
             je skip
        
           mov al, 0ah
           cmp al, buffer[di]
             je continue_main_loop
             
           cmp ah, buffer[di]
             je need_letter
           
           mov al, buffer[di]
           cmp al, '$'
             je end_of_search  
           
           skip:
           inc di
        jmp search_letter
        
        continue_main_loop:
        inc bl
        inc di
           
    loop main_loop
    jmp end_of_search
        
    need_letter:
       xor si, si
       search_word:
          mov ah, my_word[2+si]
           
          cmp ah, 0dh
            je FOUND_word
            
          cmp ah, buffer[di]
            jne NOT_FOUND_WORD
          
          mov al, buffer[di]
          cmp al, 0dh
            je NOT_FOUND_word
          
          cmp al, '$'
            je NOT_FOUND_word
          
          inc di
          inc si
       jmp search_word
       
    FOUND_word:
    mov symbol, bl
    push bx
    xor bh, bh
    mov num_str[bx], dh
    pop bx 
    ;add symbol, 30h     
    ;PUTS_STRING equal_msg
    ;PUTCHAR symbol ;num of str
    ;PUTS_STRING \n    
    jmp skip
            
    NOT_FOUND_word:
    jmp skip  
    jmp continue_main_loop      
    
    end_of_search:
    ;PUTS_STRING \n
    ;PUTS_STRING num_str
    ;PUTS_STRING \n
   
    POP_ALL
    ret
ENDP
;---------------------------------------
OUTPUT_TEXT PROC
    PUSH_ALL
    mov cx, 4
    mov bx, 0
    mov ah, 09h
    puts_text:
    lea dx, text_buff[bx+2]
    int 21h
    PUTS_STRING \n
    add bx, max_size
    loop puts_text
    POP_ALL
    ret
ENDP
;---------------------------------------

INPUT_TEXT PROC
    PUSH_ALL
    mov cx, 4
    mov bx, 0
    mov ah, 0ah
    gets_text:
    lea dx, text_buff[bx]
    int 21h
    PUTS_STRING \n
    add bx, max_size
    loop gets_text
    POP_ALL
    ret
ENDP   
;---------------------------------------

READ_FROM_FILE PROC
    PUSH_ALL
    xor bx, bx
    clear_buffer:
    mov al, buffer[bx]
    mov buffer[bx], '$'
    cmp al, '$'
    je completed_clean
    inc bx
    jmp clear_buffer
    
    completed_clean: 
    ;we must to know length of the file:  
    mov ah, 42h    ;moving function
    mov al, 02h    ;moving according to the end of the file
    mov bx, id_of_file
    xor cx, cx     ;distance to move the pointer
    xor dx, dx     ;distance to move the pointer
    int 21h
    ;ax - length of a file now
    ;push lenght in stack for temporary storage
    push ax
    
    ;return to the begin of our file
    mov ah, 42h    ;moving function
    mov al, 00h    ;moving according to the begin of the file
    xor cx, cx     ;distance to move the pointer
    xor dx, dx     ;distance to move the pointer
    int 21h
    
    ;pop AX (length of a file) from stack and move it to cx
    pop cx        ;amount of bytes for reading
    mov size_of_file, cx
    
    mov ah, 3fh   ;read from the file
    mov dx, offset buffer
    int 21h
    jc ERROR_read
    PUTS_STRING read_msg
    PUTS_STRING buffer
    POP_ALL
    ret
ENDP

ERROR_read PROC
    PUSH_ALL
    mov ah, 09h
    mov dx, offset error_read_msg
    int 21h
    POP_ALL
    call EXIT
ENDP

;--------------------------------------- 
WRITE_TO_FILE PROC
    PUSH_ALL
    mov cx, rows
    xor bx, bx
    write_line:
    push cx
    
    mov ah, 40h            ;write to the file
    xor cx, cx
    mov cl, text_buff[1+bx];amount of bytes for writing
    
    lea dx, text_buff[bx+2] 
    add bx, max_size
     
    push bx
    mov bx, id_of_file
    int 21h
  
    mov ah, 40h           ;write to the file
    lea dx, \n
    mov cl, 2
    int 21h
    
    continue_to_write:
    
    pop bx
    jc ERROR_write
    pop cx
    loop write_line
    
    PUTS_STRING write_msg
    POP_ALL
    ret
ENDP

WRITE_TO_OUTPUT_FILE PROC
    PUSH_ALL
    xor bx, bx
    PUSH_ALL
    xor bx, bx  
    xor di, di
    xor si, si
    xor dx, dx
       buff_to_buff_2:
       mov dl, num_str[bx]    ; bx - number, dl - symbol
         mov al, buffer[di]
         cmp al, 0dh
           je increment_di
         cmp al, 0ah
           je increment_di
         
         cmp al, '$'
           je end_of_writing_strs
         
         cmp dl, '1'
           je skip_str 
         cmp dl, '0'
           je str_to_str_2
    
       jmp buff_to_buff_2
    
    str_to_str_2:
       mov al, buffer[di]
       cmp al, 0ah
         je return_to_buff
       mov buffer_2[si], al
       inc di
       inc si
    jmp str_to_str_2
    
    return_to_buff:
    inc bx
    mov buffer_2[si], al    ;move 0ah
    inc si
    jmp buff_to_buff_2
    
    increment_di:
    inc di
    jmp buff_to_buff_2
    
    skip_str:
    inc bx
    skip_str_loop: 
      inc di
      mov al, buffer[di]
      cmp al, 0ah
        je buff_to_buff_2
    jmp skip_str_loop
    
    end_of_writing_strs:
    POP_ALL
    
    mov cx, si            ;amount of bytes for writing
    mov ah, 40h           ;write to the file
    xor ch, ch
    
    lea dx, buffer_2 
    mov bx, id_of_file
    int 21h
    jc ERROR_write
    PUTS_STRING write_msg
    POP_ALL
    ret
ENDP

ERROR_write PROC
    PUSH_ALL
    mov ah, 09h
    mov dx, offset error_write_msg
    int 21h
    POP_ALL
    call EXIT
ENDP
;---------------------------------------
ERROR_open proc
    PUSH_ALL
    mov ah, 09h
    mov dx, offset error_open_msg
    int 21h
    POP_ALL
    call EXIT
ENDP

;---------------------------------------
DELETE_FILES PROC
    PUSH_ALL
    mov ah, 41h     ;delete files
    mov dx, offset filename1
    int 21h
    jc ERROR_delete
    mov ah, 41h     
    mov dx, offset filename2
    int 21h
    jc ERROR_delete
    PUTS_STRING delete_msg
    POP_ALL
    ret
ENDP

ERROR_delete PROC
    PUSH_ALL
    mov ah, 09h
    mov dx, offset error_delete_msg
    int 21h
    POP_ALL
    call EXIT
ENDP

;---------------------------------------
CLOSE_FILE PROC
    PUSH_ALL
    mov ah, 3eh     ;close the file
    mov bx, id_of_file
    int 21h
    jc ERROR_close
    PUTS_STRING close_msg
    POP_ALL
    ret
ENDP

ERROR_close PROC
    PUSH_ALL
    mov ah, 09h
    mov dx, offset error_close_msg
    int 21h
    POP_ALL
    call EXIT
ENDP                                    

;---------------------------------------
CREATE_FILE PROC
    PUSH_ALL
    mov ah, 3ch      ;create a file
    mov dx, bx       ;download adress of the filename to DX from BX
    xor cx, cx       ;no atribute
    int 21h           
    jc ERROR_create
    mov id_of_file, ax       ;get identificator of the file
    PUTS_STRING create_msg
    POP_ALL
    ret
ENDP

ERROR_create PROC
    PUSH_ALL
    mov ah, 09h
    mov dx, offset error_create_msg
    int 21h
    POP_ALL
    call EXIT
ENDP

;---------------------------------------
CLEAR_SCREEN proc  ;This proc clears the user's screen
    PUSH_ALL
    MOV AX,0600h   
    MOV BH,07h      
    MOV CX,0000    
    MOV DX,184Fh   
    INT 10H      
    
    ;set cursor at (0;0)
    xor dx, dx
    xor bx, bx 
    xor ax, ax
    mov ah, 2  ;Interrupt service 10h to change cursor position 
    int 10h 
 
    POP_ALL
    ret
endp
;---------------------------------------
ERROR_find PROC
    PUSH_ALL
    mov ah, 09h
    mov dx, offset error_find_msg
    int 21h
    POP_ALL
    call EXIT
ENDP
;---------------------------------------
EXIT PROC
    mov ah, 4ch
    int 21h
    ret
ENDP
;---------------------------------------
END