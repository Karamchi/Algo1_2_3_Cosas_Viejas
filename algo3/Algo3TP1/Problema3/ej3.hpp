#include <cstdio>
#include <cstdlib>
#include <iostream>

typedef struct __attribute__((packed)) nodo_t {
    nodo_t* proximo;
    int x:8;
    int y:8;
} nodo_t;

typedef struct __attribute__((packed)) lista_t {
    nodo_t* primero;
    nodo_t* ultimo;
} lista_t;

typedef struct __attribute__((packed)) casilla_t {
    bool ocupada:8;
    int amenazas:8;
}casilla_t;

//Las casillas libres son las que no tienen un caballo ni estan amenazadas
//Las ocupadas son las que tienen una ficha

typedef struct __attribute__((packed)) tablero_t{
    casilla_t* lugar;
    int lado:8;
    int ocupadas:8;
    int libres:8;
}tablero_t;

typedef struct __attribute__((packed)) t_final{
    bool ocupada:8;
    bool inicial:8;
}t_final;

tablero_t* crear_tablero(int lado);
lista_t* recorrer(tablero_t* tablero, int c_iniciales, t_final* tablero_final);
void agregar_ficha(tablero_t* tablero, int x, int y);
void eliminar_ficha(tablero_t* tablero, int x, int y);
lista_t* lista_crear();
void lista_borrar(lista_t* lista);
nodo_t* lista_agregar(lista_t* lista, int x, int y);
int auxiliar(tablero_t* tablero, nodo_t* actual, int* max, t_final* tablero_final);
void imprimir_estado(tablero_t* tablero);
