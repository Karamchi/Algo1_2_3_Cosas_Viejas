#include <iostream>
#include "Modulos-CPP/aed2/TiposBasicos.h"
#include "Modulos-CPP/aed2/Conj.h"

using namespace std;
using namespace aed2;

typedef Nat Dinero;
typedef string Nombre;
typedef enum{comprar, vender} TipoPromesa;

struct Promesa
{
public:

const Nombre titulo() const;

const TipoPromesa tipo() const;

const Nat limite() const;

const Nat cantidad() const;

Promesa crearPromesa(Nombre n, TipoPromesa t, Dinero l, Nat c);

bool promesaEjecutable(Dinero d, Nat n);

const Nat compraVenta(Nat d, Conj<Promesa> ps);

const Conj<Promesa> promesasSobreTitulo(Nombre n, TipoPromesa t, Conj<Promesa> ps);

const bool operator == (Promesa) const;

const bool operator != (Promesa) const;

private:

Nombre _titulo;
TipoPromesa _tipo;
Nat _cantidad;
Nat _limite;

};
