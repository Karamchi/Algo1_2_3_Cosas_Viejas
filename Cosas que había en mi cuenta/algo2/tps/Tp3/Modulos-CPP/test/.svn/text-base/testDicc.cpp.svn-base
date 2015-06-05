/*
 * File:   test_dicc.cpp
 * Author: Fede
 *
 * Created on 14 de noviembre de 2010, 17:32
 */

#include <cstdlib>
#include "../aed2.h"
#include "test.h"

using namespace std;

void test_construccion(ostream&){
    Dicc<int,int> d;
    ASEGURAR(d,"{}");
    Dicc<int,int> d1(d);
    ASEGURAR(d1,"{}");
    d.DefinirRapido(3,4);
    ASEGURAR(d,"{3:4}");
    d.DefinirRapido(5,6);
    ASEGURAR(d,"{5:6,3:4}");
    d.Definir(8,9);
    ASEGURAR(d, "{8:9,5:6,3:4}");
    Dicc<int,int> d2(d);
    ASEGURAR(d2,"{8:9,5:6,3:4}");
    d2.Definir(8,77);
    ASEGURAR(d2,"{8:77,5:6,3:4}");
}

void test_significado(ostream&){
    Dicc<int,int> d;
    d.DefinirRapido(4,5);
    ASEGURAR(d.Significado(4),5);
    d.Definir(4,6);
    ASEGURAR(d.Significado(4),6);
}

void test_definido(ostream&){
    Dicc<int,float> d;
    NEGAR(d.Definido(4));
    d.DefinirRapido(4,5.6);
    AFIRMAR(d.Definido(4));
    d.Definir(4,7.8);
    AFIRMAR(d.Definido(4));
    d.Borrar(4);
    NEGAR(d.Definido(4));
}


void test_borrar(ostream&){
    Dicc<int,int> d;
    d.DefinirRapido(1,2);
    d.DefinirRapido(3,4);
    d.DefinirRapido(5,6);
    ASEGURAR(d.CantClaves(),3);
    d.Borrar(3);
    ASEGURAR(d.CantClaves(),2);
    d.Borrar(1);
    ASEGURAR(d.CantClaves(),1);
    d.Borrar(5);
    ASEGURAR(d.CantClaves(),0);


}

/*
 *
 */
int main(int argc, char** argv) {
    Tester& tester = *Tester::Instance();
    tester.NuevoSet("Dict",0);
    tester.UsarSet("Dict");
    tester.Declarar("construccion",&test_construccion,0);
    tester.Declarar("significado",&test_significado,0);
    tester.Declarar("definido",&test_definido,0);
    tester.Declarar("borrar",&test_borrar,0);
    tester.EjecutarTodos();

    return 0;
}

