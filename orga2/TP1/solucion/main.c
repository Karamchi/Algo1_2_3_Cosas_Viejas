#include <assert.h>
#include "lista.h"

void f (void* a) {} //unused parameter... qué molesto
void g (void* a,FILE* b){}
bool h (void* a,void* b){return true;}
jugador* i (jugador* a){
	jugador* copy=crear_jugador(a->nombre,a->pais,a->numero,a->altura);
	return copy;
}

void listavacia() {
	  FILE* archivo = fopen("hola.out","a");
	  lista* l = lista_crear();
	  assert(l->primero == NULL);
	  lista_imprimir_f(l, archivo, (tipo_funcion_imprimir)&g);
	  lista_borrar(l,(tipo_funcion_borrar)&f);
	  fclose(archivo);
}


void listade1(void) {
	  lista* l = lista_crear();
	  jugador* j = crear_jugador("Ginobili", "Argentina", 5, 198);
	  nodo* n=nodo_crear(j);
	  //insertar_ordenado(l, (void*)Gino, (tipo_funcion_cmp)&menor_jugador);
	  insertar_ultimo(l, n);
	  lista_imprimir(l, "hola.out", (tipo_funcion_imprimir)&imprimir_jugador);
	  assert(((jugador*)l->primero->datos)->nombre == j->nombre);
	  lista_borrar(l,(tipo_funcion_borrar)&borrar_jugador);
}

void listademas(void) {
	  lista* l = lista_crear();
	  jugador* j1 = crear_jugador("Ginobili", "Argentina", 5, 198);
	  jugador* j2 = crear_jugador("Scola", "Argentina", 6, 190);
	  jugador* j3 = crear_jugador("Prigioni", "Argentina", 7, 190);
	  jugador* j4 = crear_jugador("Ginobili", "Argentina", 9, 199);
	  jugador* j5 = crear_jugador("Ginobili", "Argentina", 10, 202);

	  insertar_ordenado(l, (void*)j1, (tipo_funcion_cmp)&h); //j1
	  insertar_ordenado(l, (void*)j2, (tipo_funcion_cmp)&h); //j2->j1 (estoy usando h, que me da que es menor)
	  insertar_ordenado(l, (void*)j3, (tipo_funcion_cmp)&menor_jugador); //j3->j2->j1
	  insertar_ordenado(l, (void*)j4, (tipo_funcion_cmp)&menor_jugador); //j4->j3->j2->j1
	  insertar_ordenado(l, (void*)j5, (tipo_funcion_cmp)&menor_jugador); //j4->j5->j3->j2->j1

	  assert(((jugador*)l->primero->datos)->altura == j4->altura); 

	  lista_imprimir(l,"hola.out", (tipo_funcion_imprimir)&imprimir_jugador);
	  lista_borrar(l,(tipo_funcion_borrar)&borrar_jugador);
}

void selvacia() {
	  FILE* archivo = fopen("hola.out","a");
	  lista* l = lista_crear();
	  seleccion* s=crear_seleccion("Andorra",1,l);
	  assert(s->jugadores->primero == NULL);
	  assert(s->alturaPromedio == 1);
	  imprimir_seleccion(s, archivo);
	  borrar_seleccion(s);
	  fclose(archivo);
}

void selllena() {
	  FILE* archivo = fopen("hola.out","a");
	  lista* l = lista_crear();
	  jugador* j1 = crear_jugador("Ginobili", "Argentina", 5, 198);
	  jugador* j2 = crear_jugador("Scola", "Argentina", 6, 197);
	  jugador* j3 = crear_jugador("Prigioni", "Argentina", 7, 198);
	  jugador* j4 = crear_jugador("Ginobili", "Argentina", 9, 199);
	  jugador* j5 = crear_jugador("Ginobili", "Argentina", 10, 199);

	  insertar_ordenado(l, (void*)j1, (tipo_funcion_cmp)&menor_jugador);//j1
	  insertar_ordenado(l, (void*)j2, (tipo_funcion_cmp)&menor_jugador);//j1->j2
	  insertar_ordenado(l, (void*)j3, (tipo_funcion_cmp)&menor_jugador);//j1->j3->j2
	  insertar_ordenado(l, (void*)j4, (tipo_funcion_cmp)&menor_jugador);//j1->j4->j3->j2
	  insertar_ordenado(l, (void*)j5, (tipo_funcion_cmp)&menor_jugador);//j1->j5->j4->j3->j2, si son iguales se agrega antes

	  seleccion* s=crear_seleccion("Uruguay",altura_promedio(l),l);
	  assert(((jugador*)s->jugadores->primero->datos)->altura== 198);
	  imprimir_seleccion(s, archivo);
	  borrar_seleccion(s);
	  fclose(archivo);
}

