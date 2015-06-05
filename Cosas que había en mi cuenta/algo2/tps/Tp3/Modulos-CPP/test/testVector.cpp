#include <iostream>
#include "../aed2.h"
#include "test.h"

using namespace aed2;
using namespace std;

#define forn(i,n)       for(Nat i = 0; i < (n); ++i)

void testLongitud (ostream& os){
    Vector<Nat> v0;

    v0.AgregarAtras(0);
    ASEGURAR(v0.Longitud(),1);
    forn(i,2) v0.AgregarAtras(1);

    ASEGURAR(v0.Longitud(),3);

    v0.AgregarAtras(1);
    ASEGURAR(v0.Longitud(),4);

    forn(i,4) v0.AgregarAtras(1);
    ASEGURAR(v0.Longitud(),8);

    forn(i,11) v0.AgregarAtras(2);
    ASEGURAR(v0.Longitud(),19);

    forn(i,9) v0.Eliminar(i);
    ASEGURAR(v0.Longitud(),10);

    forn(i, 5) {
         v0.Agregar(i,i);
         v0.Eliminar(i);
    }

    ASEGURAR(v0.Longitud(),10);
}

void testAgregarAtras (ostream& os){

    Vector<Nat> v0;

    forn(i,11) v0.AgregarAtras(i);
    forn(i,5) v0.Eliminar(0);
    forn(i,6) ASEGURAR(v0[i],i+5);

}

void testAgregar (ostream& os){
    Vector<Nat> v;


    forn(i,7) v.AgregarAtras(i);

    ASEGURAR(v, "<0,1,2,3,4,5,6>");

    v.Agregar(7,11);

    ASEGURAR(v, "<0,1,2,3,4,5,6,11>");

    v[0] = 12;
    v[1] = 13;
    v[3] = 14;

    ASEGURAR(v,"<12,13,2,14,4,5,6,11>");

}

void testCrear (ostream& os) {
    Vector<Nat> v0;
    Vector<Nat> v1;

    AFIRMAR(v0.EsVacio());
    AFIRMAR(v1.EsVacio());

    forn(i,7) v0.AgregarAtras(i);
    forn(i,7) v0.Comienzo();

    AFIRMAR(v0.EsVacio());

    forn(i,16) v0.AgregarAtras(i);
    forn(i,16) v0.Comienzo();

    AFIRMAR(v0.EsVacio());

    forn(i,124) v0.AgregarAtras(i);
    forn(i,124) v0.Comienzo();

    AFIRMAR(v0.EsVacio());

}


void testOtrasOp (ostream& os) {
    Vector<Nat> v0;
	Vector<Nat> v1;

    forn(i,10) v0.AgregarAtras(i);
    forn(i,6) v1.AgregarAtras(i);

    v0.TirarUltimos(4);
    v0.AgregarAtras(1);
    v0.TomarPrimeros(6);
    ASEGURAR(v0, v1);

    v0.TomarPrimeros(5);
    v1.TomarPrimeros(5);
    ASEGURAR(v0,v1);

    forn(i,10) v1.Agregar(i,i);
    v1.TomarPrimeros(5);
    ASEGURAR(v0,v1);

    v0.Comienzo();
    v1.TomarPrimeros(4);

    ASEGURAR(v1,v0);

}

int main() {
    Tester::Instance()->NuevoSet("Vector");
    Tester::Instance()->UsarSet("Vector");
    Tester::Instance()->Declarar("Creacion", &testCrear);
    Tester::Instance()->Declarar("Longitud", &testLongitud);
    Tester::Instance()->Declarar("AgregarAtras", &testAgregarAtras);
    Tester::Instance()->Declarar("Agregar", &testAgregar);
    Tester::Instance()->Declarar("Otras Operaciones", &testOtrasOp);
	Tester::Instance()->setVerborragia(3);

    Tester::Instance()->Ejecutar("Vector");
    return 0;
}
