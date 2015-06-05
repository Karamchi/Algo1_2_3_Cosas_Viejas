#include <cstdlib>
#include "../aed2.h"
#include "test.h"
using namespace std;

void test_construccion(ostream&){
    Conj<int> d;
    ASEGURAR(d,"{}");
    Conj<int> d1(d);
    ASEGURAR(d1,"{}");
    d.AgregarRapido(3);
    ASEGURAR(d,"{3}");
    d.AgregarRapido(5);
    ASEGURAR(d,"{5,3}");
    d.Agregar(8);
    ASEGURAR(d, "{8,5,3}");
    Conj<int> d2(d);
    ASEGURAR(d2,"{8,5,3}");
}



void test_pertenece(ostream&){
    Conj<int> d;
    NEGAR(d.Pertenece(4));
    d.AgregarRapido(4);
    AFIRMAR(d.Pertenece(4));
    d.Agregar(4);
    AFIRMAR(d.Pertenece(4));
    d.Eliminar(4);
    NEGAR(d.Pertenece(4));
}


void test_eliminar(ostream&){
    Conj<int> d;
    d.AgregarRapido(1);
    d.AgregarRapido(3);
    d.AgregarRapido(5);
    ASEGURAR(d.Cardinal(),3);
    d.Eliminar(3);
    ASEGURAR(d.Cardinal(),2);
    d.Eliminar(1);
    ASEGURAR(d.Cardinal(),1);
    d.Eliminar(5);
    ASEGURAR(d.Cardinal(),0);


}

/*
 *
 */
int main(int argc, char** argv) {
    Tester& tester = *Tester::Instance();
    tester.NuevoSet("Conj",0);
    tester.UsarSet("Conj");
    tester.Declarar("construccion",&test_construccion,0);
    tester.Declarar("pertenece",&test_pertenece,0);
    tester.Declarar("eliminar",&test_eliminar,0);
    tester.EjecutarTodos();

    return 0;
}

