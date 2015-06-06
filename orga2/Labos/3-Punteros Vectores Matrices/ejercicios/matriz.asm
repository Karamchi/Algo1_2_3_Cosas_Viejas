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
	; RDI = matriz
	; SI = n
	; RDX = vector
	
	xor rcx, rcx
	mov cx, si						; RCX = iteraciones = columnas
	mov rsi, rcx

	.ciclo:	
		mov r8w, [rdi]				; buscamos los elementos de la diagonal	
		mov [rdx], r8w				; guardamos el elemento
	
		lea rdi, [rdi + 2*rsi + 2]  ; me muevo hasta siguiente elemento de diagonal
		lea rdx, [rdx+2]			; me muevo un lugar en el vector
		loop .ciclo

	.fin:	
		ret

;------------------------------------------------
