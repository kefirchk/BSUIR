.model small
.data 
enterInfo db 'Enter something: $'  ;string type values
yourInfo db 'Your information: $'
otst db '', 0DH,0Ah,'$'

namepar label byte       ;pointer
maxlen db 20             ;length of the line
actlen db ?              ;factual length 
infofld db 20 dup('$')   ;value             

.code
    start:
    MOV AX, DATA      ;push our data in register
    MOV DS, AX
    
    LEA DX, enterInfo ;output of invite
    MOV AH, 09        ;calling the 9 command of 
    INT 21h           ;21 interruption
    
    LEA DX, namepar   ;input of line
    MOV AH, 0ah       ;calling the 0a command of 
    INT 21h           ;21 interruption
    
    MOV AH, 09        ;== '\n'
    LEA DX, otst
    INT 21h
    
    MOV AH, 09
    LEA DX, yourInfo  ;output of the line
    INT 21h        
    
    LEA DX, infofld   ;output of your information
    INT 21h
    
    MOV AH, 4ch       ;correct finnishing of program
    INT 21h
    
    ;RET               ;return
    end start         ;end of start
END





;===========================================
;another option
;===========================================

;.model large 
;DATA SEGMENT
;enterInfo db 'Enter something: $'  ;string type values
;yourInfo db 'Your information: $'
;otst db '', 0DH,0Ah,'$'
;
;namepar label byte       ;pointer
;maxlen db 20             ;length of the line
;actlen db ?              ;factual length 
;infofld db 20 dup('$')   ;value
;DATA ENDS             
;
;STK SEGMENT STACK        ;description of the stack
;db 256 dup('')
;STK ENDS
;
;CODE SEGMENT
;    ASSUME CS:CODE, DS:DATA, SS:STK
;    start:
;    MOV AX, DATA      ;push our data in register
;    MOV DS, AX
;    
;    LEA DX, enterInfo ;output of invite
;    MOV AH, 09        ;calling the 9 command of 
;    INT 21h           ;21 interruption
;    
;    LEA DX, namepar   ;input of line
;    MOV AH, 0ah       ;calling the 0a command of 
;    INT 21h           ;21 interruption
;    
;    MOV AH, 09        ;== '\n'
;    LEA DX, otst
;    INT 21h
;    
;    MOV AH, 09
;    LEA DX, yourInfo  ;output of the line
;    INT 21h        
;    
;    LEA DX, infofld   ;output of your information
;    INT 21h
;    
;    MOV AH, 4ch       ;correct finnishing of program
;    INT 21h
;    
;    ;RET               ;return
;    end start         ;end of start
;CODE ENDS
;END