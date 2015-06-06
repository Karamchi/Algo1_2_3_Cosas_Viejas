#include <iostream>
#include "../aed2.h"
#include "test.h"


using namespace std;


void test_construccion(ostream&)
{
    Lista<Nat> l;
    ASEGURAR(l, "<>");      // Nueva lista vacia

    Lista<Nat> l2(l);
    ASEGURAR(l2, "<>");     // Nueva lista vacia por copia

    l.AgregarAtras(1);      // l2 no debe cambiar
    ASEGURAR(l2,"<>");

    l2.AgregarAtras(3);     // l no debe cambiar
    ASEGURAR(l,"<1>");

    ASEGURAR(l2,"<3>");
    l2 = l;                 // test asignacion
    ASEGURAR(l2,"<1>");

    l.AgregarAtras(3);      // l2 no debe cambiar
    ASEGURAR(l2,"<1>");

    l2.AgregarAtras(4);     // l no debe cambiar
    ASEGURAR(l,"<1,3>");
}

void test_es_vacia(ostream&)
{
    Lista<Nat> l;           // Nueva lista es vacia
    AFIRMAR(l.EsVacia());

    l.AgregarAdelante(1);   // Ahora debe ser no vacia
    NEGAR(l.EsVacia());

    l.Fin();                // Ahora vuelve a ser vacia
    AFIRMAR(l.EsVacia());
}

void test_longitud(ostream&)
{
    Lista<Nat> l;           // Longitud de nueva lista: 0
    AFIRMAR(l.Longitud() == 0);

    l.AgregarAtras(2);      // Se incrementa en 1 (caso vacia)
    AFIRMAR(l.Longitud() == 1);

    l.AgregarAtras(4);      // Se incrementa en 1 (caso no vacia)
    AFIRMAR(l.Longitud() == 2);

    l.Fin();                // Se decrementa en 1
    AFIRMAR(l.Longitud() == 1);
}

void test_primero(ostream&)
{
    Lista<Nat> l;
    l.AgregarAtras(1);      // Debe tener el 1 primero
    ASEGURAR(l.Primero(),"1");

    l.AgregarAtras(2);      // Mantiene el primero anterior
    ASEGURAR(l.Primero(),"1");

    l.Fin();                // Ahora el primero es "2"
    ASEGURAR(l.Primero(),"2");

    l.Primero() = 3;        // Cambia el primero: Ahora es "3"
    ASEGURAR(l.Primero(),"3");
}

void test_ultimo(ostream&)
{
    Lista<Nat> l;
    l.AgregarAtras(3);      // Debe tener el "3" ultimo
    ASEGURAR(l.Ultimo(),"3");

    l.AgregarAtras(4);      // Ahora el ultimo es "4"
    ASEGURAR(l.Ultimo(),"4");

    l.Fin();                // Ahora el ultimo es "4"
    ASEGURAR(l.Ultimo(),"4");

    l.Ultimo() = 10;        // Cambia el ultimo a "10"
    ASEGURAR(l.Ultimo(),"10");
}

void test_agregar_adelante(ostream&)
{
    Lista<Nat> l;
    ASEGURAR(l, "<>");      // Nueva lista vacia

    l.AgregarAdelante(1);   // Agrega por delante a lista vacia
    ASEGURAR(l,"<1>");

    l.AgregarAdelante(2);   // Agrega por delante a una lista no vacía
    ASEGURAR(l,"<2,1>");
}

void test_agregar_atras(ostream&)
{
    Lista<Nat> l;
    ASEGURAR(l, "<>");      // Nueva lista vacía

    l.AgregarAtras(3);   // Agrega por detras a lista vacia
    ASEGURAR(l,"<3>");

    l.AgregarAtras(4);   // Agrega por detras a una lista no vacía
    ASEGURAR(l,"<3,4>");
}

