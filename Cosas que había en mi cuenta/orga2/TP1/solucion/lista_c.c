#include "lista.h"


// Completar las funciones en C


lista *generar_selecciones( lista *l ){
	lista* res=lista_crear();
	nodo* n = l->primero;
	while (n!=NULL) {
		jugador* j = (jugador *) n->datos;
//Chequeo si está (lo haría en un auxiliar pero no sé si vale)
		bool esta=false;
		nodo* n2 = res->primero;
		while (n2!=NULL && esta==false) {
			seleccion* p = (seleccion *) n2->datos;
			if (string_iguales(p->pais,j->pais)) { //en realidad esto tampoco sé si vale, pero dado que prohibieron strcmp...
				esta=true;
			} n=n->sig;
		} 
//Chequeado ha sido
		if (!esta) {
			lista* jugs=filtrar_jugadores(l, (tipo_funcion_cmp)&pais_jugador, n);
			lista* jugs2=ordenar_lista_jugadores(jugs);
			lista_borrar(jugs,(tipo_funcion_borrar)&borrar_jugador);
			lista* jugs3=mapear(jugs2, (tipo_funcion_mapear)&normalizar_jugador);
			double d=altura_promedio(jugs3);
			seleccion* s=crear_seleccion(j->pais, d, jugs3);
			lista_borrar(jugs2, (tipo_funcion_borrar)&borrar_jugador);
			insertar_ordenado(res,s,(tipo_funcion_cmp)&menor_seleccion);
		} n=n->sig;
	} 
	return res;
}

// Funciones ya implementadas en C 

lista *filtrar_jugadores (lista *l, tipo_funcion_cmp f, nodo *cmp){
	lista *res = lista_crear();
	nodo *n = l->primero;
    while(n != NULL){
		if (f (n->datos, cmp->datos)){
			jugador *j = (jugador *) n->datos;
			nodo *p = nodo_crear ( (void *) crear_jugador (j->nombre, j->pais, j->numero, j->altura) );
			insertar_ultimo (res, p);
		}
		n = n->sig;
	}
	return res;
}

void insertar_ultimo (lista *l, nodo *nuevo){
	nodo *ultimo = l->ultimo;
	if (ultimo == NULL){
		l->primero = nuevo;
	}
	else{
		ultimo->sig = nuevo;
	}
	nuevo->ant = l->ultimo;
	l->ultimo = nuevo;
}

