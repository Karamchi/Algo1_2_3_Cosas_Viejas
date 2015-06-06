section .data
	msg: DB 'en 10 me voy...'
	largo EQU $ - msg
	num: DB '9' ; en cuánto me voy
	enter: DB 10 


global _start
section .text
_start:
	add byte[num],1
loop:
	sub byte [num],1

	mov rax, 4
	mov rbx, 1 
	mov rcx, msg ; escribo mensaje
	mov rdx, largo ; largo del mensaje
	int 0x80

	mov rax, 4
	mov rbx, 1
	mov rcx, num
	mov rdx, 1 ; es un byte
	int 0x80

	mov rax, 4
	mov rbx, 1
	mov rcx, enter
	mov rdx, 1 ; es un byte
	int 0x80

	cmp byte[num], '0'
	jne loop ; salta y jujuy
	mov rax, 1 ; terminar
	mov rbx, 0 ; todo bien
	int 0x80