void test_iesimo(ostream&)
{
    Lista<Nat> l;

    l.AgregarAtras(2);
    l.AgregarAtras(8);
    l.AgregarAtras(1);
    l.AgregarAtras(9);
    ASEGURAR(l,"<2,8,1,9>");

    ASEGURAR(l[0],"2");
    ASEGURAR(l[1],"8");
    ASEGURAR(l[2],"1");
    ASEGURAR(l[3],"9");

    Lista<Nat>::Iterador it = l.CrearIt();
    it.Avanzar();
    it.EliminarSiguiente(); // Elimina, ahora l[1] = "1"
    ASEGURAR(l[0],"2");
    ASEGURAR(l[1],"1");
    ASEGURAR(l[2],"9");

    l[1] = 33;              // Cambia solamente l[1] (referencia).
    ASEGURAR(l[0],"2");
    ASEGURAR(l[1],"33");
    ASEGURAR(l[2],"9");
}

void test_fin(ostream&)
{
    Lista<Nat> l;

    l.AgregarAtras(2);
    l.AgregarAtras(8);
    ASEGURAR(l,"<2,8>");

    l.Fin();            // Fin de lista de longitud > 1
    ASEGURAR(l,"<8>");

    l.Fin();            // Fin de lista de longitud 1
    ASEGURAR(l,"<>");
}

void test_comienzo(ostream&)
{
    Lista<Nat> l;

    l.AgregarAtras(2);
    l.AgregarAtras(8);      // Fabrica una lista
    ASEGURAR(l,"<2,8>");

    l.Comienzo();            // Comienzo de lista de longitud > 1
    ASEGURAR(l,"<2>");

    l.Comienzo();            // Comienzo de lista de longitud 1
    ASEGURAR(l,"<>");
}

/// TESTS CONST ITERADOR ///

void test_const_iterador_construccion(ostream&)
{
    Lista<Nat> l;
    l.AgregarAtras(1);
    l.AgregarAtras(3);
    l.AgregarAtras(5);
    l.AgregarAtras(7);
    ASEGURAR(l,"<1,3,5,7>");

    // Construccion y copia

    Lista<Nat>::const_Iterador cit1 = l.CrearIt(); // siguiente cit1: "1". Sin anterior
    Lista<Nat>::const_Iterador cit2 = l.CrearItUlt(); // anterior cit2: "7". Sin siguiente

    NEGAR(cit1.HayAnterior());
    NEGAR(cit2.HaySiguiente());
    AFIRMAR(cit2.HayAnterior());
    AFIRMAR(cit1.HaySiguiente());
    ASEGURAR(cit1.Siguiente(),"1");
    ASEGURAR(cit2.Anterior(), "7");

    Lista<Nat>::const_Iterador cit3(cit1);  // Crea otro iterador por copia
    NEGAR(cit3.HayAnterior());
    AFIRMAR(cit3.HaySiguiente());
    ASEGURAR(cit3.Siguiente(),"1");

    cit1.Avanzar();                         // Cambia el original y no  la copia
    NEGAR(cit3.HayAnterior());
    AFIRMAR(cit3.HaySiguiente());
    ASEGURAR(cit3.Siguiente(),"1");

    AFIRMAR(cit1 == cit1);
    AFIRMAR(l.CrearIt() == l.CrearIt());
	NEGAR(l.CrearIt() == l.CrearItUlt());
	NEGAR(l.CrearIt() == Lista<Nat>().CrearIt());
}

// Tambien testea HayAnterior / HaySiguiente / Anterior / Siguiente
void test_const_iterador_avanzar(ostream&)
{
    Lista<Nat> l, vacia;
    l.AgregarAtras(1);
    l.AgregarAtras(3);
    l.AgregarAtras(5);
    l.AgregarAtras(7);

    // Caso lista vacia
    Lista<Nat>::const_Iterador citv = vacia.CrearIt();
    NEGAR(citv.HayAnterior());
    NEGAR(citv.HaySiguiente());

    Lista<Nat>::const_Iterador cit = l.CrearIt();          // Nuevo iterador al comienzo
    NEGAR(cit.HayAnterior());
    AFIRMAR(cit.HaySiguiente());
    ASEGURAR(cit.Siguiente(),"1");

    l.AgregarAdelante(0);       // Cambia el primero: ahora el iter tiene anterior
    AFIRMAR(cit.HayAnterior());
    AFIRMAR(cit.HaySiguiente());
    ASEGURAR(cit.Siguiente(),"1");

    cit.Avanzar();              // Avanza uno y comprueba
    AFIRMAR(cit.HayAnterior());
    AFIRMAR(cit.HaySiguiente());
    ASEGURAR(cit.Siguiente(),"3");

    cit.Avanzar();
    cit.Avanzar();
    cit.Avanzar();              // Llega al final de la lista
    NEGAR(cit.HaySiguiente());
    AFIRMAR(cit.HayAnterior());
    ASEGURAR(cit.Anterior(),"7");

    l.AgregarAtras(9);  // Cambia el último de la lista, el anterior de iter cambia
    NEGAR(cit.HaySiguiente());
    AFIRMAR(cit.HayAnterior());
    ASEGURAR(cit.Anterior(),"9");
}

