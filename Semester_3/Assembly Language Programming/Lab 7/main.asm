.model small
.stack 100h
.data
;===========================================================
;const int:
    max_path_size equ 124
    min_num       equ 32768
    max_num       equ 32767
    string_size   equ 10
    ten   dw 10
    minus dw -1
;===========================================================
;const char*:
    result_msg      db "Result: ",'$'
    overflow_msg    db "Overflow!",'$'
    math_exp_msg    db "Mathematical expression: ", '$'
    wrong_input_msg db "Wrong input!",'$'
    wrong_args db "Wrong arguments", 0Dh, 0Ah
               db "Correct format:", 0Dh, 0Ah
               db "[Your program] ",'"',"mathematical expression",'"', 0Dh, 0Ah, '$'     
    program_over db "Program is over",0Dh,0Ah,'$'   
    enter db 0Dh,0Ah,'$'
    pathAdd db "add.exe", 0
    pathSub db "sub.exe", 0
    pathMul db "mul.exe", 0
    pathDiv db "div.exe", 0
;===========================================================   
    math_exp db max_path_size dup(0)
    PSP dw ?        ;Program Segment Prefix
    EPB dw ?        ;Exec Parameter Blok
        dw 0
    
    sign dw ?
    current_element dw ? 
    string db string_size dup('$')
    previous_operation dw ?
    run_adr dw 0
    run_seg dw ?
    
    ;stacks:
    ;-----------------------------------
    start_of_stack_numbers equ 0F926h   ;63782
    start_of_stack_operations equ 9C40h ;40000
    stack_of_numbers dw 0F926h
    stack_of_operations dw 9C40h      
    ;----------------------------------- 
.code
    jmp start

;===========================================================
;========================MACROS=============================                 
;-----------------------------------------------------------
     
ExecOverlay MACRO
    call dword ptr run_adr
ENDM                                            

;===========================================================
LoadOverlay MACRO overlayPath
    push dx
    push bx
    push ax

    lea dx, overlayPath
    lea bx, EPB 
    mov ax, 4B03h 
    int 21h

    pop ax
    pop bx
    pop dx
ENDM

;===========================================================    
OutputString MACRO str
    mov ah, 09h
    mov dx, offset str
    int 21h
ENDM

;===========================================================
Output_symbol MACRO symb                                                                                                      
    mov dx,symb
    mov ah,06h
    int 21h
ENDM

;===========================================================
;==========================START============================
;-----------------------------------------------------------    
start:
    push ds
    mov	ax,@data                      
    mov	ds,ax 
    pop PSP
;-----------------------------------------------------------   
;resize block of memory
    mov ax, progEnd  ;temp segment no know size of program 
    mov dx, es
    sub ax, dx
    mov bx, ax       ;new size in 16-byte's paragraphs
    mov ah, 4Ah
    int 21h        
;-----------------------------------------------------------     
;allocate a block of memory for overlay
    mov ah, 48h  
    mov bx, 1000h    ;how much memory we want to get    
    int 21h          ;AX = adress of getting block of memory
