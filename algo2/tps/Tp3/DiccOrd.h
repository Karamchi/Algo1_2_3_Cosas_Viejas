#include <iostream>
#include "Modulos-CPP/aed2/TiposBasicos.h"
#include "Modulos-CPP/aed2/Arreglo.h"

using namespace std;
using namespace aed2;

template<class K,class S>
struct DiccAcot {

public:

    struct Elem;
    struct const_Elem;

    class Iterador;
    class const_Iterador;


    DiccAcot();
    DiccAcot(const Nat n);
    //DiccAcot(const DiccAcot<K,S>& otro);
    //DiccAcot<K,S>& operator=(const DiccAcot<K,S>& otro);

    Iterador Definir(const K& clave, const S& significado);
    Iterador DefinirRapido(const K& clave, const S&);

    bool Definido(const K& clave) const;
    const S& Significado(const K& clave) const;
    S& Significado(const K& clave);
    void Borrar(const K& clave);
    Nat CantClaves() const;
    Nat MaxClaves() const;
    bool operator == (DiccAcot<K,S>) const;
    Iterador CrearIt();
    const_Iterador CrearIt() const;



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
        friend class DiccAcot<K, S>::const_Iterador;
    };

    class const_Iterador
    {
      public:

        const_Iterador();

        const_Iterador(const typename DiccAcot<K,S>::Iterador& otro);

        const_Iterador(const typename DiccAcot<K, S>::const_Iterador& otro);

        const_Iterador& operator = (const typename DiccAcot<K, S>::const_Iterador& otro);

        bool operator==(const typename DiccAcot<K,S>::const_Iterador&) const;

        bool HaySiguiente() const;
        const K& SiguienteClave() const;
        const S& SiguienteSignificado() const;
        const_Elem Siguiente() const;
        void Avanzar();


    private:

        typename Arreglo<Elem>::const_Iterador *it_elementos;
        Nat _i;
        Nat _long;

        const_Iterador(const DiccAcot<K,S>* d);

        friend typename DiccAcot<K,S>::const_Iterador DiccAcot<K,S>::CrearIt() const;

     };

    struct Elem{
      public:

        K& clave;
        S& significado;

        Elem( K& c, S& s) : clave(c), significado(s) {}

        friend std::ostream& operator<<(std::ostream& os, const DiccAcot<K,S>::Elem& e) {
          return os << e.clave << ":" << e.significado;
        }

        typename DiccAcot<K,S>::Elem& operator=(const typename DiccAcot<K,S>::Elem&);
      private:


    };

    struct const_Elem
    {
      public:

        const K& clave;
        const S& significado;

        const_Elem(const K& c, const S& s) : clave(c), significado(s) {}

        friend std::ostream& operator << (std::ostream& os, const DiccAcot<K,S>::const_Elem& e) {
          return os << e.clave << ":" << e.significado;
        }

      private:
        typename DiccAcot<K,S>::const_Elem& operator= (const typename  DiccAcot<K,S>::const_Elem&);
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
    Nat i=0;
    //auxK y auxS los usamos para ir trasladando los elementos del array
    K auxK = c;
    S auxS = s;
    //auxK2 y auxS2 los usamos para el swap
    K auxK2;
    S auxS2;
    while (i<CantClaves()){
        if ((_elementos[i].clave)>c){
            auxK2 = _elementos[i].clave;
            auxS2 =_elementos[i].significado;
            _elementos[i]=Elem(auxK, auxS);
            auxK=auxK2;
            auxS=auxS2;
        }
        i++;
    }
	auxK = c;
	auxS = s;

    _elementos.Definir(i, Elem(auxK, auxS));
    _lReal++;
	cout <<endl << i << endl;
	cout <<endl<<endl<< _elementos[i] << endl << endl;
	return CrearIt();
}
template<class K,class S>
typename DiccAcot<K, S>::Iterador DiccAcot<K,S>::DefinirRapido(const K& c, const S& s) {
    const_Elem a=const_Elem(c,s);
    _elementos[_lReal]=a;
    _lReal++;
    return CrearIt();
}

template<class K,class S>
bool DiccAcot<K,S>::Definido(const K& c) const {
cout << _elementos[0] << endl << endl;
    Nat i=_lReal/2;
    Nat mx=_lReal;
    Nat mn=0;
	do {
//cout << _elementos[i].clave << endl << endl;
		if (_elementos[i].clave==c) {
            return true;
        } else if (_elementos[i].clave<c) {
            mn=i;
            i=(i+mx)/2;
        } else {

            mx=i;
            i=(i+mn)/2;
        }
	}
    while (mx > mn+1);

    return false;
}

template<class K,class S>
S& DiccAcot<K,S>::Significado(const K& c) {
    Nat i=_lReal/2;
    Nat mx=_lReal;
    Nat mn=0;
    while (true) {
        if (_elementos[i].clave==c) {
            return (_elementos[i]).significado;
        } else if ((_elementos[i]).clave<c) {
            mn=i;
            i=(i+mx)/2;
        } else {
            mx=i;
            i=(i+mn)/2;
        }
    }
}

template<class K,class S>
void DiccAcot<K,S>::Borrar(const K& clave){

    Nat i=0;
    bool encontrado = false;

    while(i < _lReal-1){

        if (_elementos[i].clave== clave || encontrado){
            _elementos[i] = _elementos[i+1];
            encontrado = true;
        }
        i++;

    }

    _lReal--;

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

    int i = 0;
    bool res = true;

    if(_lReal != d2._lReal)                         {res = false;}
    else{
        while (i < _lReal){
            if(_elementos[i] == d2._elementos[i])   {res = false;}
        }
        i++;
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

    return _i<_long-1;

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
typename DiccAcot<K,S>::Elem& DiccAcot<K,S>::Elem::operator=(const typename  DiccAcot<K,S>::Elem& otro){
    clave=otro.clave;
    significado=otro.significado;
    return *this;
}


template<class K,class S>
typename DiccAcot<K,S>::const_Elem& DiccAcot<K,S>::const_Elem::operator=(const typename  DiccAcot<K,S>::const_Elem& otro){
    clave=otro.clave;
    significado=otro.significado;
    return *this;
}
