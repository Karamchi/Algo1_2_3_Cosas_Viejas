#include "lista_alumnos.h"
#include "mini_test.h"

void lista_nueva_es_vacia() {
  ListaAlumnos l;
  ASSERT_EQ(l.longitud(), 0);
}

void a_la_lista_vacia_se_le_agrega_alumno() {
  ListaAlumnos l;

  Alumno a;
  a.LU = 78403;
  a.edad = 29;
  l.agAdelante(a);

  ASSERT_EQ(l.longitud(), 1);
}

int main() {
  RUN_TEST(lista_nueva_es_vacia);
  RUN_TEST(a_la_lista_vacia_se_le_agrega_alumno);

  return 0;
}
