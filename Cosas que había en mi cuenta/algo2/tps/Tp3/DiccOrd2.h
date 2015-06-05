//¿podemos agregarle un devolver iesimo a diccord?
#include <iostream>
#include "Modulos-CPP/aed2/TiposBasicos.h"
#include "Modulos-CPP/aed2/Arreglo.h"

using namespace std;
using namespace aed2;

template<class K,class S>
struct DiccAcot {

public:

    struct Elem;

    class Iterador;


    DiccAcot();
    DiccAcot(const Nat n);

    Iterador Definir(const K& clave, const S& significado);
    Iterador DefinirRapido(const K& clave, const S&);

    bool Definido(const K& clave) const;
    const S& const_Significado(const K& clave) const;
    S& Significado(const K& clave);
    void Borrar(const K& clave);
    Nat CantClaves() const;
    Nat MaxClaves() const;
    bool operator == (DiccAcot<K,S>) const;
    Iterador CrearIt();

    class Iterador
    {
      public:

        Iterador();

        Iterador(const typename DiccAcot<K, S>::Iterador& otro);

        Iterador& operator = (const typename DiccAcot<K, S>::Iterador& otro);

        bool operator == (const typename DiccAcot<K,S>::Iterador&) const;

        bool HaySiguiente() const;
        const K& SiguienteClave() const;
        S& SiguienteSignificado();
        Elem Siguiente();
        void Avanzar();

      private:

        Arreglo<Elem> *it_elementos;
        Nat _i;
        Nat _long;

        Iterador(DiccAcot<K,S>* d);

        friend typename DiccAcot<K,S>::Iterador DiccAcot<K,S>::CrearIt();
        Elem operator=(const typename DiccAcot<K,S>::Elem otro);
    };

    struct Elem{
      public:

        K clave;
        S significado;

        Elem(K c, S s) : clave(c), significado(s) {}

        friend std::ostream& operator<<(std::ostream& os, const DiccAcot<K,S>::Elem& e) {
          return os << e.clave << ":" << e.significado;
        }

        typename DiccAcot<K,S>::Elem& operator=(const typename DiccAcot<K,S>::Elem);
      private:
    };

 private:

    Arreglo<Elem> _elementos;
    Nat _longitud;
    Nat _lReal;

};


template<class K,class S>
DiccAcot<K,S>::DiccAcot() {
    _elementos=Arreglo<Elem>();
    _longitud=0;
    _lReal=0;
}

template<class K,class S>
DiccAcot<K,S>::DiccAcot(Nat n) {
    _elementos=Arreglo<Elem>(n);
    _longitud=n;
    _lReal=0;
}
template<class K,class S>
typename DiccAcot<K, S>::Iterador DiccAcot<K,S>::Definir(const K& c, const S& s) {
    #ifdef DEBUG
    assert(_longitud>_lReal);
    #endif
    //auxK y auxS los usamos para ir trasladando los elementos del array
    K auxK = c;
    S auxS = s;
    //auxK2 y auxS2 los usamos para el swap
    K auxK2;
    S auxS2;
    Nat i;
    for (i=0;i<CantClaves();i++){
        if ((_elementos[i].clave)>c){
            auxK2 = _elementos[i].clave;
            auxS2 =_elementos[i].significado;
            _elementos[i]=Elem(auxK, auxS);
            auxK=auxK2;
            auxS=auxS2;
        }
    }
    _elementos.Definir(i, Elem(auxK, auxS));
    _lReal++;
    return CrearIt();
}
template<class K,class S>
typename DiccAcot<K, S>::Iterador DiccAcot<K,S>::DefinirRapido(const K& c, const S& s) {
    #ifdef DEBUG
    assert(_longitud>_lReal);
    #endif
    Elem a=Elem(c,s);
    _elementos.Definir(_lReal, a);
    _lReal++;
    return CrearIt();
}

template<class K,class S>
bool DiccAcot<K,S>::Definido(const K& c) const {
    Nat i=(_lReal-1)/2;
    Nat mx=(_lReal-1);
    Nat mn=0;
	if (_elementos[0].clave == c)	{return true;}
	while (mx > mn+1) {
        if (_elementos[i].clave==c) {
            return true;
        } else if (_elementos[i].clave<c) {
            mn=i;
            i=(i+mx)/2;
        } else {
            mx=i;
            i=(i+mn)/2;
        }
	} if (_elementos[mx].clave==c || _elementos[mn].clave==c) {
        return true;
    } return false;
}

