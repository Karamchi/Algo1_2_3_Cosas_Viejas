global borrarUltimo
global agregarPrimero
extern free
extern malloc

%define NULL 0
%define offset_primer_nodo 0
%define offset_prox 8				; NO ESTA EMPAQUETADO!
%define offset_dato 0				; NO ESTA EMPAQUETADO!
%define TAM_NODO 16				; NO ESTA EMPAQUETADO!

section .data

section .text

borrarUltimo:
	
	;supongo que la lista tiene algun elemento al menos
	;extern void borrarUltimo(struct lista *unaLista);
	; unaLista -> rdi
	
	; armamos stack frame
	push rbp
	mov rbp, rsp
	push rbx
	push r12
; 	no modifico r13 r14 r15, la pila ya esta alineada

	; rbx va a ser mi temp
	; r12 va a ser la direccion del puntero q tiene la direccion del nodo
	; que borre. Es decir, la lista tenia un solo elemento voy a tener 
	; la direccion de lista->primero (NO el contenido, la direccion)
	; si la lista tenia al menos dos elementos voy a tener una direccion
	; que representa la direccion de algo del estilo lista->prox
	; (NO el contenido, la direccion)
	
	mov rbx,  [ rdi +offset_primer_nodo]; cargo el primer nodo
	cmp rbx, NULL
	je fin
	lea r12, [rdi +offset_primer_nodo]	; rdi apunta a la direccion donde esta el puntero 
										; a poner en NULL
.cicloAvanzar:	
	cmp qword [rbx+offset_prox], NULL 	; comparo si donde estoy, el prox es NULL
	je .encontreUltimo					; salto a borrar si encontre el ultimo
	lea r12, [rbx+offset_prox]			; cargo en r12 lo que explique antes
	mov rbx, [r12]			; avanzo
	
	jmp .cicloAvanzar
			
	.encontreUltimo:
	; tengo en rbx el nodo a borrar
	; tengo que llamar a malloc
	
	mov rdi, rbx 	; cargo el primer parametro
	call free
	
	; Corrijo lo que apunta rdi
	mov qword [r12], NULL

fin:
	; desarmo
; 	no modifico r13 r14 r15, la pila ya esta alineada
	pop r12
	pop rbx
	pop rbp
	ret
	
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	
;void agregarPrimero(struct lista* unaLista, int unInt){
agregarPrimero:
	; unaLista -> rdi
	; unInt -> esi
	
	; armamos stack frame
	push rbp
	mov rbp, rsp
	push rbx
	push r12
	push r13
; 	no modifico r15 r14
	sub rsp,8						  ; alieno la pila
	mov r12, [rdi+offset_primer_nodo] ; r12  antiguo primer nodo
	
	mov r13, rdi					  ; r13 direccion de la lista
	
	mov ebx, esi				      ;  guardo en ebx el valor q ingresar
	; creo nodo nuevo
	mov rdi, TAM_NODO
	call malloc
	
	; cargo el nodo
	mov [rax + offset_dato], ebx	; cargo el dato
	mov [rax + offset_prox], r12	; cargo el proximo
	
	; arreglo la lista
	mov [r13+ offset_primer_nodo], rax

	; desarmo
	add rsp, 8
; 	no modifico r15 r14
	pop r13
	pop r12
	pop rbx
	pop rbp
	ret