;-----------------------------------------------------------    
;save overlay segment
    mov EPB, ax  
    mov EPB+2, ax   ;offset of command line
    mov run_seg, ax 
    mov ax, ds
    mov es, ax

    mov ax, @data
    mov ds, ax
    mov es, ax
    
    ;analyse command line
    ;--------------------
    call parseCommandLine
    jc Error_wrong_args
    ;--------------------              
    
    ;calcucalte mathematical expression
    ;----------------------------------
    outputString math_exp_msg
    mov si,offset math_exp
    call Output         ;character-by-character output
    outputString enter  ;\n
    call CalculateExpression
    ;----------------------------------
    
    Final_loop:
        cmp [stack_of_operations], start_of_stack_operations  ;empty?
        je Final_end
    
    call GetOperationFromStack
    mov dx, ax
    call GetNumberFromStack
    mov cx, ax
    call GetNumberFromStack
    
    mov dh,0
    cmp dx, '+'
    jne FinalSub
    
    cmp previous_operation, dx
    je FinalWithoutChange_add
    LoadOverlay pathAdd  
    
    FinalWithoutChange_add:
        ExecOverlay
        mov previous_operation, dx
        jmp Final_complete
    
    FinalSub:
        cmp dx, '-'
        jne FinalMul
    
        cmp previous_operation, dx
        je FinalWithoutChange_sub
        LoadOverlay pathSub  
    
    FinalWithoutChange_sub:
        ExecOverlay
        mov previous_operation, dx
        jmp Final_complete
    
    FinalMul:
        cmp dx, '*'
        jne FinalDiv
    
        cmp previous_operation, dx
        je FinalWithoutChange_mul
        LoadOverlay pathMul  
    
    FinalWithoutChange_mul:
        ExecOverlay
        mov previous_operation, dx
        jmp Final_complete
    
    FinalDiv:
        cmp previous_operation, dx
        je FinalWithoutChange_div   
        LoadOverlay pathDiv
    FinalWithoutChange_div:
        xor dx, dx
        ExecOverlay
        mov previous_operation, dx
    
    Final_complete:
    
        call NumberToStack
        jmp Final_loop  
    
    Final_end: 
        push ax
        OutputString result_msg 
        pop ax   
        cmp ax,0
        js Negative_sign
        jns Positive_sign 
    
        OutputString enter
    
        jmp _end
    
    Error_wrong_args:
        outputString wrong_args
        jmp _end

    _end:    
        call Exit

;===========================================================
;================PROCEDURES of WORK with NUMBERS============
;-----------------------------------------------------------
CHECK_NUM PROC
    mov si,offset string
    cmp [si],'-' 
    je Negative_num
    mov bx,0
    mov sign,1
    jmp _num
    
    Negative_num:
       mov sign,-1
       inc si
       mov bx,0
       
    _num:
    call ConvertNumber 
    ret
ENDP

;===========================================================
ConvertNumber PROC
    mov ax,ten
    mul bx
    mov bx,ax
    push bx
    mov ax,0
    mov al,[si]
    sub ax,'0'
    pop bx
    add bx,ax
    inc si
    cmp [si],'$'
    jne call ConvertNumber
    mov ax,bx
    
    cmp sign,-1
    je min_point
    jne max_point
    
    max_point:    
        cmp ax,max_num
        ja OutputWrongInput
        jmp point
    
    min_point:
        cmp ax,min_num
        ja OutputWrongInput
    
    point:    
        mul sign
        mov current_element,ax
    ret
ENDP

;===========================================================
NEGATIVE_SIGN PROC
    mov sign,-1    
    
    push ds
    mov bx,es
    pop es
    mov ds,bx
    
    mul minus
    
    push ds
    mov bx,es
    pop es
    mov ds,bx
    
    mov di,0
    call OutputNumber 
    ret
ENDP

;===========================================================
POSITIVE_SIGN PROC
    mov sign,1
    mov di,0
    call OutputNumber
    ret
ENDP

;===========================================================
OutputNumber PROC
    Outp: 
        inc di
        mov dx,0
    
        push ds
        mov bx,es
        pop es
        mov ds,bx
    
        div ten 
        jo OutputOverflow
    
        push ds
        mov bx,es
        pop es
        mov ds,bx
    
        add dx,'0'
        push dx
        cmp ax,0
        jne Outp
    
        cmp sign,-1
        jne Output_num
        Output_symbol '-'
    
    Output_num:
        pop ax
        Output_symbol ax
        dec di
        cmp di,0
    jg loop Output_num
    
    OutputString enter
    call Exit
    
    ret
ENDP

;===========================================================
;================PROCEDURES of WORK with STACK==============
;-----------------------------------------------------------

GetOperationFromStack PROC
    push dx
    mov dx, sp
    mov sp, [stack_of_operations]
    pop ax
    mov [stack_of_operations], sp
    mov sp, dx
    pop dx  
    ret
ENDP

;===========================================================
OperationToStack PROC
    push dx
    
    mov dx, sp
    mov sp, [stack_of_operations]
    push ax
    mov [stack_of_operations], sp
    mov sp, dx
    
    pop dx
    ret
    ret
