#include <cstdio>
#include <cstdlib>
#include <iostream>

typedef struct __attribute__((packed)) nodo_p {
    nodo_p* proximo;
    nodo_p* anterior;
    int red;
} nodo_p;

typedef struct __attribute__((packed)) nodo_t {
    nodo_t* proximo;
    nodo_t* anterior;
    int pozo1;
    int pozo2;
} nodo_t;

typedef struct __attribute__((packed)) lista_t {
    void* primero;
    void* ultimo;
    int cardinal;
} lista_t;

typedef struct __attribute__((packed)) tuberia_t {
    int costos;
    int fuente;
} tuberia_t;

typedef struct __attribute__((packed)) red_t {
    tuberia_t* disponibles;
    nodo_p* nodo;
} red_t;

lista_t* lista_crear();
void lista_borrar(lista_t* lista);
void eliminar_nodo(lista_t* lista, nodo_p* nodo);
void lista_agregar_conexion(lista_t* lista, int x, int y);
nodo_p* lista_agregar_pozo(lista_t* lista, int p);
void merge(red_t* conexiones, int red, int minpozo, int pozos);
int auxiliar(red_t* conexiones, lista_t* camino, lista_t* realizadas, int pozos, int costo);
