#ifndef DICCHASHCERRADO_H_
#define DICCHASHCERRADO_H_

#include "Lista.h"
#include "Arreglo.h"

namespace aed2 {

template<class S>
class DiccHashCerrado {
public:

	typedef String K;

	DiccHashCerrado();
	~DiccHashCerrado();

	bool 	 Definido(const K& clave) const;
	void 	 Definir(const K& clave, const S& significado);
	S& 		 Significado(const K& clave);
	void 	 Borrar(const K& clave);
	Nat 	 CantClaves() const;

	// solo para test!!
	Lista<K> Claves() const;
	float    factorCarga() const;
	Nat      colisiones() const;

private:

	#define TAM_TABLA_INI 100
	#define UMBRAL_FC	  0.75

	struct TElem{
			K 	 clave;
			S 	 signif;

			TElem(const K& c, const S& v) : clave(c), signif(v) {}
		};


	Arreglo<Lista<TElem> > 	_tabla;
	Nat 		 			_cant_elems;


	Nat fn_hash (const String& str) const {

		Nat hash = 0;
		for(Nat p = 0; p < 4 && p < str.size(); p++ ){
			Nat num = charToNat(str[p]);
			hash += ( num << p);
		}

		hash = hash % _tabla.Tamanho();

		return hash;
	}

	Nat charToNat(char c) const {
			return (Nat)(c);
	}


	void redimensionarTabla(){

		std::cerr << std::endl
				  << "Redimensionando tabla en " << _tabla.Tamanho()*2
				  << " elementos" << std::endl;

		Arreglo<Lista<TElem> > tabla_vieja(_tabla);

		_cant_elems = 0;
		_tabla.Redimensionar(0); // Borro el contenido de _tabla
		_tabla.Redimensionar(tabla_vieja.Tamanho()*2);

		for(Nat i=0; i < tabla_vieja.Tamanho(); i++){
			if(tabla_vieja.Definido(i)){
				for(typename Lista<TElem>::const_Iterador it = tabla_vieja[i].CrearIt(); it.HaySiguiente(); it.Avanzar())
					this->Definir(it.Siguiente().clave, it.Siguiente().signif);
			}
		}
	}
};

/********************************************************************************
 * Implementacion
 ********************************************************************************/

template<class S>
DiccHashCerrado<S>::DiccHashCerrado() : _tabla(TAM_TABLA_INI), _cant_elems(0) {}

template<class S>
DiccHashCerrado<S>::~DiccHashCerrado() {}

template<class S>
bool DiccHashCerrado<S>::Definido(const K& clave) const {
	Nat h=fn_hash(clave);
	Lista<TElem> l = (this->_tabla)[h];
    typename Lista<TElem>::Iterador it = l.CrearIt();
	while (it.HaySiguiente()) {
        if (it.Siguiente().clave == clave) {
            return true;
        } it.Avanzar();
	} return false;
}


template<class S>
void DiccHashCerrado<S>::Definir(const K& clave, const S& significado) {
    TElem t(clave, significado);
    Nat h=fn_hash(clave);
    if (this->_tabla.Definido(h)) {
        Lista<TElem> l = (this->_tabla)[h];
        if (Definido(clave)) {
            typename Lista<TElem>::Iterador it = l.CrearIt();
            while (it.HaySiguiente()) {
                if (it.Siguiente().clave == clave) {
                   it.Siguiente().signif=significado;
                  }
                  it.Avanzar();
            }
        } else {
            l.AgregarAtras(t);
            (this->_cant_elems)++;
        }
    } else {
        Lista<TElem> l;
        l.AgregarAtras(t);
        (this->_tabla).Definir(h, l);
        (this->_cant_elems)++;
    }
	if(factorCarga() > UMBRAL_FC)
		redimensionarTabla();

	//TODO
}


template<class S>
S& DiccHashCerrado<S>::Significado(const K& clave) {
    assert( Definido(clave) );
	Nat h=fn_hash(clave);
	Lista<TElem> l = (this->_tabla)[h];
    typename Lista<TElem>::Iterador it = l.CrearIt();
	while (it.HaySiguiente()) {
        if (it.Siguiente().clave == clave) {
            return it.Siguiente().signif;
        } it.Avanzar();
	}
}



template<class S>
void DiccHashCerrado<S>::Borrar(const K& clave) {
	assert( Definido(clave) );
	this->_cant_elems--;
    Nat h=fn_hash(clave);
    Lista<TElem> l = (this->_tabla)[h];
    typename Lista<TElem>::Iterador it = l.CrearIt();
    while (it.HaySiguiente()) {
        if (it.Siguiente().clave == clave) {
            it.EliminarSiguiente();
            break;
        } it.Avanzar();
    }
}

template<class S>
Nat DiccHashCerrado<S>::CantClaves() const {

	return _cant_elems;
}

// solo para test!!
template<class S>
Lista<typename DiccHashCerrado<S>::K> DiccHashCerrado<S>::Claves() const {
	Lista<K> ret;
	typename Lista<TElem>::const_Iterador it;

	for(Nat i=0; i < _tabla.Tamanho(); i++){
		if(_tabla.Definido(i)){
			for(it = _tabla[i].CrearIt(); it.HaySiguiente(); it.Avanzar())
				ret.AgregarAtras(it.Siguiente().clave);
		}
	}

	return ret;
}

// solo para test!!
template<class S>
float DiccHashCerrado<S>::factorCarga() const {

	return float(_cant_elems)/_tabla.Tamanho();
}

// solo para test!!
template<class S>
Nat DiccHashCerrado<S>::colisiones() const {

	Nat ret = 0;
	for(Nat i=0; i < _tabla.Tamanho(); i++){
		if(_tabla.Definido(i)){
			ret = ret + _tabla[i].Longitud() -1;
		}
	}

	return ret;
}


} /* namespace aed2 */

#endif /* DICCHASHCERRADO_H_ */
