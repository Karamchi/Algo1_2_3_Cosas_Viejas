
#include <iostream>
#include "../aed2.h"
#include "test.h"


using namespace std;

void testCreacion(ostream& os) {
	ConjAcotado ca(0, 10);		// Crea un conjunto vacio en el rango [0, 10]
	ASEGURAR(ca, "{}");

	ConjAcotado cb(ca);			// Copia un conjunto vacio en el rango [0, 10]
	ASEGURAR(cb, "{}");

	ConjAcotado cc(10, 30);		// Crea un conjunto vacio en el rango [10, 30]
	ASEGURAR(cc, "{}");
}

void testAgregar(ostream& os) {
	ConjAcotado ca(0, 10);
	ca.Agregar(5);				// Agrega un elemento nuevo en el rango [0, 10]
	ASEGURAR(ca, "{5}");

	ConjAcotado cb(ca);
	cb.Agregar(7);				// Agregar un elemento nuevo a la copia no cambia el original
	ASEGURAR(ca, "{5}");

	ConjAcotado cc(10, 30);
	cc.Agregar(11);
	cc.Agregar(11);				// Agrega un elemento repetido en el rango [10, 30]
	ASEGURAR(cc, "{11}");
}

void testEliminar(ostream& os) {
	ConjAcotado ca(0, 10);
	ca.Agregar(5);
	ca.Eliminar(5);				// Elimina uno que pertence
	ASEGURAR(ca, "{}");

	ConjAcotado cb(ca);
	cb.Agregar(7);
	cb.Eliminar(5);				// Elimina uno que no pertenece
	ASEGURAR(cb, "{7}");

	ConjAcotado cc(10, 30);
	cc.Agregar(11);
	cc.Eliminar(5);				// Elimina por debajo del rango
	cc.Eliminar(35);			// Elimina por encima del rango
	ASEGURAR(cc, "{11}");
}

void testInfimo(ostream& os) {
	ConjAcotado ca(0, 10);
	ASEGURAR(ca.Infimo(), 0);	// Pide el Infimo en el rango [0, 10]

	ConjAcotado cb(ca);
	ASEGURAR(ca.Infimo(), 0);	// Pide el Infimo de una copia

	ConjAcotado cc(10, 30);
	ASEGURAR(cc.Infimo(), 10);	// Pide el Infimo en el rango [10, 30]
}

void testSupremo(ostream& os) {
	ConjAcotado ca(0, 10);
	ASEGURAR(ca.Supremo(), 10);	// Pide el Supremo en el rango [0, 10]

	ConjAcotado cb(ca);
	ASEGURAR(ca.Supremo(), 10);	// Pide el Supremo de una copia

	ConjAcotado cc(10, 30);
	ASEGURAR(cc.Supremo(), 30);	// Pide el Supremo en el rango [10, 30]
}

void testEsVacio(ostream& os) {
	ConjAcotado ca(0, 10);
	AFIRMAR(ca.EsVacio());		// Pregunta por vacio a un conjunto vacio

	ConjAcotado cb(ca);
	AFIRMAR(cb.EsVacio());		// Pregunta por vacio en una copia

	ConjAcotado cc(10, 30);
	cc.Agregar(11);
	NEGAR(cc.EsVacio());		// Pregunta por vacio a un conjunto con un elemento
}

void testPertenece(ostream& os) {
	ConjAcotado ca(0, 10);
	ca.Agregar(5);
	AFIRMAR(ca.Pertenece(5));	// Verifica que un elemento pertenece
	NEGAR(ca.Pertenece(7));		// Verifica que un elemento no pertenece
	NEGAR(ca.Pertenece(11));	// Verifica que un elemento fuera de rango no pertenece

	ConjAcotado cb(ca);
	cb.Agregar(7);
	AFIRMAR(cb.Pertenece(5));	// Verifica que un elemento pertenece
	AFIRMAR(cb.Pertenece(7));	// Verifica que un elemento pertenece
	NEGAR(cb.Pertenece(11));	// Verifica que un elemento fuera de rango no pertenece

	ConjAcotado cc(10, 30);
	cc.Agregar(11);
	NEGAR(cc.Pertenece(5));		// Verifica que un elemento fuera de rango no pertenece
	NEGAR(cc.Pertenece(7));		// Verifica que un elemento fuera de rango no pertenece
	AFIRMAR(cc.Pertenece(11));	// Verifica que un elemento pertenece
}

