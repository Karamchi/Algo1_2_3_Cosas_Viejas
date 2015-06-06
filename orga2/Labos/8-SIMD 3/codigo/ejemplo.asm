global shufps_ejemplo
global pshufd_ejemplo
global pshufb_ejemplo
global multiplicar_por_pi_asm

section .data
ALIGN 16
pi: DD 3.141592653, 3.141592653, 3.141592653, 3.141592653

data_ejemplo: DD 0xAAAAAAAA, 0xBBBBBBBB, 0xCCCCCCCC, 0xDDDDDDDD

data_ejemplo_pshufb:
                    DB 0x00, 0x01, 0x02, 0x03,
                    DB 0x04, 0x05, 0x06, 0x07,
                    DB 0xF0, 0xF1, 0xF2, 0xF3,
                    DB 0xF4, 0xF5, 0xF6, 0xF7

pshufb_mask:
            DB 0x0F, 0x0E, 0x0D, 0x0C,
            DB 0x0B, 0x0A, 0x09, 0x08,
            DB 0x07, 0x06, 0x05, 0x04,
            DB 0x03, 0x02, 0x01, 0x00

section .text

shufps_ejemplo:
    push rbp
    mov rbp, rsp


    pop rbp
    ret

pshufb_ejemplo:
    push rbp
    mov rbp, rsp

    movdqa xmm0, [data_ejemplo_pshufb]
    pshufb xmm0, [pshufb_mask]

    pop rbp
    ret

pshufd_ejemplo:
    push rbp
    mov rbp, rsp

    movdqa xmm0, [data_ejemplo]
    ; Tengo xmm0: [0xD,0xC,0xB,0xA]
    pshufd xmm1, xmm0, 0x88 ; 10 00 10 00
    ; Tengo xmm1: [0xC,0xA,0xC,0xA]
    pshufd xmm2, xmm0, 0x70; 01 11 00 00
    ; Tengo xmm2: [0xB, 0xD, 0xA, 0xA]
    pop rbp
    ret
%define elems rdi
%define n rsi
%define col rax

multiplicar_por_pi_asm:
    ;rdi: unsigned short *elems
    ;esi: int n
    push rbp
    mov rbp, rsp

    mov esi, esi
    sal n, 1

    movdqa xmm0, [pi]
    xor rax, rax
    pxor xmm15, xmm15
    .loop:
        movdqa xmm1, [elems + col]

        movdqa xmm2, xmm1
        punpcklwd xmm1, xmm15 ; En xmm1 está la parte baja
        punpckhwd xmm2, xmm15

        cvtdq2ps xmm1, xmm1
        cvtdq2ps xmm2, xmm2

        mulps xmm1, xmm0
        mulps xmm2, xmm0

        cvttps2dq xmm1, xmm1
        cvttps2dq xmm2, xmm2

        packusdw xmm1, xmm2

        movdqa [elems + col], xmm1
        add col, 16
        cmp col, n
        jl .loop


    pop rbp
    ret
