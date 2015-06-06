#include <stdio.h>      /* printf, scanf, NULL */
#include <stdlib.h>     /* malloc, free, rand */


struct nodo{
	int dato;
	struct nodo *prox;
};
struct lista{
	struct nodo *primero;
};

extern void borrarUltimo(struct lista *unaLista);
extern void agregarPrimero(struct lista* unaLista, int unInt);

struct lista * crearLista(){
	struct lista * unaLista = malloc( sizeof(struct lista));
	unaLista->primero = NULL;
}

void mostrarLista(struct lista *unaLista){
	printf("");
	struct nodo * unNodo = unaLista->primero;
	while(unNodo){
		printf("[%d] -> ", unNodo->dato);
		unNodo= unNodo->prox;
	}
	printf("-|\n");
}

void destruirLista(struct lista *unaLista){
	printf("");
	struct nodo * unNodo = unaLista->primero;
	struct nodo * temp;
	while(unNodo){
		temp =unNodo->prox;
		//borro cada nodo
		free(unNodo);
		unNodo= temp;
	}
	//borro la lista
	free(unaLista);
}

int main(){
	
	// creo la lista
	struct lista * lista1 = crearLista();
	
	// muestro la lista
	mostrarLista( lista1);
	
	//agrego elemtos
	agregarPrimero( lista1, 4);
	agregarPrimero( lista1, 3);
	agregarPrimero( lista1, 5);
	agregarPrimero( lista1, 7);
	
	// muestro a la lista
	mostrarLista( lista1 );
	
	// borro Ultimo
	borrarUltimo(lista1);
	borrarUltimo(lista1);
	borrarUltimo(lista1);
	borrarUltimo(lista1);
	
	borrarUltimo(lista1); // borra sobre una lista sin elementos
	
	// muestro a la lista
	mostrarLista( lista1 );
	
	// libero memoria de la lista
	destruirLista( lista1);
	
	return 0;
	
}
