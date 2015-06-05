global nodo_crear
global lista_crear
global lista_borrar
global lista_imprimir
global lista_imprimir_f
global crear_jugador
global menor_jugador
global normalizar_jugador
global pais_jugador
global borrar_jugador
global imprimir_jugador
global crear_seleccion
global menor_seleccion
global primer_jugador
global borrar_seleccion
global imprimir_seleccion
global insertar_ordenado
global mapear
global ordenar_lista_jugadores
global altura_promedio
global string_iguales

extern filtrar_jugadores
extern insertar_ultimo
extern fprintf
extern malloc
extern free
extern fopen
extern fclose


; SE RECOMIENDA COMPLETAR LOS DEFINES CON LOS VALORES CORRECTOS
%define NULL 0
%define TRUE 1
%define FALSE 0

%define NODO_SIZE      24 
%define LISTA_SIZE     16 
%define JUGADOR_SIZE   21 
%define SELECCION_SIZE 24 

%define OFFSET_DATOS 0
%define OFFSET_SIG   8 
%define OFFSET_ANT   16 

%define OFFSET_PRIMERO 0
%define OFFSET_ULTIMO  8 

%define OFFSET_NOMBRE_J 0
%define OFFSET_PAIS_J   8 
%define OFFSET_NUMERO_J 16 
%define OFFSET_ALTURA_J 17 

%define OFFSET_PAIS_S      0
%define OFFSET_ALTURA_S    8 
%define OFFSET_JUGADORES_S 16 


section .rodata


section .data
vacia: DB '<vacia>',10,0
strjug: DB '%s %s %u %u' ,10,0
strsel: DB '%s %.2f',10,0
mira: DB 0,0,0,0,0,0,0,5
rulo: DB 5,0,0,0,0,0,0,0
teniarazondk: DQ 5

section .text

; FUNCIONES OBLIGATORIAS. PUEDEN CREAR LAS FUNCIONES AUXILIARES QUE CREAN CONVENIENTES

nodo_crear:

	push rbp
	mov rbp, rsp
	push r12
	sub rsp, 8
	
	mov r12, rdi
	mov rdi, NODO_SIZE
	call malloc

	mov [rax+OFFSET_DATOS], r12
	mov qword [rax+OFFSET_SIG], NULL
	mov qword [rax+OFFSET_ANT], NULL

	add rsp, 8
	pop r12	
	pop rbp
	ret


lista_crear:
	push rbp
	mov rbp, rsp

	mov rdi, LISTA_SIZE
	call malloc
	mov qword [rax+OFFSET_PRIMERO], NULL
	mov qword [rax+OFFSET_ULTIMO], NULL

	pop rbp
	ret 

lista_borrar:
		push rbp
		mov rbp, rsp
		push rbx
		push r12
		push r13
		push r14 ; tienen que ser impares contando rbp

		mov rbx, [rdi+OFFSET_PRIMERO] ; primero
		mov r13, rdi ; puntero a la lista para borrarla al final
 		mov r14, rsi ; funcion que borra nodos
		cmp rbx, NULL ; caso lista vacia
		je .fin
	.ciclo:	
		mov r12, [rbx+OFFSET_SIG] ; en r12 guardo el siguiente para que al borrar no se vaya
		mov rdi, [rbx+OFFSET_DATOS]
		call r14 ; r14 solo borra los datos del nodo
		mov rdi, rbx
		call free ; ahi si debería haberse borrado el nodo
		mov rbx, r12
		cmp rbx, NULL ; chequeo si existe siguiente
		jne .ciclo
	.fin:
		mov rdi, r13 
		call free ; termino borrando el struct

		pop r14
		pop r13		
		pop r12
		pop rbx
		pop rbp
		ret

lista_imprimir:
	push rbp
	mov rbp, rsp
	push rbx
	push r12
	push r13		
	sub rsp, 8

	mov rbx, rdi ; lista
	mov r12, rsi ; nombre de archivo
	mov r13, rdx ; fn imprimir

	mov qword [rsp], "a" ;guardo una variable local que vale "a"
	
	mov rdi,r12
	mov rsi,rsp
	call fopen ; el inmundo pide puntero a "a"

	mov r12, rax ; guardo el archivo p cerrarlo
	
	mov rdi, rbx ; lista
	mov rsi, r12 ; nombre de archivo
	mov rdx, r13 ; función imprimir
	call lista_imprimir_f
	
	mov rdi, r12
	call fclose

	add rsp, 8
	pop r13
	pop r12
	pop rbx
	pop rbp
	ret		

