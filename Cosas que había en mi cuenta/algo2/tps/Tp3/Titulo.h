#include <iostream>
#include "Modulos-CPP/aed2/TiposBasicos.h"
#include "Modulos-CPP/aed2/Conj.h"
#include "Modulos-CPP/aed2/Vector.h"
#include "Promesa.h"

using namespace std;
using namespace aed2;

typedef Nat Dinero;
typedef string Nombre;


struct Titulo
{
public:

const Nombre nombre() const;

const Nat cantmax() const;

const Nat cot() const;

const bool enalza() const;

Titulo nuevoT(const Nombre n, Nat c, Nat cm);

void recotizar(Nat c);

Nat cotActual(Nombre nt, Conj<Titulo> ts);

void cambiarCotTs(Nombre nt, Dinero c, Conj<Titulo> &ts);

Nat limTen(Nombre nt, Conj<Titulo> ts);

bool titEnAlza(Nombre nt, Conj<Titulo> ts);

bool operator==(const Titulo) const;

bool operator!=(const Titulo t) const;

private:

Nombre _nombre;
Nat _cot;
Nat _cantmax;
bool _enalza;

};
