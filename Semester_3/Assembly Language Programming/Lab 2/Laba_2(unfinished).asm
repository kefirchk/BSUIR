.model small
.stack 100h
.data
;======================================
;PARAMETRES FOR INPUT
;--------------------------------------
  MyString db 20, 20 dup('$')
  SubStr1 db 20, 20 dup('$')
  SubStr2 db 20, 20 dup('$')
  maxlen EQU 20 
;--------------------------------------      
  Invite  db 'Enter your line: $' ;10 and 13 - perevod stroki i vozvrat karetki v nachalo
  Invite1 db 10, 13, 'Enter the first substring: $'
  Invite2 db 0ah, 0dh, 'Enter the second substring: $'  
  ResOfInput db 10, 13, 'Your line: $'
  ;ERROR db 10, 13, 'ERROR!$'  
;======================================              
.code                 
start:
;======================================
;INITIALIZATION OF DATA
;--------------------------------------       
     MOV AX, @data               
     MOV DS, AX
     MOV ES, AX
     
;the first byte - max size of string:     
     MOV AH, maxlen
     MOV MyString[0], AH
     MOV SubStr1[0], AH
     MOV SubStr2[0], AH
;======================================
;INPUT OF THE MAIN STRING
;--------------------------------------
     MOV DX, offset Invite       
     CALL puts
     MOV DX, offset MyString                         
     CALL gets 
     MOV DX, offset ResOfInput
     CALL puts
     MOV DX, offset MyString+2             
     CALL puts
;======================================     
;INPUT OF THE FIRST SUBSTRING
;--------------------------------------    
     MOV DX, offset Invite1      
     CALL puts 
     MOV DX, offset SubStr1                         
     CALL gets
;======================================
;INPUT OF THE SECOND SUBSTRING
;--------------------------------------     
     MOV DX, offset Invite2            
     CALL puts                        
     MOV DX, offset SubStr2                         
     CALL gets                       
;======================================                
     
     XOR CX, CX
     MOV AL, MyString[1]
     CMP AL, SubStr1[1] ;if length of MyString less than SubStr1
     JB exit 
     
     
     CALL strlen                          ;undinished code is here
     XOR AX, AX
     L1:
     MOV AL, MyString[2+si]
     MOV AH, SubStr1[2+di]
     CMP ah, al
     JE inc_di
     mov di, 0
     inc_di:
     inc di
     jmp L1_continue
     L1_continue:
     inc si
     cmp ah, '$'
     je exit
     LOOP L1
     
     
     
     JMP exit
ends start  
;======================================
;OUTPUT OF STRING FUNCTION
;--------------------------------------  
puts:  
     MOV AH, 9                    
     INT 21h
     RET
;======================================
;INPUT OF STRING FUNCTION
;--------------------------------------
gets:  
     MOV AH, 10
     INT 21h
     RET
;======================================
;STRING LENGTH COUNTING FUNCTION
;--------------------------------------
strlen:
     push si
     xor cx, cx
     .Loop1:
        CMP MyString[2+si], '$'
        JE .break
        inc si                   ;counter
        inc cl                   ;length of the line
     JMP .Loop1
     .break:
     mov MyString[1], cl
     mov ch, 0 
     pop si
     ret
;======================================
;EXIT FUNCTION
;-------------------------------------- 
exit:
     MOV AH, 4ch
     INT 21h
     RET     
;======================================       