lista_imprimir_f:

		push rbp
		mov rbp, rsp
		push rbx
		push r12
		push r13
		sub rsp, 8

		mov rbx,rdx ; 
		mov r13,rsi ;si no me lo pisa
		mov r12, [rdi+OFFSET_PRIMERO]
		cmp r12, NULL
		jne .ciclo;
		mov rdi, r13
		mov rsi, vacia ;caso lista vacia
		call fprintf 
		jmp .fin
		
	.ciclo:
		mov rdi, [r12+OFFSET_DATOS]
		mov rsi, r13
		call rbx ;imprimo datos
		mov r12, [r12+OFFSET_SIG]
		cmp r12, NULL
		jne .ciclo
	.fin:
		add rsp, 8
		pop r13
		pop r12
		pop rbx
		pop rbp
		ret

crear_jugador: 
	push rbp
	mov rbp, rsp
	push r12
	push r13
	push r14
	push r15

	mov r12,rdi
	mov r13,rsi
	mov r14,rdx
	mov r15,rcx
	
	mov rdi, r12
	call string_copiar
	mov r12, rax

	mov rdi, r13
	call string_copiar
	mov r13, rax

	mov rdi, JUGADOR_SIZE
	call malloc ; el jugador ya queda en rax

	mov [rax+OFFSET_NOMBRE_J], r12 ; copiar string
	mov [rax+OFFSET_PAIS_J], r13 ; recontracopiar string
	mov byte [rax+OFFSET_NUMERO_J], r14b ; esto es un char
	mov dword [rax+OFFSET_ALTURA_J], r15d ; esto es un int :D
	
	pop r15
	pop r14
	pop r13
	pop r12
	pop rbp
	ret

menor_jugador:
		push rbp
		mov rbp, rsp
		push rbx
		push r12
		push r13
		sub rsp, 8

		mov r12, rdi
		mov r13, rsi
		mov rdi, [r12+OFFSET_NOMBRE_J]
		mov rsi, [r13+OFFSET_NOMBRE_J]
		call string_comparar
		cmp rax, 0
		jne .finf
		mov r12d, [r12+OFFSET_ALTURA_J]
 		cmp r12d, [r13+OFFSET_ALTURA_J]
		jle .fint
		mov rax, FALSE
		jmp .fin
	.finf:
		cmp rax, 0
		jl .fint
		mov rax, FALSE
		jmp .fin
	.fint:	mov rax, TRUE
		;jmp .fin
	.fin:
		add rsp, 8
		pop r13
		pop r12
		pop rbx
		pop rbp
		ret

normalizar_jugador:
		push rbp
		mov rbp, rsp
		push rbx
		push r12
		push r13
		sub rsp, 8		

		call jugador_copiar; ya está en rdi

		mov rbx, [rax+OFFSET_NOMBRE_J]
		mov r12d, [rax+OFFSET_ALTURA_J]
		mov r13, rax
	
		mov rcx, -1

	.ciclo:
		inc rcx
		cmp byte [rbx+rcx],0
		je .fin
		cmp byte [rbx+rcx], 'a'
		jl .ciclo
		cmp byte [rbx+rcx], 'z'
		jg .ciclo
		sub byte [rbx+rcx], 32 ; pone char en mayúscula (solo si estaba en minúscula)
		jmp .ciclo
	.fin:

		mov rcx, 100
		xor rax, rax ;ponemos la altura en pies
		xor rdx, rdx
		mov eax, r12d ;dx no debería importar
		mul cx	
		mov cx, 3048
		div cx
		mov [r13+OFFSET_ALTURA_J], eax ; IT FUNKS!

		mov rax, r13

		add rsp, 8
		pop r13
		pop r12
		pop rbx
		pop rbp
		ret

pais_jugador:
	push rbp
	mov rbp, rsp

	mov rdi, [rdi+OFFSET_PAIS_J] ;pais de jug 1
	mov rsi, [rsi+OFFSET_PAIS_J] ;pais de jug 2
	call string_iguales
	
	pop rbp
	ret

borrar_jugador:
	push rbp
	mov rbp, rsp
	push rbx
	sub rsp, 8

	mov rbx, rdi
	mov rdi, [rbx+OFFSET_NOMBRE_J]
	call free
	mov rdi, [rbx+OFFSET_PAIS_J]
	call free ; free sabe borrar strings
	mov rdi, rbx
	call free ; eso borra toda la struct

	add rsp, 8
	pop rbx
	pop rbp
	ret

imprimir_jugador:
	push rbp
	mov rbp, rsp
	push r12
	sub rsp, 8

	mov r12, rdi
	mov rdi, rsi
	mov rsi, strjug
	mov rdx, [r12+OFFSET_NOMBRE_J]
	mov rcx, [r12+OFFSET_PAIS_J]
	xor r8, r8
	mov r8b, [r12+OFFSET_NUMERO_J]
	xor r9, r9
	mov r9d, [r12+OFFSET_ALTURA_J]

	call fprintf; (*archivo, "%s %s %s %d", "We", "are", "in", 2012)

	add rsp, 8
	pop r12
	pop rbp
	ret