// Tambien testea HayAnterior / HaySiguiente / Anterior / Siguiente
void test_const_iterador_retroceder(ostream&)
{
    Lista<Nat> l, vacia;
    l.AgregarAtras(1);
    l.AgregarAtras(3);
    l.AgregarAtras(5);
    l.AgregarAtras(7);

    // Caso lista con elementos
    Lista<Nat>::const_Iterador cit = l.CrearItUlt();
    NEGAR(cit.HaySiguiente());
    AFIRMAR(cit.HayAnterior());
    ASEGURAR(cit.Anterior(),"7");

    l.AgregarAtras(9);          // Cambia el ultimo, cambia el anterior del iter
    NEGAR(cit.HaySiguiente());
    AFIRMAR(cit.HayAnterior());
    ASEGURAR(cit.Anterior(),"9");

    cit.Retroceder();           // Retrocede uno
    AFIRMAR(cit.HaySiguiente());
    AFIRMAR(cit.HayAnterior());
    ASEGURAR(cit.Anterior(),"7");

    cit.Retroceder();
    cit.Retroceder();
    cit.Retroceder();
    cit.Retroceder();           // Llega al principio
    NEGAR(cit.HayAnterior());
    AFIRMAR(cit.HaySiguiente());
    ASEGURAR(cit.Siguiente(),"1");

    l.AgregarAdelante(0);       // El iter ahora tiene anterior y mismo siguiente
    AFIRMAR(cit.HaySiguiente());
    AFIRMAR(cit.HayAnterior());
    ASEGURAR(cit.Anterior(),"0");
    ASEGURAR(cit.Siguiente(),"1");
}

/// TESTS ITERADOR ///

void test_iterador_construccion(ostream&)
{
    Lista<Nat> l;
    l.AgregarAtras(1);
    l.AgregarAtras(3);
    l.AgregarAtras(5);
    l.AgregarAtras(7);

    ASEGURAR(l,"<1,3,5,7>");

    // Construccion y copia

    Lista<Nat>::Iterador it1(l.CrearIt()); // siguiente it1: "1". Sin anterior
    Lista<Nat>::Iterador it2(l.CrearItUlt()); // anterior it2: "7". Sin siguiente

    ASEGURAR(it1.Siguiente(),"1");
    ASEGURAR(it2.Anterior(), "7");
    NEGAR(it1.HayAnterior());
    NEGAR(it2.HaySiguiente());

    Lista<Nat>::Iterador it3(it1);  // Crea otro iterador por copia
    NEGAR(it3.HayAnterior());
    AFIRMAR(it3.HaySiguiente());
    ASEGURAR(it3.Siguiente(),"1");

    it1.Avanzar();                         // Cambia el original y no  la copia
    NEGAR(it3.HayAnterior());
    AFIRMAR(it3.HaySiguiente());
    ASEGURAR(it3.Siguiente(),"1");
}