ENDP  

;===========================================================
GetNumberFromStack PROC  ;output: ax - number
    push dx
    mov dx, sp
    mov sp, [stack_of_numbers]
    pop ax
    mov [stack_of_numbers], sp
    mov sp, dx   
    pop dx  
    ret
ENDP

;===========================================================
NumberToStack PROC
    push dx
    
    mov dx, sp
    mov sp, [stack_of_numbers]
    push ax
    mov [stack_of_numbers], sp
    mov sp, dx
    
    pop dx
    ret
ENDP

;===========================================================    
;====================OTHER PROCEDURES=======================
;-----------------------------------------------------------
parseCommandLine PROC
    push si
    push di
    push ax
    push cx

    mov ah, 62h
    int 21h
    mov PSP, bx

    push ds

    mov ds, bx
    xor ah, ah
    mov al, byte ptr ds:[80h]
    pop ds
    cmp al, 0
    je parseCommandLine_error

    xor ch, ch
    mov cl, al
    mov si, 81h
    
    mov di, offset math_exp
    call getWord
    jc parseCommandLine_error

    parseCommandLine_fine:
        clc
        jmp parseCommandLine_end

    parseCommandLine_error:
        stc
        jmp parseCommandLine_end

    parseCommandLine_end:
        pop cx
        pop ax
        pop di
        pop si
    ret
ENDP

;===========================================================
Output PROC      
    Output_loop:
        lodsb
        cmp al, 0
        je Output_end
        mov ah, 02h
        mov dl, al
        int 21h
        jmp Output_loop  
        
    Output_end:
    ret
ENDP

;===========================================================
OutputWrongInput PROC
    OutputString wrong_input_msg
    OutputString enter
    call Exit
ENDP

;===========================================================
OutputOverflow PROC
    OutputString overflow_msg
    OutputString enter
    call Exit
ENDP

;===========================================================
GetWord PROC; si - source, di - dest, cx - size; output: si is modified, cx is modified
    push bx
    push ax
    push di
    push ds

    mov ax, PSP
    mov ds, ax

    mov bx, di
    mov di, si
    cmp byte ptr [di], '"'
    je Get_word_no_spaces   
    mov al, ' '
    repe scasb        
    
    Get_word_no_spaces:
        scasb
        mov si, di
        mov di, bx
        cmp cx, 0
        je Get_word_error

    Get_word_space_loop:
        lodsb
        cmp al, '"'
        je Get_word_space
        cmp al, '0'
        jl Check_expression
        cmp al, '9'
        jg Check_expression
        jmp Check_expression_end
    
        Check_expression:
            cmp al, '+'
            je Check_expression_end
            cmp al, '-'
            je Check_expression_end
            cmp al, '/'
            je Check_expression_end
            cmp al, '*'
            je Check_expression_end
            cmp al, ' '
            je Check_expression_end
    
        Check_expression_error:
            pop ds
            pop di
            pop ax
            pop bx
    
        call OutputWrongInput
    
        Check_expression_end:
            stosb
            
    loop Get_word_space_loop

    jmp Get_word_fine

    Get_word_space:
        dec cx
        jmp Get_word_fine

    Get_word_fine:
        clc
        jmp Get_word_end

    Get_word_error:
        stc
        jmp Get_word_end

    Get_word_end:
        pop ds
        pop di
        pop ax
        pop bx
    ret
ENDP