crear_seleccion:
	push rbp
	mov rbp, rsp
	push rbx
	push r12
	push r13
	sub rsp, 8

	movq r12,xmm0 ;altura
	mov r13,rsi ;*lista

	call string_copiar ;en rdi ya tenía el *nombre
	mov rbx,rax

	mov rdi, SELECCION_SIZE
	call malloc ;ya dejo selección en rax

	mov [rax+OFFSET_PAIS_S], rbx
	mov [rax+OFFSET_ALTURA_S], r12
	mov [rax+OFFSET_JUGADORES_S], r13

	add rsp, 8
	pop r13	
	pop r12
	pop rbx
	pop rbp
	ret

menor_seleccion:
		push rbp
		mov rbp, rsp

		mov rdi, [rdi+OFFSET_PAIS_S]
		mov rsi, [rsi+OFFSET_PAIS_S]
		call string_comparar
		cmp rax, 0
		jl .fint

		mov rax, FALSE
		jmp .fin
	.fint:
		mov rax, TRUE
	.fin:
		pop rbp
		ret

primer_jugador:
		push rbp
		mov rbp, rsp	

		mov rdi, [rdi+OFFSET_JUGADORES_S]
		mov rdi, [rdi+OFFSET_PRIMERO]
		mov rdi, [rdi+OFFSET_DATOS]
		call jugador_copiar ;tiene que devolver una copia

		pop rbp
		ret


borrar_seleccion:
		push rbp
		mov rbp, rsp
		push rbx
		sub rsp, 8

		mov rbx, rdi
		mov rdi, [rbx+OFFSET_JUGADORES_S]
		mov rsi, borrar_jugador
		call lista_borrar
		mov rdi, [rbx+OFFSET_PAIS_S]
		call free
		mov rdi, rbx
		call free

		add rsp, 8
		pop rbx
		pop rbp
		ret


imprimir_seleccion:
	push rbp
	mov rbp, rsp
	push r12
	push r13

	mov r12, rdi ;seleccion*
	mov r13, rsi ;file*

	mov rdi, rsi
	mov rsi, strsel
	mov rdx, [r12+OFFSET_PAIS_S]
	movq xmm0, [r12+OFFSET_ALTURA_S] ;esto me hizo quedarme hasta las 5 de la mañana

	call fprintf

	mov rdi, [r12+OFFSET_JUGADORES_S]
	mov rsi, r13
	mov rdx, imprimir_jugador
	call lista_imprimir_f

	pop r13
	pop r12
	pop rbp	
	ret

insertar_ordenado:
		push rbp
		mov rbp, rsp
		push rbx
		push r12
		push r13
		push r14

		mov rbx, rdi ; lista*
		mov r12, rsi ; datos (void*)
		mov r13, rdx ; funcion de comparacion

		mov rdi, r12
		call nodo_crear ; ahi ta el nodo en rax
		mov r12, rax ; los datos los piso porque en realidad los sigo teniendo

		mov r14, [rbx+OFFSET_PRIMERO] ;nodo*
		cmp r14, NULL
		je .insertovacio
	.ciclo:
		mov rdi, [r12+OFFSET_DATOS]
		mov rsi, [r14+OFFSET_DATOS]
		call r13
		cmp rax, FALSE ;el de la lista < el que quiero agregar
		jne .insertonormal

		mov r14, [r14+OFFSET_SIG]
		cmp r14, NULL
		je .insertoultimo
		jmp .ciclo

	.insertovacio:
		mov [rbx+OFFSET_PRIMERO], r12
		mov [rbx+OFFSET_ULTIMO], r12
		jmp .fin

	.insertonormal:	;en r14 esta el que compare ultimo
		mov r8, [r14+OFFSET_ANT]
		cmp r8, NULL
		je .insertoprimero
		mov [r8+OFFSET_SIG],r12 ; a->ant->sig=nuevo
		mov [r12+OFFSET_ANT],r8 ; nuevo->ant=a->ant
		mov [r12+OFFSET_SIG],r14 ; nuevo->sig=a
		mov [r14+OFFSET_ANT],r12 ; a -> ant = nuevo
		jmp .fin
		
	.insertoprimero: ; me encantaría no repetir código, pero los movs no pueden ir antes del cmp
		mov [rbx+OFFSET_PRIMERO],r12
		mov [r12+OFFSET_SIG],r14 ; nuevo->sig=a
		mov [r14+OFFSET_ANT],r12 ; a -> ant = nuevo
		jmp .fin
		
	.insertoultimo:	
		mov rdi, rbx
		mov rsi, r12
		call insertar_ultimo

	.fin:
		pop r14
		pop r13
		pop r12
		pop rbx
		pop rbp
		ret

