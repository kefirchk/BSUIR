; multi-segment executable file template. 
.model small
.stack 100h
.data
;data segment
;snake size    
s_size  db     3

;max snake size
max_s_size equ 50 

;direction constants(bios key codes)
left    equ     4bh
right   equ     4dh
up      equ     48h
down    equ     50h  

;borders of playing field
left_border  equ   5
right_border equ   74
up_border    equ   3
down_border  equ   20
 
;body coordinates
snake dw max_s_size dup(0) 

;food coordinates
coordinates dw 0  

;current snake direction
cur_dir db      right 

;messages
first_message db 'Press any key to start playing!', 0dh,0ah, '$' 
second_message db 'GAME OVER, LOSER!!!', 0dh,0ah, '$'

;tail coordinates 
tail    dw      ?   

;health level
hp      db     '3'  

;score level
score   db     '0'  

;value for random method
seed    db     60

;playing field 
field db ' SCORE: 0   HP: 3', 0dh,0ah
    db 5 dup(' '), 218, 68 dup(196), 191, 0dh,0ah
	db 5 dup(' '), 179, 68 dup(' '), 179, 0dh,0ah
	db 5 dup(' '), 179, 68 dup(' '), 179, 0dh,0ah 
	db 5 dup(' '), 179, 68 dup(' '), 179, 0dh,0ah
	db 5 dup(' '), 179, 68 dup(' '), 179, 0dh,0ah
	db 5 dup(' '), 179, 68 dup(' '), 179, 0dh,0ah
	db 5 dup(' '), 179, 68 dup(' '), 179, 0dh,0ah 
	db 5 dup(' '), 179, 68 dup(' '), 179, 0dh,0ah
	db 5 dup(' '), 179, 68 dup(' '), 179, 0dh,0ah
	db 5 dup(' '), 179, 68 dup(' '), 179, 0dh,0ah
	db 5 dup(' '), 179, 68 dup(' '), 179, 0dh,0ah 
	db 5 dup(' '), 179, 68 dup(' '), 179, 0dh,0ah
	db 5 dup(' '), 179, 68 dup(' '), 179, 0dh,0ah 
	db 5 dup(' '), 179, 68 dup(' '), 179, 0dh,0ah
	db 5 dup(' '), 179, 68 dup(' '), 179, 0dh,0ah 
	db 5 dup(' '), 179, 68 dup(' '), 179, 0dh,0ah
	db 5 dup(' '), 179, 68 dup(' '), 179, 0dh,0ah
	db 5 dup(' '), 179, 68 dup(' '), 179, 0dh,0ah
	db 5 dup(' '), 192, 68 dup(196), 217, 0dh,0ah, '$'   

wait_time dw    0
ends

;stack segment
;    dw   128  dup(0)
;ends

;code segment
.code

start proc

; set segment registers:
    mov ax, @data
    mov ds, ax
    mov es, ax

;(set cursor position)
mov ah, 02h          
mov bh, 0        ;set video page
mov dh, 11       ;set string
mov dl, 22       ;set column
int 10h
 
;(print message)  
mov dx, offset first_message
mov ah, 09h
int 21h   

;(hide text cursor)
mov ah, 02h
mov dh, 25   ;set string
mov dl, 0    ;set column
int 10h    

;(wait for any key)
mov ah, 00h
int 16h  
  
;(set cursor position)
mov ah, 02h          
mov bh, 0       ;set video page
mov dh, 2       ;set string
mov dl, 5       ;set column
int 10h

;(print playing field) 
mov dx, offset field
mov ah, 09h
int 21h
call print_food  ;print first food 

;(set snake hade at the centre of the field)      
mov b.snake[0], 35
mov b.snake[1], 10

game_loop: 
;(check hp level)
xor ax, ax
mov al, hp
cmp al, '0'
je stop_game

;(show new head, set cursor at dl,dh)
mov dx, snake[0]
mov ah, 02h
int 10h     

;(print new part at the location)
mov al, 0dbh ;sign to write
mov ah, 09h  ;BIOS function
mov bl, 0ah  ;attribute.
mov cx, 1    ;single char.
int 10h 

;if snake its food(head coordinats == food coordinates)
cmp dx, coordinates
je add_food
jne skip_adding_food
add_food:
call change_score
call print_food 
inc s_size
skip_adding_food:

;(keep the tail) snake[s_size * 2 - 2]
xor ax, ax
mov al, s_size
mov di, ax
add di, ax
sub di, 2
mov ax, snake[di]
mov tail, ax

call move_snake

;(hide old tail, set cursor at dl,dh)
mov dx, tail
mov ah, 02h
int 10h

;(print ' ' at the location)
mov al, ' ' ;sign to write
mov ah, 09h ;BIOS function
mov bl, 0eh ;attribute.
mov cx, 1   ;single char.
int 10h

check_for_key:

;(check for player commands)
mov ah, 01h  ;BIOS function
int 16h      ;has button been pressed(check buffer)
jz  no_key   

mov ah, 00h  ;read sign(asci) from bufer to al
int 16h      

cmp al, 1bh    ;esc - key? (check scan-code)
je  stop_game  