template<class K,class S>
S& DiccAcot<K,S>::Significado(const K& c) {
    #ifdef DEBUG
    assert(Definido(c));
    #endif
    Nat i=_lReal/2;
    Nat mx=_lReal;
    Nat mn=0;
    while (_elementos[i].clave!=c) {
        if ((_elementos[i]).clave<c) {
            mn=i;
            i=(i+mx)/2;
        } if ((_elementos[i]).clave>c) {
            mx=i;
            i=(i+mn)/2;
        }
    }
    return (_elementos[i]).significado;
}

template<class K,class S>
const S& DiccAcot<K,S>::const_Significado(const K& c) const{
    #ifdef DEBUG
    assert(Definido(c));
    #endif
    Nat i=_lReal/2;
    Nat mx=_lReal;
    Nat mn=0;
    while (_elementos[i].clave!=c) {
        if ((_elementos[i]).clave<c) {
            mn=i;
            i=(i+mx)/2;
        } if ((_elementos[i]).clave>c) {
            mx=i;
            i=(i+mn)/2;
        }
    }
    return (_elementos[i]).significado;
}

template<class K,class S>
void DiccAcot<K,S>::Borrar(const K& clave){
    #ifdef DEBUG
    assert(Definido(clave));
    #endif
    bool encontrado = false;
    for(Nat i=0;i < _lReal-1;i++){
        if (_elementos[i].clave== clave || encontrado){
            _elementos[i] = _elementos[i+1];
            encontrado = true;
        }
    } _lReal = _lReal-1;
}

template<class K,class S>
Nat DiccAcot<K,S>::CantClaves() const{

return _lReal;

}

template<class K,class S>
Nat DiccAcot<K,S>::MaxClaves() const{

return _longitud;

}

template<class K,class S>
bool DiccAcot<K,S>::operator == (const DiccAcot<K,S> d2) const{

    bool res = true;
    if(_lReal != d2._lReal)                         {res = false;}
    else{
        for (Nat i=0;i < _lReal;i++){
            if(_elementos[i] == d2._elementos[i])   {res = false;}
        }
    }
    return res;
}

template<class K,class S>
DiccAcot<K,S>::Iterador::Iterador(DiccAcot<K,S>* d)
 : it_elementos(&d->_elementos), _i(0), _long(d->_lReal)
{}

template<class K,class S>
DiccAcot<K,S>::Iterador::Iterador(const typename DiccAcot<K, S>::Iterador& otro)
  : it_elementos(otro.it_elementos), _i(otro._i), _long(otro._long)
{}


/*template<class K,class S>
DiccAcot<K,S>::Iterador& operator = (const typename DiccAcot<K, S>::Iterador& otro){

it_elementos = otro.it_elementos;
_i = otro._i;
_long = otro._long;

}

template<class K,class S>
bool operator == (const typename DiccAcot<K,S>::Iterador otro) const{

return it_elementos == otro.it_elementos && _i == otro._i && _long == otro._long;

}
*/          // ESTAS COSAS NO SON NECESARIAS PERO TARIA BUENO TENERLAS

template<class K, class S>
typename DiccAcot<K,S>::Iterador DiccAcot<K,S>::CrearIt()
{
  return Iterador(this);
}

template<class K,class S>
bool DiccAcot<K,S>::Iterador::HaySiguiente() const{
    return _i<_long;

}

template<class K,class S>
const K& DiccAcot<K,S>::Iterador::SiguienteClave() const{

    return (*it_elementos)[_i].clave;

}

template<class K,class S>
S& DiccAcot<K,S>::Iterador::SiguienteSignificado(){

    return (*it_elementos)[_i].significado;

}

template<class K,class S>
typename DiccAcot<K,S>::Elem DiccAcot<K,S>::Iterador::Siguiente(){

    return (*it_elementos)[_i];

}

template<class K,class S>
void DiccAcot<K,S>::Iterador::Avanzar(){
    _i++;
}

template<class K,class S>
typename DiccAcot<K,S>::Elem& DiccAcot<K,S>::Elem::operator=(const typename  DiccAcot<K,S>::Elem otro){
    clave=otro.clave;
    significado=otro.significado;
    return *this;
}