altura_promedio:
		push rbp
		mov rbp, rsp
		push rbx
		push r12

		mov rbx, [rdi+OFFSET_PRIMERO]
		xorps xmm0, xmm0 ; este se devuelve por xmm0
		xor rcx, rcx
	
	.ciclo:
		mov r12, [rbx+OFFSET_DATOS]
		xorps xmm1, xmm1 ; cv no toca la parte alta
		mov r12d, [r12+OFFSET_ALTURA_J]
		cvtsi2sd xmm1, r12d 
		addsd xmm0, xmm1 ;addsd=add para doubles
		inc ecx
		mov rbx, [rbx+OFFSET_SIG]
		cmp rbx, NULL ; doy por hecho que hay un primer jugador, si no da 0/0
		jne .ciclo

		xorps xmm1, xmm1 ; cv no toca la parte alta

		cvtsi2sd xmm1, ecx ;instruccion mágica que pasa de int a double
		divsd xmm0, xmm1 ;instrucción mágica que te evita hacer lío con el div

		pop r12
		pop rbx
		pop rbp
		ret

ordenar_lista_jugadores:
		push rbp
		mov rbp, rsp
		push rbx
		push r12

		mov rbx, rdi ;tengo en rbx la lista vieja
		call lista_crear
		mov r12, rax ;y en r12 la nueva
		mov rbx, [rbx+OFFSET_PRIMERO] ;en rbx voy recorriendo los elementos
	.ciclo:
		cmp rbx, NULL
		je .fin
		mov rdi, [rbx+OFFSET_DATOS]
		call jugador_copiar

		mov rdi, r12
		mov rsi, rax ; una copia
		mov rdx, menor_jugador 
		call insertar_ordenado ; (lista*, datos*, fn)

		mov rbx, [rbx+OFFSET_SIG]
		jmp .ciclo

	.fin:
		mov rax, r12
		pop r12
		pop rbx
		pop rbp
		ret

mapear:
		push rbp
		mov rbp, rsp
		push r12
		push r13
		push r14
		push r15

		mov r13, [rdi+OFFSET_PRIMERO] ;nodo viejo
		mov r12, rsi ;fn de mapeo
		call lista_crear
		mov r15, rax ;lista nueva

	.ciclo:
		cmp r13, NULL
		je .fin

		mov rdi, [r13+OFFSET_DATOS]
		call r12 ;fn de mapeo (const)
		mov rdi, rax
		call nodo_crear
		
		mov rdi, r15 ;lista nueva 
		mov rsi, rax ;nodo*
		call insertar_ultimo
		mov r15, rax
		mov r13, [r13+OFFSET_SIG]
		jmp .ciclo
	.fin:
		mov rax, r15
		pop r15
		pop r14
		pop r13
		pop r12
		pop rbp
		ret

string_iguales:
		push rbp
		mov rbp, rsp

		call string_comparar ;tiene los mismos rdi y rsi
		cmp rax, 0
		je .fint
		mov rax, 0
		jmp .fin
	.fint:	
		mov rax, 1	
	.fin:	
		pop rbp
		ret

string_comparar:
		push rbp
		mov rbp, rsp
		push r12
		sub rsp, 8

		mov rcx, 0

	.cmpstring:
		mov r12b, [rsi+rcx]
		cmp byte [rdi+rcx], r12b
		jl .finl ;que bueno que el caracter de finalización sea 0
		jg .fing
		cmp byte [rdi+rcx], 0
		je .fine
		inc rcx
		jmp .cmpstring
	.fine:
		mov rax, 0
		jmp .fin
	.finl:
		mov rax, -1
		jmp .fin
	.fing:
		mov rax, 1
	.fin:
		add rsp, 8
		pop r12
		pop rbp
		ret

string_copiar:
		push rbp
		mov rbp, rsp
		push rbx
		push r12

		mov rbx, rdi
		mov rcx, 0 
	.ciclo1:
		inc rcx 
		cmp byte [rbx+rcx],0
		jne .ciclo1

		inc rcx ; el 0 final tambien hay que copiarlo
		mov rdi,rcx
		call malloc
		mov rcx, 0

	.ciclo2:
		mov r12b, [rbx+rcx]
		mov [rax+rcx], r12b
		inc rcx		
		cmp byte [rbx+rcx],0
		jne .ciclo2

		mov byte [rax+rcx], 0

		pop r12
		pop rbx
		pop rbp
		ret

jugador_copiar:
	push rbp
	mov rbp,rsp
		
	mov r8, rdi

	mov rdi, [r8+OFFSET_NOMBRE_J]
	mov rsi, [r8+OFFSET_PAIS_J]
	mov dl, [r8+OFFSET_NUMERO_J]
	mov ecx, [r8+OFFSET_ALTURA_J]
	call crear_jugador

	pop rbp
	ret