// Tambien testea HayAnterior / HaySiguiente / Anterior / Siguiente
void test_iterador_avanzar(ostream&)
{
    Lista<Nat> l, vacia;
    l.AgregarAtras(1);
    l.AgregarAtras(3);
    l.AgregarAtras(5);
    l.AgregarAtras(7);

    // Caso lista vacia
    Lista<Nat>::Iterador it = vacia.CrearIt();
    NEGAR(it.HayAnterior());
    NEGAR(it.HaySiguiente());

    it = l.CrearIt();          // Nuevo iterador al comienzo
    NEGAR(it.HayAnterior());
    AFIRMAR(it.HaySiguiente());
    ASEGURAR(it.Siguiente(),"1");

    l.AgregarAdelante(0);       // Cambia el primero: ahora el iter tiene anterior
    AFIRMAR(it.HayAnterior());
    AFIRMAR(it.HaySiguiente());
    ASEGURAR(it.Siguiente(),"1");

    it.Avanzar();              // Avanza uno y comprueba
    AFIRMAR(it.HayAnterior());
    AFIRMAR(it.HaySiguiente());
    ASEGURAR(it.Siguiente(),"3");

    it.Avanzar();
    it.Avanzar();
    it.Avanzar();              // Llega al final de la lista
    NEGAR(it.HaySiguiente());
    AFIRMAR(it.HayAnterior());
    ASEGURAR(it.Anterior(),"7");

    l.AgregarAtras(9);  // Cambia el último de la lista, el anterior de iter cambia
    NEGAR(it.HaySiguiente());
    AFIRMAR(it.HayAnterior());
    ASEGURAR(it.Anterior(),"9");
}

// Tambien testea HayAnterior / HaySiguiente / Anterior / Siguiente
void test_iterador_retroceder(ostream&)
{
    Lista<Nat> l, vacia;
    l.AgregarAtras(1);
    l.AgregarAtras(3);
    l.AgregarAtras(5);
    l.AgregarAtras(7);

    // Caso lista vacia
    Lista<Nat>::Iterador it = vacia.CrearIt();
    NEGAR(it.HayAnterior());
    NEGAR(it.HaySiguiente());

    // Caso lista con elementos
    it = l.CrearItUlt();
    NEGAR(it.HaySiguiente());
    AFIRMAR(it.HayAnterior());
    ASEGURAR(it.Anterior(),"7");

    l.AgregarAtras(9);          // Cambia el ultimo, cambia el anterior del iter
    NEGAR(it.HaySiguiente());
    AFIRMAR(it.HayAnterior());
    ASEGURAR(it.Anterior(),"9");

    it.Retroceder();           // Retrocede uno
    AFIRMAR(it.HaySiguiente());
    AFIRMAR(it.HayAnterior());
    ASEGURAR(it.Anterior(),"7");

    it.Retroceder();
    it.Retroceder();
    it.Retroceder();
    it.Retroceder();           // Llega al principio
    NEGAR(it.HayAnterior());
    AFIRMAR(it.HaySiguiente());
    ASEGURAR(it.Siguiente(),"1");

    l.AgregarAdelante(0);       // El iter ahora tiene anterior y mismo siguiente
    AFIRMAR(it.HaySiguiente());
    AFIRMAR(it.HayAnterior());
    ASEGURAR(it.Anterior(),"0");
    ASEGURAR(it.Siguiente(),"1");
}

void test_iterador_agregar(ostream&)
{
    // Comienza: lista vacia
    Lista<Nat> l;
    Lista<Nat>::Iterador it = l.CrearIt();
    NEGAR(it.HayAnterior());
    NEGAR(it.HaySiguiente());

    // Agrega adelate, verifica iter y lista
    it.AgregarComoSiguiente(1);
    NEGAR(it.HayAnterior());
    AFIRMAR(it.HaySiguiente());
    ASEGURAR(it.Siguiente(),"1");
    ASEGURAR(l.Primero(),"1");
    ASEGURAR(l.Ultimo(),"1");

    // Agrega Atras, verifica iter y lista
    it.AgregarComoAnterior(9);
    AFIRMAR(it.HayAnterior());
    AFIRMAR(it.HaySiguiente());
    ASEGURAR(it.Anterior(),"9");
    ASEGURAR(it.Siguiente(),"1");
    ASEGURAR(l.Primero(),"9");
    ASEGURAR(l.Ultimo(),"1");

    // Agrega en lista al principio y al fin, iter debe quedar igual
    l.AgregarAtras(2);
    l.AgregarAdelante(8);
    AFIRMAR(it.HayAnterior());
    AFIRMAR(it.HaySiguiente());
    ASEGURAR(it.Anterior(),"9");
    ASEGURAR(it.Siguiente(),"1");
    ASEGURAR(l.Primero(),"8");
    ASEGURAR(l.Ultimo(),"2");
}

