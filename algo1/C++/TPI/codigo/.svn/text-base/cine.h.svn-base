
#ifndef CINE_H_
#define CINE_H_

#include "lista.h"
#include "pelicula.h"
#include "tipos.h"
#include "ticket.h"
#include <utility>

using namespace std;

class Cine {
 public:
  Cine(){}
  Cine(Nombre n);
  Cine(const Cine &c) {
    nombre_ = c.nombre_;
    peliculas_ = c.peliculas_;
    espectadores_ = c.espectadores_;
    ticketsVendidos_ = c.ticketsVendidos_;
    salasSinUsar_ = c.salasSinUsar_;
  }
  string nombreC() const;
  Lista<Pelicula> peliculasC() const;
  Lista<Sala> salasC() const;
  Sala salaC(const Nombre &p) const;
  int espectadoresC(Sala s) const;
  Lista<Ticket> ticketsVendidosSinUsarC() const;

  void abrirSalaC(Sala s);
  void agregarPeliculaC(const Pelicula &c, Sala s);
  void cerrarSalaC(Sala s);
  void cerrarSalasC(int e);
  void cerrarSalasDeLaCadenaC(Lista<Cine> &cs, int e) const;
  Pelicula peliculaC(Sala s) const;
  Ticket venderTicketC(const Nombre &p);
  Ticket ingresarASalaC(Sala s, const Ticket &t);
  Pelicula pasarA3DUnaPeliculaC(Nombre n);

  void mostrar(std::ostream& os) const;
  void guardar(std::ostream& os) const;
  void cargar (std::istream& is);

 private:
  Nombre nombre_;
  Lista<pair<Pelicula,Sala> > peliculas_;
  Lista<pair<Sala, int> > espectadores_;
  Lista<Ticket> ticketsVendidos_;
  Lista<Sala> salasSinUsar_;
};

std::ostream & operator<<(std::ostream & os, const Cine & c);
std::istream & operator>>(std::istream & is, Cine& c);


#endif // CINE_H_
