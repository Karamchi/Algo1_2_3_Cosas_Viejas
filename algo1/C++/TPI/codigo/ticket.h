#ifndef TICKET_H_
#define TICKET_H_

#include "lista.h"
#include "pelicula.h"
#include "tipos.h"

class Ticket {
 public:
  Ticket(){}
  Ticket(const Pelicula &p, Sala s, bool u);
  const Pelicula &peliculaT() const;
  Sala salaT() const;
  bool usadoT() const;
  void usarT();
  Pelicula peliculaMenosVistaT(const Lista<Ticket> &ts) const;
  bool todosLosTicketsParaLaMismaSalaT(const Lista<Ticket> &ts) const;
  Lista<Ticket> cambiarSalaT(const Lista<Ticket> &ts, Sala vieja, Sala nueva) const;
  Ticket ingresarASalaC(Sala s, const Ticket &t);

  bool operator==(const Ticket &otro) const {
    return pelicula_ == otro.pelicula_ && sala_ == otro.sala_ && usado_ == otro.usado_;
  }

  void mostrar(std::ostream& os) const;
  void guardar(std::ostream& os) const;
  void cargar (std::istream& is);

 private:
  Pelicula pelicula_;
  Sala sala_;
  bool usado_;
};

std::ostream & operator<<(std::ostream & os,const Ticket & t);
std::istream & operator>>(std::istream & is, Ticket & t);


#endif // TICKET_H_
