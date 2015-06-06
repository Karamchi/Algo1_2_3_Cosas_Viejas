global suma
global diagonal

section .text

;------------------------------------------------

suma:
    ; RDI = vector
    ; SI = n
    
     push rbp
     mov rbp, rsp
     push r12
	
     xor r12,r12		; R12 = inicializo acumulador
     xor rcx, rcx    
     mov cx, si			; RCX = iteraciones = columnas	 

	.cicloSuma:
		 add r12w, [rdi]
		 lea rdi, [rdi+2] 	; me muevo dentro del vector
		 loop .cicloSuma
     
	mov rax, r12			; devuelvo resultado

	.fin:
		 pop r12
		 pop rbp
		 ret

;------------------------------------------------

diagonal:
    push rbp
    mov rbp, rsp
    push r12
    push r13

    ; rdi=matriz
    ; rdx=resultado

    xor r12,r12 ;donde estamos del vector
    xor rcx,rcx ;tamaño diag
    mov cx, si  ;"      "
    
    .cicloDiag:
        mov rax, [rdx+r12]
        add rax, [rdi]
        inc r12
        lea rdi, [rdi+2*rcx+2]
        loop .cicloDiag
    
    mov rdx, rax    
    
	.fin:
		pop r12
        push r13
		pop rbp
		ret

;------------------------------------------------
