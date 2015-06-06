
#include <iostream>
#include "../aed2.h"
#include "test.h"

using namespace std;

#define forn(i,n)       for(Nat i = 0; i < (n); ++i)

void testCreacion(ostream& os) {
    Arreglo<Nat> a;
    Arreglo<Nat> b(19);
}

void testDefinir(ostream& os) {
    Arreglo<Nat> a(10);
    forn(i,10) NEGAR(a.Definido(i));
    forn(i,10) a.Definir(i, i);
    forn(i,10) AFIRMAR(a.Definido(i));
    forn(i,10) ASEGURAR(a[i], i);
    forn(i,10) a[i] = i+1;
    forn(i,10) DESASEGURAR(a[i], i);
}

void testBorrar(ostream& os) {
    Arreglo<Nat> a(10);
    forn(i,10) a.Definir(i, i);
    forn(i,10) AFIRMAR(a.Definido(i));
    forn(i,5) a.Borrar(2*i);
    forn(i,5) NEGAR(a.Definido(2*i));
    forn(i,5) AFIRMAR(a.Definido(2*i+1));
}

void testCopiaAsignacion(ostream& os) {
    Arreglo<Nat> a(10);
    forn(i,10) a.Definir(i, i);
    Arreglo<Nat> ca = a;
    forn(i,10) AFIRMAR(ca.Definido(i));
    forn(i,10) ASEGURAR(ca[i], i);
    ca.Borrar(0);
    DESASEGURAR(ca, a);
    Arreglo<Nat> b;
    b = ca;
    ASEGURAR(b, ca);
    ASEGURAR(b.Tamanho(), ca.Tamanho());
    Arreglo<Nat> c;
    ca = c;
    ASEGURAR(c.Tamanho(), ca.Tamanho());
    ASEGURAR(ca.Tamanho(), 0);
}

void testRedim(ostream& os) {
    Arreglo<Nat> a;
    a.Redimensionar(10);
    ASEGURAR(a.Tamanho(), 10);
    forn(i,10) NEGAR(a.Definido(i));
    forn(i,10) a.Definir(i, i);
    a.Redimensionar(20);
    forn(i,10) AFIRMAR(a.Definido(i));
    forn(i,10) ASEGURAR(a[i], i);
    forn(i,10) NEGAR(a.Definido(i+10));
    a.Redimensionar(5);
    ASEGURAR(a.Tamanho(), 5);
    forn(i,5) AFIRMAR(a.Definido(i));
    forn(i,5) ASEGURAR(a[i], i);
    a.Redimensionar(10);
    forn(i,5) AFIRMAR(a.Definido(i));
    forn(i,5) NEGAR(a.Definido(i+5));
}

void testMoverSwap(ostream& os) {
    Arreglo<Nat> a(10);
    forn(i,10) a.Definir(i,i);
    Arreglo<Nat> b(10);
    forn(i,10) b.Definir(i,9-i);
    a.Mover(0, b, 0);
    ASEGURAR(a[0], 9);
    NEGAR(b.Definido(0));
    a.Swap(0, b, 0);
    ASEGURAR(b[0], 9);
    NEGAR(a.Definido(0));
}

int main() {

    Tester::Instance()->NuevoSet("Arreglo");
    Tester::Instance()->UsarSet("Arreglo");
    Tester::Instance()->Declarar("Creacion", &testCreacion, 3);
    Tester::Instance()->Declarar("Definir", &testDefinir);
    Tester::Instance()->Declarar("Borrar", &testBorrar);
    Tester::Instance()->Declarar("Copia", &testCopiaAsignacion);
    Tester::Instance()->Declarar("Redimensionar", &testRedim);
    Tester::Instance()->Declarar("Mover", &testMoverSwap);

    Tester::Instance()->setVerborragia(0);
    Tester::Instance()->Ejecutar("Arreglo");


    return 0;
}
