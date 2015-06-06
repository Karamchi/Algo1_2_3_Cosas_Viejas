	; unaLista -> rdi
	; unInt -> esi
	
borrarUltimo:
	push rbp
	mov rbp, rsp
	push rbx
	push r12

	mov rbx,  [ rdi +offset_primer_nodo]
	cmp rbx, NULL
	je fin
	lea r12, [rdi +offset_primer_nodo]
.cicloAvanzar:
	cmp qword [rbx+offset_prox], NULL
	je .encontreUltimo
	lea r12, [rbx+offset_prox]
	mov rbx, [r12]
	jmp .cicloAvanzar
.encontreUltimo:
	mov rdi, rbx
	call free
	mov qword [r12], NULL
fin:
	pop r12
	pop rbx
	pop rbp
	ret

agregarPrimero:
	push rbp
	mov rbp, rsp
	push rbx
	push r12
	push r13
	sub rsp,8
	mov r12, [rdi+offset_primer_nodo]
	mov r13, rdi
	mov ebx, esi
	mov rdi, TAM_NODO
	call malloc
	mov [rax + offset_dato], ebx
	mov [rax + offset_prox], r12
	mov [r13+ offset_primer_nodo], rax
	add rsp, 8
	pop r13
	pop r12
	pop rbx
	pop rbp
	ret