void test_iterador_eliminar(ostream&)
{
    // Lista con algunos elementos
    Lista<Nat> l;
    l.AgregarAtras(2);
    l.AgregarAtras(3);
    l.AgregarAtras(5);
    l.AgregarAtras(7);

    Lista<Nat>::Iterador it = l.CrearIt();
    it.Avanzar();
    it.Avanzar(); // Siguiente: 5
    AFIRMAR(it.HayAnterior());
    AFIRMAR(it.HaySiguiente());
    ASEGURAR(it.Anterior(),"3");
    ASEGURAR(it.Siguiente(),"5");
    ASEGURAR(l,"<2,3,5,7>");

    it.EliminarSiguiente();
    AFIRMAR(it.HayAnterior());
    AFIRMAR(it.HaySiguiente());
    ASEGURAR(it.Anterior(),"3");
    ASEGURAR(it.Siguiente(),"7");
    ASEGURAR(l,"<2,3,7>");

    it.EliminarAnterior();
    AFIRMAR(it.HayAnterior());
    AFIRMAR(it.HaySiguiente());
    ASEGURAR(it.Anterior(),"2");
    ASEGURAR(it.Siguiente(),"7");
    ASEGURAR(l,"<2,7>");

    it.EliminarSiguiente();
    AFIRMAR(it.HayAnterior());
    NEGAR(it.HaySiguiente());
    ASEGURAR(it.Anterior(),"2");
    ASEGURAR(l,"<2>");

    it.EliminarAnterior();
    NEGAR(it.HayAnterior());
    NEGAR(it.HaySiguiente());
    ASEGURAR(l,"<>");
}

void test_igualdad(ostream&) {
  Lista<Nat> l;
  l.AgregarAtras(1);
  l.AgregarAtras(5);
  l.AgregarAtras(7);

  Lista<Nat> l2;
  l2.AgregarAtras(1);
  l2.AgregarAtras(5);
  l2.AgregarAtras(7);

  Lista<Nat> l3;
  l3.AgregarAtras(1);
  l3.AgregarAtras(5);
  l3.AgregarAtras(9);

  AFIRMAR(l == l);
  AFIRMAR(l == l2);
  NEGAR(l == l3);
}

int main()
{
    Tester *t = Tester::Instance();
    t->NuevoSet("Lista");
    t->UsarSet("Lista");

    // Lista<T>
    t->Declarar("Creacion",&test_construccion);
    t->Declarar("EsVacia",&test_es_vacia);
    t->Declarar("Longitud",&test_longitud);
    t->Declarar("Primero",&test_primero);
    t->Declarar("Ultimo",&test_ultimo);
    t->Declarar("AgregarAdelante",&test_agregar_adelante);
    t->Declarar("AgregarAtras",&test_agregar_atras);
    t->Declarar("Iesimo",&test_iesimo);
    t->Declarar("Fin",&test_fin);
    t->Declarar("Comienzo",&test_comienzo);

    // Lista<T>::const_Iterador
    t->Declarar("CIterCreacion",&test_const_iterador_construccion);
    t->Declarar("CIterAvanzar",&test_const_iterador_avanzar);
    t->Declarar("CIterRetrocederr",&test_const_iterador_retroceder);

    // Lista<T>::Iterador
    t->Declarar("IterCreacion",&test_iterador_construccion);
    t->Declarar("IterAvanzar",&test_iterador_avanzar);
    t->Declarar("IterRetroceder",&test_iterador_retroceder);
    t->Declarar("IterAgregar",&test_iterador_agregar);
    t->Declarar("IterEliminar",&test_iterador_eliminar);

    t->Ejecutar("Lista");
    return 0;
}