void listadesels() {
	  lista* l = lista_crear();
	  jugador* j1 = crear_jugador("Ginobili", "Argentina", 5, 198);
	  jugador* j2 = crear_jugador("Scola", "Argentina", 6, 198);
	  jugador* j3 = crear_jugador("Prigioni", "Argentina", 7, 198);
	  jugador* j4 = crear_jugador("Ginobili", "Argentina", 9, 199);
	  jugador* j5 = crear_jugador("Ginobili", "Argentina", 10, 199);

	  insertar_ordenado(l, (void*)j1, (tipo_funcion_cmp)&menor_jugador);
	  insertar_ordenado(l, (void*)j2, (tipo_funcion_cmp)&menor_jugador);
	  insertar_ordenado(l, (void*)j3, (tipo_funcion_cmp)&menor_jugador);
	  insertar_ordenado(l, (void*)j4, (tipo_funcion_cmp)&menor_jugador);
	  insertar_ordenado(l, (void*)j5, (tipo_funcion_cmp)&menor_jugador);

	  seleccion* s=crear_seleccion("Uruguay",altura_promedio(l),l);
	  lista* l2 = lista_crear();
	  seleccion* s2=crear_seleccion("Andorra",0,l2);
	  lista* partido=lista_crear();
	  insertar_ordenado(partido, (void*)s, (tipo_funcion_cmp)&menor_seleccion);
	  insertar_ordenado(partido, (void*)s2, (tipo_funcion_cmp)&menor_seleccion);

	  assert(((seleccion*)partido->primero->datos)->jugadores->primero== NULL);
	  assert(((seleccion*)partido->primero->sig->datos)->alturaPromedio==(992/5.0));

	  lista_imprimir(partido, "hola.out",(tipo_funcion_imprimir)&imprimir_seleccion);
	  lista_borrar(partido,(tipo_funcion_borrar)&borrar_seleccion);
}

void ordenar() {
	  lista* l = lista_crear();
	  jugador* j1 = crear_jugador("Ginobili", "Argentina", 5, 198);
	  nodo* n1 = nodo_crear(j1);
	  jugador* j2 = crear_jugador("Scola", "Argentina", 6, 198);
	  nodo* n2 = nodo_crear(j2);
	  jugador* j3 = crear_jugador("Prigioni", "Argentina", 7, 198);
	  nodo* n3 = nodo_crear(j3);
	  jugador* j4 = crear_jugador("Ginobili", "Argentina", 9, 199);
	  nodo* n4 = nodo_crear(j4);
	  jugador* j5 = crear_jugador("Ginobili", "Argentina", 10, 199);
	  nodo* n5 = nodo_crear(j5);

	  insertar_ultimo(l, n1);

	  lista* lord=ordenar_lista_jugadores(l);
	  lista_imprimir(lord, "hola.out",(tipo_funcion_imprimir)&imprimir_jugador);
	  assert(((jugador*)lord->primero->datos)->altura==j1->altura);
	  lista_borrar(lord,(tipo_funcion_borrar)&borrar_jugador);

	  insertar_ultimo(l, n2);
	  insertar_ultimo(l, n3);
	  insertar_ultimo(l, n4);
	  insertar_ultimo(l, n5);

	  lista* lord2=ordenar_lista_jugadores(l);

	  assert(((jugador*)lord2->primero->datos)->altura==j1->altura);

	  lista_imprimir(lord2, "hola.out",(tipo_funcion_imprimir)&imprimir_jugador);

	  lista_borrar(lord2,(tipo_funcion_borrar)&borrar_jugador);
	  lista_borrar(l,(tipo_funcion_borrar)&borrar_jugador);
}

void map() {
	  lista* l = lista_crear();
	  jugador* j1 = crear_jugador("Ginobili", "Argentina", 5, 198);
	  jugador* j2 = crear_jugador("Scola", "Argentina", 6, 198);
	  jugador* j3 = crear_jugador("Prigioni", "Argentina", 7, 198);
	  jugador* j4 = crear_jugador("Ginobili", "Argentina", 9, 199);
	  jugador* j5 = crear_jugador("Ginobili", "Argentina", 10, 199);

	  insertar_ordenado(l, (void*)j1, (tipo_funcion_cmp)&menor_jugador);
	  lista* lmap=mapear(l, (tipo_funcion_mapear)&i);
	  assert(((jugador*)lmap->primero->datos)->altura==j1->altura);
	  lista_imprimir(lmap, "hola.out",(tipo_funcion_imprimir)&imprimir_jugador);
	  lista_borrar(lmap,(tipo_funcion_borrar)&borrar_jugador);

	  insertar_ordenado(l, (void*)j2, (tipo_funcion_cmp)&menor_jugador);
	  insertar_ordenado(l, (void*)j3, (tipo_funcion_cmp)&menor_jugador);
	  insertar_ordenado(l, (void*)j4, (tipo_funcion_cmp)&menor_jugador);
	  insertar_ordenado(l, (void*)j5, (tipo_funcion_cmp)&menor_jugador);

	  lista* lmap2=mapear(l, (tipo_funcion_mapear)&normalizar_jugador);
	  lista_imprimir(lmap2, "hola.out",(tipo_funcion_imprimir)&imprimir_jugador);

	  jugador* n1 = normalizar_jugador(j1);

	  assert(((jugador*)lmap2->primero->datos)->altura==n1->altura);

	  borrar_jugador(n1);
	  lista_borrar(lmap2,(tipo_funcion_borrar)&borrar_jugador);
	  lista_borrar(l,(tipo_funcion_borrar)&borrar_jugador);
}

