#include "Titulo.h"

const Nombre Titulo::nombre() const{

    return _nombre;

}

const Nat Titulo::cantmax() const{

    return _cantmax;

}

const Nat Titulo::cot() const{

    return _cot;

}

const bool Titulo::enalza() const{

    return _enalza;

}

Titulo Titulo::nuevoT(const Nombre n, Nat c, Nat cm){
    _nombre = n;
    _cot = c;
    _cantmax = cm;
	_enalza = true;
    return *this;
}

void Titulo::recotizar(Nat c) {
    _enalza = _cot < c;
    _cot = c;
}


Nat cotActual(Nombre nt, Conj<Titulo> ts){
    typename Conj<Titulo>::const_Iterador it = ts.CrearIt();

    while (it.Siguiente().nombre() != nt){
        it.Avanzar();
    }
    return it.Siguiente().cot();
}


void cambiarCotTs(Nombre nt, Dinero c, Conj<Titulo> &ts){
    typename Conj<Titulo>::Iterador it = ts.CrearIt();

    while(it.Siguiente().nombre() != nt){
        it.Avanzar();
    }
	Titulo t = it.Siguiente();
	t.recotizar(c);
    it.EliminarSiguiente();
	ts.AgregarRapido(t);
}

Nat limTen(Nombre nt, Conj<Titulo> ts){
    typename Conj<Titulo>::const_Iterador it = ts.CrearIt();

    while (it.Siguiente().nombre() != nt){
        it.Avanzar();
    }
    return it.Siguiente().cantmax();
}

bool titEnAlza(Nombre nt, Conj<Titulo> ts){
    typename Conj<Titulo>::const_Iterador it = ts.CrearIt();

    while (it.Siguiente().nombre() != nt){
        it.Avanzar();
    }
    return it.Siguiente().enalza();
}

bool Titulo::operator==(const Titulo t) const{

	if (_nombre == t._nombre && _cot == t._cot && _cantmax == t._cantmax && _enalza == t._enalza)	{return true;}

	return false;

}

bool Titulo::operator!=(const Titulo t) const{

	if (_nombre == t._nombre && _cot == t._cot && _cantmax == t._cantmax && _enalza == t._enalza)	{return false;}

	return true;

}