mov cur_dir, ah ;write to cur_dir direction 
jmp game_loop

no_key:

;wait a few moments here:
;get number of clock ticks
;(about 18 per second)
;since midnight into cx:dx
mov     ah, 00h
int     1ah
cmp     dx, wait_time
jb      check_for_key
add     dx, 4
mov     wait_time, dx

;eternal game loop:
jmp     game_loop

stop_game: 
;(change video page) 
mov ah, 05h
mov al, 1
int 10h  

;(set cursor position)
mov ah, 02h          
mov bh, 1        ;set video page
mov dh, 11       ;set string
mov dl, 30       ;set column
int 10h   

;(print playing field) 
mov dx, offset second_message
mov ah, 09h
int 21h

mov ah, 4Ch
int 21h
ret

start endp

move_snake proc near
    
  xor ax, ax        ;s_size * 2 - 2
  mov al, s_size
  mov di, ax
  add di, ax
  sub di, 2
  ; point di to tail
  ;move all body parts
  ;(last one simply goes away) 
  dec ax
  mov   cx, ax
move_array:
  mov   ax, snake[di-2]
  mov   snake[di], ax
  sub   di, 2
  loop  move_array


cmp     cur_dir, left
  je    move_left
cmp     cur_dir, right
  je    move_right
cmp     cur_dir, up
  je    move_up
cmp     cur_dir, down
  je    move_down

jmp     stop_move           ;no direction.


move_left:
  mov   al, b.snake[0]
  dec   al
  mov   b.snake[0], al
  cmp   al, left_border
  jne   stop_move       
  mov   al, right_border    ;col number.
  dec   al
  mov   b.snake[0], al      ;return to right.
    call decrease_hp  
  jmp   stop_move

move_right:
  mov   al, b.snake[0]
  inc   al
  mov   b.snake[0], al
  cmp   al, right_border    ;col number.   
  jb    stop_move  
  mov   al, left_border
  inc   al
  mov   b.snake[0], al      ;return to left.
    call decrease_hp  
  jmp   stop_move

move_up:
  mov   al, b.snake[1]
  dec   al
  mov   b.snake[1], al
  cmp   al, up_border
  jne   stop_move
  mov   al, down_border     ;row number -1.
  mov   b.snake[1], al      ;return to bottom.  
    call decrease_hp  
  jmp   stop_move

move_down:
  mov   al, b.snake[1]
  inc   al
  mov   b.snake[1], al
  cmp   al, down_border     ;row number -1.
  jbe   stop_move  
  mov   al, up_border
  inc   al
  mov   b.snake[1], al      ;return to top.  
    call decrease_hp
  jmp   stop_move

stop_move:
  ret
move_snake endp     


;(this proc decrease snake hp)
decrease_hp proc near
;decrease hp level 
    xor ax, ax 
    mov al, hp 
    dec al
    mov hp, al    
    mov ah, '0'
    cmp al, ah
    jg rewrite_hp
    je not_to_rewrite   
    
rewrite_hp: 
 ;set cursor position   
    mov ah, 02h      
    mov dh, 2
    mov dl, 21
    int 10h
;write new hp status
    mov al, hp
    mov ah, 09h ;BIOS function
    mov bl, 08h ; attribute.
    mov cx, 1   ; single char.
    int 10h   
not_to_rewrite:    
ret
decrease_hp endp   

;get random number(min =  bh; max = bl)
;result in 'seed' and ah
random_number proc
repeat: 
    mov ah, 2ch      ;function to get time
    int 21h
    add dh, seed     ;add seed to secunds 
    xor ax, ax
    mov al, dh       ;mov sum to ax for division
    div bl           ;in ah remainder
    cmp ah, bh       ;if ah < min then repeat 
    jb repeat
    mov seed, ah     ;remember last value    
ret
random_number endp  
  
  
;this proc print food on the playing field  
print_food proc   
;get string
    mov bh, left_border         ;set min value
    inc bh
    mov bl, right_border        ;set max value
    dec bl
    call random_number
    mov b.coordinates[0], ah    ;remember string
;get column
    mov bh, up_border           ;set min value
    inc bh
    mov bl, down_border         ;set max value
    dec bl
    call random_number 
    mov b.coordinates[1], ah    ;remember column
;set cursor position
    mov ah, 02h 
    mov bh, 0                  ;set video page
    mov dh, b.coordinates[1]   ;set column
    mov dl, b.coordinates[0]   ;set string
    int 10h
;print sign
    mov al, 3
    mov ah, 09h ;BIOS function
    mov bl, 0ch ;attribute.
    mov cx, 1   ;single char.
    int 10h   
    
ret
print_food endp  


change_score proc
    inc score 
;set cursor position   
    mov ah, 02h      
    mov dh, 2
    mov dl, 13
    int 10h
;write new score status
    mov al, score
    mov ah, 09h ;BIOS function
    mov bl, 08h ; attribute.
    mov cx, 1   ; single char.
    int 10h       
ret
change_score endp
    
   ; mov ax, 4c00h ; exit to operating system.
;    int 21h    
;ends
 ; set entry point and stop the assembler.