void filtrar() {
	  lista* l = lista_crear();
	  jugador* j1 = crear_jugador("Ginobili", "Argentina", 5, 198);
	  jugador* j2 = crear_jugador("Scola", "Antartida", 6, 198);
	  jugador* j3 = crear_jugador("Prigioni", "Argentina", 7, 198);
	  nodo* n3 = nodo_crear(j3);
	  jugador* j4 = crear_jugador("Ginobili", "Argentina", 9, 199);
	  jugador* j5 = crear_jugador("Ginobili", "Antartida", 10, 199);

	  insertar_ultimo(l, n3);
	  insertar_ordenado(l, (void*)j1, (tipo_funcion_cmp)&menor_jugador);
	  insertar_ordenado(l, (void*)j2, (tipo_funcion_cmp)&menor_jugador);
	  insertar_ordenado(l, (void*)j4, (tipo_funcion_cmp)&menor_jugador);
	  insertar_ordenado(l, (void*)j5, (tipo_funcion_cmp)&menor_jugador);

	  lista* lfil=filtrar_jugadores(l, (tipo_funcion_cmp)&menor_jugador,n3);
	  lista_imprimir(lfil, "hola.out",(tipo_funcion_imprimir)&imprimir_jugador);
	  assert(((jugador*)lfil->primero->sig->sig->datos)->altura==j4->altura);
	  lista_borrar(lfil,(tipo_funcion_borrar)&borrar_jugador);

	  lista* lfil2=filtrar_jugadores(l, (tipo_funcion_cmp)&pais_jugador,n3);
	  lista_imprimir(lfil2, "hola.out",(tipo_funcion_imprimir)&imprimir_jugador);
	  assert(((jugador*)lfil2->primero->sig->sig->datos)->altura==j3->altura);
	  lista_borrar(lfil2,(tipo_funcion_borrar)&borrar_jugador);

	  lista_borrar(l,(tipo_funcion_borrar)&borrar_jugador);
}

void generar() {
	  lista* l = lista_crear();
	  jugador* j1 = crear_jugador("Ginobili", "Argentina", 5, 198);
	  jugador* j2 = crear_jugador("Scola", "Transnistria", 6, 198);
	  jugador* j3 = crear_jugador("Prigioni", "Argentina", 7, 198);
	  jugador* j4 = crear_jugador("Ginobili", "Argentina", 9, 199);
	  jugador* j5 = crear_jugador("Ginobili", "Transnistria", 10, 199);

	  insertar_ordenado(l, (void*)j1, (tipo_funcion_cmp)&menor_jugador);
	  insertar_ordenado(l, (void*)j2, (tipo_funcion_cmp)&menor_jugador);
	  insertar_ordenado(l, (void*)j3, (tipo_funcion_cmp)&menor_jugador);
	  insertar_ordenado(l, (void*)j4, (tipo_funcion_cmp)&menor_jugador);
	  insertar_ordenado(l, (void*)j5, (tipo_funcion_cmp)&menor_jugador);

	  lista* gen=generar_selecciones(l);
	  lista_imprimir(gen, "hola.out",(tipo_funcion_imprimir)&imprimir_seleccion);

	  assert(((seleccion*)gen->primero->sig->datos)->alturaPromedio==6);
								//Los dos Transnistrios son de 6 pies
	  assert(((jugador*)((seleccion*)gen->primero->datos)->jugadores->primero->datos)->altura==6); 
								//El primero de argentina es Gino (6 pies)

	  lista_borrar(gen,(tipo_funcion_borrar)&borrar_seleccion);
	  lista_borrar(l,(tipo_funcion_borrar)&borrar_jugador);
}

int main(void) {
	remove("hola.out");
	listavacia();
	listade1();
	listademas();
	selvacia();
	selllena();
	listadesels();
	ordenar();
	map();
	filtrar();
	generar();
	
    return 0;
} 
