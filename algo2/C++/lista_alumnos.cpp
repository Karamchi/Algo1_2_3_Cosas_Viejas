#include "lista_alumnos.h"

ListaAlumnos::ListaAlumnos()
  : len(0), prim(NULL), fin(NULL) {
}

ListaAlumnos::~ListaAlumnos() {
  // Completar

  // Esto soluciona el problema de memoria
  // para listas de longitud 1
  // if (prim != NULL) {
  //   delete prim;
  // }
}

int ListaAlumnos::longitud() const {
  return len;
}

void ListaAlumnos::agAdelante(const Alumno& elem) {
  // Completar/Arreglar
  Nodo* nuevo = new Nodo;
  nuevo->alumno = elem;
  nuevo->sig = NULL;

  len = 1;
  prim = nuevo;
  fin = nuevo;
}

// Completar
