#include "ej3.hpp"
#include <time.h>
#include <fstream>

using namespace std;

int main(){

    int pozos;
    int cantconexiones;
    int costo;
    
    cin >> pozos;
    cin >> cantconexiones;
    cin >> costo;
    
    red_t* conexiones = (red_t*)malloc(pozos*16);

    int j = 0;

    for(int i=0;i<pozos;i++){
        conexiones[i].disponibles = (tuberia_t*)malloc(pozos*8);
        while(j<pozos){
            conexiones[i].disponibles[j].costos = costo;
            conexiones[i].disponibles[j].fuente = i;
            j++;
        }
        conexiones[i].disponibles[i].costos = -1;
        j=0;
    }

    int p1;
    int p2;
    int costopozo;

    while(cantconexiones > 0){
        cin >> p1;
        cin >> p2;
        cin >> costopozo;

        p1--;
        p2--;

        conexiones[p1].disponibles[p2].costos = costopozo;
        conexiones[p2].disponibles[p1].costos = costopozo;

        cantconexiones--;
    }

	clock_t t;
	t = clock();

    lista_t* camino = lista_crear();
    nodo_p* link;

    for(j=0;j<pozos;j++){

        link = lista_agregar_pozo(camino, j);
        conexiones[j].nodo = link;
    }

    lista_t* realizadas = lista_crear();
    int solucion;

    solucion = auxiliar(conexiones, camino, realizadas, pozos, costo);

	ofstream tiempo;
	t = clock() - t;
	tiempo.open("Tiempo",ios::app);
	tiempo << cantconexiones << ' ' << pozos << ' ' << (long int)t << endl;

    cout << solucion << endl;
    cout << camino->cardinal << ' ';
    cout << realizadas->cardinal << endl;

    link = (nodo_p*)camino->primero;

    while(link != (nodo_p*)0){
        cout << link->red+1 << endl;
        link = link->proximo;
    }

    nodo_t* nodo = (nodo_t*)realizadas->primero;

    while(nodo != (nodo_t*)0){
        cout << nodo->pozo1+1 << ' ' << nodo->pozo2+1 << endl;
        nodo = nodo->proximo;
    }
}

//Esta funcion crea una lista vacia

lista_t* lista_crear(){

    lista_t* lista = (lista_t*) malloc(20);
    lista->primero = (void*)0;
    lista->ultimo = (void*)0;
    lista->cardinal = 0;

    return lista;
}

//Esta funcion borra una lista y todos los nodos contenidos en ella

void lista_borrar(lista_t* lista){

    nodo_t* nodo = (nodo_t*)lista->primero;
    nodo_t* prox;

    while(nodo!= (nodo_t*) 0){
        prox = nodo->proximo;
        free(nodo);
        nodo = prox;
    }

    free(lista);

    return;
}

//Esta funcion agrega un nodo a la lista con los atributos pasados por parametro

nodo_p* lista_agregar_pozo(lista_t* lista, int p){

    nodo_p* nodo = (nodo_p*) malloc(20);
    nodo->red = p;

    nodo->anterior = (nodo_p*)(lista->ultimo);
    nodo->proximo = (nodo_p*)0;
    
    if(lista->primero == (void*)0){
        lista->primero = (void*)nodo;
    }else{
        ((nodo_p*)(lista->ultimo))->proximo = nodo;
    }

    lista->ultimo = (void*)nodo;

    lista->cardinal++;

    return nodo;
}

void lista_agregar_conexion(lista_t* lista, int x, int y){

    nodo_t* nodo = (nodo_t*) malloc(24);
    nodo->pozo1 = x;
    nodo->pozo2 = y;

    nodo->proximo = (nodo_t*)0;
    nodo->anterior = (nodo_t*)(lista->ultimo);
    
    if(lista->primero == (void*)0){
        lista->primero = nodo;
    }else{
        ((nodo_t*)(lista->ultimo))->proximo = nodo;
    }

    lista->ultimo = (void*)nodo;

    lista->cardinal++;

    return;
}

void eliminar_nodo(lista_t* lista, nodo_p* nodo){
    
    if (nodo->proximo != (nodo_p*)0){
        nodo->proximo->anterior = nodo->anterior;
    }
    if (nodo->anterior != (nodo_p*)0){
        nodo->anterior->proximo = nodo->proximo;
    }
    if(lista->primero == (void*)nodo){
        lista->primero = (void*)nodo->proximo;
    }
    if(lista->ultimo == (void*)nodo){
        lista->ultimo = (void*)nodo->anterior;
    }
    free(nodo);

    lista->cardinal--;

    return;
}

void merge(red_t* conexiones, int red, int minpozo, int pozos){
    for(int i=0;i<pozos;i++){
        if((conexiones[minpozo].disponibles[i].costos)<=(conexiones[red].disponibles[i].costos)){
            conexiones[red].disponibles[i].costos = conexiones[minpozo].disponibles[i].costos;
            conexiones[red].disponibles[i].fuente = conexiones[minpozo].disponibles[i].fuente;
        }
    }
    return;
}

int auxiliar(red_t* conexiones, lista_t* camino, lista_t* realizadas, int pozos, int costo){

    nodo_p* nodo = (nodo_p*)camino->primero;
    tuberia_t* tuberia;
    int solucion = 0;
    int mincosto = costo;
    int minpozo;
    int pozo;
    int i = 0;
    
    while(nodo != (nodo_p*)0){
        tuberia = conexiones[nodo->red].disponibles;

        while(i<pozos){
            if((tuberia[i].costos >= 0) and (tuberia[i].costos < mincosto)){
                mincosto = tuberia[i].costos;
                pozo = tuberia[i].fuente;
                minpozo = i;
            }
            i++;
        }

        if(mincosto<costo){
            solucion = solucion + mincosto;
            merge(conexiones, nodo->red, minpozo, pozos);
            lista_agregar_conexion(realizadas, pozo, minpozo);
            eliminar_nodo(camino, conexiones[minpozo].nodo);
        }else{
            nodo = nodo->proximo;
            solucion = solucion + costo;   
        }

        mincosto = costo;
        i=0;
    }
    
    return solucion;
}