void testCardinal(ostream& os) {
	ConjAcotado ca(0, 10);
	ca.Agregar(5);
	ASEGURAR(ca.Cardinal(), 1);	// Pide el cardinal de un conjunto con un elemento

	ConjAcotado cb(ca);
	cb.Agregar(7);
	ASEGURAR(cb.Cardinal(), 2);	// Pide el cardinal de un conjunto con dos elementos

	ConjAcotado cc(10, 30);
	ASEGURAR(cc.Cardinal(), 0); // Pide el cardinal de un conjunto vacio
}

void testIterar(ostream& os) {
	ConjAcotado ca(0, 10);
	ca.Agregar(5);
	ca.Agregar(7);
	ConjAcotado::Iterador it = ca.CrearIt();

	NEGAR(it.HayAnterior());
	AFIRMAR(it.HaySiguiente());
	Nat primero = it.Siguiente();
	it.Avanzar();

	AFIRMAR(it.HayAnterior());
	AFIRMAR(it.HaySiguiente());
	Nat segundo = it.Siguiente();
	ASEGURAR(it.Anterior(), primero);
	it.Avanzar();

	NEGAR(it.HaySiguiente());
	AFIRMAR(it.HayAnterior());
	ASEGURAR(it.Anterior(), segundo);
	it.Retroceder();

	it.EliminarSiguiente();
	NEGAR(it.HaySiguiente());
	it.EliminarAnterior();
	NEGAR(it.HayAnterior());
}

void testIterarConst(ostream& os) {
	ConjAcotado ca(0, 10);
	ca.Agregar(5);
	ca.Agregar(7);
	const ConjAcotado& cb(ca);
	ConjAcotado::const_Iterador it = cb.CrearIt();

	NEGAR(it.HayAnterior());
	AFIRMAR(it.HaySiguiente());
	Nat primero = it.Siguiente();
	it.Avanzar();

	AFIRMAR(it.HayAnterior());
	AFIRMAR(it.HaySiguiente());
	Nat segundo = it.Siguiente();
	ASEGURAR(it.Anterior(), primero);
	it.Avanzar();

	NEGAR(it.HaySiguiente());
	AFIRMAR(it.HayAnterior());
	ASEGURAR(it.Anterior(), segundo);
	it.Retroceder();

	AFIRMAR(it.HayAnterior());
	AFIRMAR(it.HaySiguiente());
	ASEGURAR(it.Anterior(), primero);
	ASEGURAR(it.Siguiente(), segundo);
}


int main() {

    Tester::Instance()->NuevoSet("ConjuntoAcotado");
    Tester::Instance()->UsarSet("ConjuntoAcotado");

    Tester::Instance()->Declarar("Creacion", &testCreacion);
    Tester::Instance()->Declarar("Agregar", &testAgregar);
    Tester::Instance()->Declarar("Eliminar", &testEliminar);
    Tester::Instance()->Declarar("Infimo", &testInfimo);
    Tester::Instance()->Declarar("Supremo", &testSupremo);
    Tester::Instance()->Declarar("EsVacio", &testEsVacio);
    Tester::Instance()->Declarar("Pertence", &testPertenece);
    Tester::Instance()->Declarar("Cardinal", &testCardinal);
    Tester::Instance()->Declarar("Iterar", &testIterar);
    Tester::Instance()->Declarar("IterarConst", &testIterarConst);

    Tester::Instance()->setVerborragia(0);
    Tester::Instance()->Ejecutar("ConjuntoAcotado");

    return 0;
}
