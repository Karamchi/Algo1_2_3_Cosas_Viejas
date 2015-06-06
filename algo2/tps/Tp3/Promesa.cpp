#include "Promesa.h"

const Nombre Promesa::titulo() const{

    return _titulo;

}

const TipoPromesa Promesa::tipo() const{

    return _tipo;

}

const Nat Promesa::limite() const{

    return _limite;

}

const Nat Promesa::cantidad() const{

    return _cantidad;

}

 Promesa Promesa::crearPromesa(Nombre n, TipoPromesa t, Dinero l, Nat c){

    _titulo = n;
    _tipo = t;
    _limite = l;
    _cantidad = c;

    return *this;

}

bool Promesa::promesaEjecutable(Dinero d, Nat n){

    if(tipo()==vender && d<limite()) {
        return true;
    }

    if (tipo()==comprar && d>limite() && n>= cantidad()) {
        return true;
    }

    return false;
}

const Nat compraVenta(Nat d,const Conj<Promesa> ps){

    typename Conj<Promesa>::const_Iterador it = ps.CrearIt();

    Nat res = d;

    while (it.HaySiguiente()){

        if(it.Siguiente().tipo() == comprar) {
            res = res + it.Siguiente().cantidad();
        }

        else{
            res = res - it.Siguiente().cantidad();
        }
        it.Avanzar();
    } return res;

}

const Conj<Promesa> promesasSobreTitulo(Nombre n, TipoPromesa t, Conj<Promesa> ps){

    typename Conj<Promesa>::const_Iterador it = ps.CrearIt();

    Conj<Promesa> res;

    while(it.HaySiguiente()){

        if(it.Siguiente().titulo() == n && it.Siguiente().tipo() == t) {
            res.AgregarRapido(it.Siguiente());
        }
        it.Avanzar();
    }
    return res;
}

const bool Promesa::operator == (Promesa p) const{
	bool b = titulo() == p.titulo() && tipo() == p.tipo() && limite() == p.limite() && cantidad() == p.cantidad();
	return b;
}

const bool Promesa::operator != (Promesa p) const{
	bool b = titulo() != p.titulo() || tipo() != p.tipo() || limite() != p.limite() || cantidad() != p.cantidad();
	return b;
}