;===========================================================
CalculateExpression proc
    mov si, offset math_exp
    dec si
    
    FindNumber:
        mov di, offset string 
        mov cx,10     
        ClearString:
            ;cmp cx,0
            ;je FindNumber_continue
            mov [di],'$'
            inc di
            ;dec cx
            loop ClearString

        FindNumber_continue:
            mov di, offset string 
    
        FindNumber_skipSpaces:
            inc si
            cmp [si], ' '
            je OutputWrongInput ;if math_exp[0] == ' ' for example
    
        FindNumber_afterSpaces:
            cmp [si], '-'
            jne FindNumber_onlyNumber
            movsb

        FindNumber_onlyNumber:
            cmp [si], ' '
            je FindNumber_end
            cmp [si], '$'
            je FindNumber_end 
            cmp [si], 0
            je FindNumber_end   
            cmp [si], '0'
            jl OutputWrongInput
            cmp [si], '9'
            jg OutputWrongInput
    
        movsb  ;[si]->[di]
        jmp FindNumber_onlyNumber 
    
        FindNumber_end:
            mov di, offset string
            cmp [di], '$'    
            je CalculateExpression_end
    
    push si
    call Check_num
    call NumberToStack
    pop si       
    
    ;FindOperation:
        ;dec si
        FindOperation_skipSpaces:
            inc si
            cmp [si], ' '
            je OutputWrongInput
    
        FindOperation_afterSpaces:
            cmp [si], '*'
            je FindOperation_noError
            cmp [si], '/'
            je FindOperation_noError
            cmp [si], '+'
            je FindOperation_noError
            cmp [si], '-'
            je FindOperation_noError
            cmp [si], 0
            je CalculateExpression_end
    
        FindOperation_error:
            call OutputWrongInput
   
        FindOperation_noError:
            inc si
            cmp [si], ' '
            je FindOperation_addToStack
            jne FindOperation_error
    
        FindOperation_addToStack:
            dec si

    CheckPriority:    
        mov bx, [si]
        cmp [stack_of_operations], start_of_stack_operations
        je FindOperation_addToStackWithoutChanges
        
        mov bx, ax
        call GetOperationFromStack
        call OperationToStack   
        call GetPriority
    
        mov ax, dx
        push ax
        mov ax, [si]
        call GetPriority
        pop ax   
        cmp ax, dx
        jb FindOperation_addToStackWithoutChanges    
        call GetOperationFromStack
        mov dx, ax
        call GetNumberFromStack
        mov cx, ax
        call GetNumberFromStack
    
        mov dh,0
        cmp dx, '+'
        jne FindOperation_sub
    
        cmp previous_operation, dx
        je withoutchange_add
        LoadOverlay pathAdd
    Withoutchange_add:
        ExecOverlay
        mov previous_operation, dx
        jmp FindOperation_endOp
     
    FindOperation_sub:
        cmp dx, '-'
        jne FindOperation_mul 
        cmp previous_operation, dx
        je WithoutChange_sub
        LoadOverlay pathSub
    WithoutChange_sub:
        ExecOverlay
        mov previous_operation, dx
        jmp FindOperation_endOp
    
    FindOperation_mul:
        cmp dx, '*'
        jne FindOperation_div
        cmp previous_operation, dx
        je WithoutChange_mul
        LoadOverlay pathMul
    WithoutChange_mul:
        ExecOverlay 
        mov previous_operation, dx
        jmp FindOperation_endOp
    
    FindOperation_div:
        cmp previous_operation, dx
        je withoutchange_div   
        LoadOverlay pathDiv
    Withoutchange_div: 
        xor dx, dx
        ExecOverlay 
        mov previous_operation, dx
        
    FindOperation_endOp:
        
        call numberToStack
        jmp CheckPriority        
    
    FindOperation_addToStackWithoutChanges:
        mov ax,[si]
        call OperationToStack   
        inc si 

    jmp FindNumber    
    
CalculateExpression_end:
    mov si, offset math_exp
    cmp [si], 0
    je call Exit 
    ret
ENDP

;===========================================================
GetPriority PROC
    mov ah, 0 
    cmp ax, '+'
    jne substr
    mov dx, 1
    jmp toEnd
    substr:
        cmp ax, '-'
        jne multipl
        mov dx, 1
        jmp toEnd
    multipl:
        cmp ax, '*'
        jne division
        mov dx, 3
        jmp toEnd
    division:
        cmp ax, '/'
        mov dx, 3
    toEnd:
    ret 
ENDP 

;===========================================================
Exit PROC
    outputString program_over
    
    mov ax,4C00h
    int 21h
    ret
ENDP

;===========================================================
progEnd segment
progEnd ends    
end start    