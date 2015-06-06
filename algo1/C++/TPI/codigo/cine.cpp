#include "pelicula.h"
#include "lista.h"
#include "ticket.h"
#include "tipos.h"
#include "cine.h"
#include <iostream>
#include <fstream>

using namespace std;

Cine::Cine(Nombre n)
{
    nombre_ =n;
    Lista<pair<Pelicula,Sala> > peliculas_ ;
    Lista<pair<Sala, int> > espectadores_ ;
    Lista<Ticket> ticketsVendidos_ ;
    Lista<Sala> salasSinUsar_;
}

string Cine::nombreC() const {
	return nombre_;
}

Lista<Pelicula> Cine::peliculasC() const {
	Lista<std::pair<Pelicula,Sala> > ps=peliculas_;
	Lista<Pelicula> res;
	int i=0;
	while (i<ps.longitud()) {
        res.agregar((ps.iesimo(i)).first);
        i++;
	} return res;
}

Lista<Sala> Cine::salasC() const {
	Lista<std::pair<Pelicula,Sala> > ps=peliculas_;
	Lista<Sala> res=salasSinUsar_;
	int i=0;
	while (i<ps.longitud()) {
        res.agregar((ps.iesimo(i)).second);
        i++;
	} return res;
}

int Cine::espectadoresC(Sala s) const {
    Lista<pair<Sala, int> > es=espectadores_;
    int res=0;
	int i=0;
	while (i<es.longitud()) {
        if (((es.iesimo(i)).first)==s) {
            res=((es.iesimo(i)).second);
        } i++;
	} return res;
}

Sala Cine::salaC(const Nombre &n) const {
    Lista<std::pair<Pelicula,Sala> > ps=peliculas_;
    int i=0;
    Sala res=0;
    while(i<ps.longitud()) {
        if (((ps.iesimo(i)).first).nombreP()==n) {
          res=((ps.iesimo(i)).second);
        } i++;
    } return res;
}

Lista <Ticket> Cine::ticketsVendidosSinUsarC() const {
    return ticketsVendidos_;
}

void Cine::abrirSalaC(Sala s) {

    Lista<Sala> cs=salasSinUsar_;
    cs.agregar(s);
    salasSinUsar_ = cs;
    espectadores_.agregar(make_pair(s,0));
}

void Cine::agregarPeliculaC(const Pelicula &c, Sala s){

    Lista<pair<Pelicula,Sala> > pc = peliculas_;
    Lista<Sala> ssu = salasSinUsar_;
    salasSinUsar_.sacar(s);
    pair<Pelicula,Sala> pcn = make_pair(c,s);
    peliculas_.agregar(pcn);
    pair<Sala, int> a = make_pair(s,0);
    espectadores_.agregar(a);

}

void Cine::cerrarSalaC(Sala s) {
    Pelicula pp;
    int i = 0;

    while (i < peliculas_.longitud()){
        if (((peliculas_.iesimo(i)).second)==s) {
          pp=((peliculas_.iesimo(i)).first);
        } i++;
    }

    pair<Pelicula,Sala> pcn = make_pair(pp,s);

    peliculas_.sacar(pcn);
    i = 0;

    while (i < espectadores_.longitud()){
        if (((espectadores_.iesimo(i)).first)==s) {
          espectadores_.eliminarPosicion(i);
        } i++;
    }

}

void Cine::cerrarSalasC(int e){

    int i = 0;
    while (i<espectadores_.longitud())
    {        if (e>espectadores_.iesimo(i).second) {
        cerrarSalaC(espectadores_.iesimo(i).first);}
        i++;
    }
    }

void Cine::cerrarSalasDeLaCadenaC(Lista<Cine> &cs, int e) const{
    int i = 0;
    while (i<cs.longitud())
    {
        Cine csi;
        csi = cs.iesimo(0);
        csi.cerrarSalasC(e);
        cs.agregarAtras(csi);
        cs.eliminarPosicion(0);
        i=i+1;
    }
}

Pelicula Cine::peliculaC(Sala s) const {
    Lista<std::pair<Pelicula,Sala> > ps=peliculas_;
    int i=0;
    Pelicula res;
    while(i<ps.longitud()) {
        if (((ps.iesimo(i)).second)==s) {
          res=((ps.iesimo(i)).first);
        } i++;
    } return res;
}

Ticket Cine::venderTicketC(const Nombre &p) {
    Lista<std::pair<Pelicula,Sala> > ps=peliculas_;
    int i=0;
    Pelicula pel;
    while(i<ps.longitud()) {
        if (((ps.iesimo(i)).first).nombreP()==p) {
          pel=(ps.iesimo(i)).first;
        }
        i++;
    } Ticket res= Ticket(pel,salaC(p),false);
    ticketsVendidos_.agregar(res);
    return res;
}

Ticket Cine::ingresarASalaC(Sala s, const Ticket &t){
    Lista<pair<Sala, int> > es=espectadores_;
    int i=0;
    int se=0;
    while (i<es.longitud()) {
        if (((es.iesimo(i)).first)==s) {
        se=i;
        }
        i++;
    }

    espectadores_.agregarAtras(make_pair(s,espectadoresC(s)+1));
    espectadores_.sacar(es.iesimo(se));
    ticketsVendidos_.eliminarPosicion(ticketsVendidos_.posicion(t));
    Pelicula p=t.peliculaT();
    Ticket res=Ticket(p,s,true);
    return res;
}
Pelicula Cine::pasarA3DUnaPeliculaC(Nombre n){
    std::pair <Pelicula,Sala> p;
    Lista<std::pair<Pelicula,Sala> > ps=peliculas_;
    int i = 0;
    while (i<ps.longitud()){
        if (n == ps.iesimo(i).first.nombreP())
        {
        p.first = Pelicula(n,((ps.iesimo(i)).first).generosP(),(ps.iesimo(i)).first.actoresP(), true);
        p.second = ps.iesimo(i).second;
        this->peliculas_.eliminarPosicion(i);
        this->peliculas_.agregar(p);
         }
    i++;
    }
    return p.first;
    }

std::ostream& operator<<(std::ostream &os, const Cine &c){
    os << "Peliculas: "<< c.peliculasC() << endl << "Salas: " << c.salasC() << endl << "TVSU: " << c.ticketsVendidosSinUsarC();
    cout << os;
    return os;
}

  void Cine::cargar (std::istream& is) {

    Nombre n;
    Pelicula p;
    Lista<pair<Pelicula,Sala> > ps ;
    Lista<pair<Sala, int> > es ;
    Lista <Ticket> tvsu;
    int s;
    int e;
    int i;
    Ticket t;
    char c;
    is >> c;
    is >> c;
    getline(is, nombre_,'|');
    is >> c;//descarta el [
    while (c!=']') {
        is >> s;
        salasSinUsar_.agregarAtras(s);
        is >> c;//vale , o ]
    }
    is >> c;//descarta [
    while (c!=']') {
        is >> c;//descarta (
        if (c==']'){
            break;
        }
        is >> s;
        is >> c;//descarta ,
        is >> e;
        es.agregarAtras(make_pair(s,e));
        is >> c;//descarta )
        is >> c;//vale , o ]
    }
    espectadores_ = es;
    is >> c;//descarta [
    while (c!=']') {
        is >> c;//descarta (
        if (c==']'){
            break;
        }
        is >> s;
        is >> c;//descarta ,
        is >> i;
        while (i !=0) {
        ticketsVendidos_.agregar(Ticket(peliculaC(s),s,false));
        i=i-1;
        }
        is >> c;//descarta )
        is >> c;//vale , o ]
    }
    is >> c;//descarta [
    while (c!=']') {
        is >> c;//descarta (
        if (c==']'){
            break;
        }
        is >> s;
        is >> c;//descarta ,
        is >> c;//descarta (
        p.cargar(is);
        ps.agregarAtras(make_pair(p,s));
        is >> c;//descarta )
        is >> c;//descarta )
        is >> c;//vale , o ]
    }
    peliculas_ =ps;
    is >> c;
  }

void Cine::guardar(std::ostream& os) const
  {
      os << 'C';
      os << ' ';
      os << '|';
      os << ' ';
      os << nombre_;
      os << ' ';
      os << '|';
      os << ' ';
      os << '[';
      int i=0;
      while (i<salasSinUsar_.longitud()) {
          os << salasSinUsar_.iesimo(i);
          if(i != salasSinUsar_.longitud()-1){os << ',';}
          i++;
      }
      i=0;
      os << ']';
      os << ' ';
      os << '[';
      while (i<espectadores_.longitud()) {
          os << '(';
          os << espectadores_.iesimo(i).first;
          os << ',';
          os << espectadores_.iesimo(i).second;
          os << ')';
          if(i != espectadores_.longitud()-1){os << ',';}
          i++;
      }
      i=0;
      os << ']';
      os << ' ';
      os << '[';
      while (i<peliculas_.longitud()) {
          os << '(';
          os << peliculas_.iesimo(i).second;
          os << ',';
          int j=0;
          int t=0;
          while (j<ticketsVendidos_.longitud()){
            if (ticketsVendidos_.iesimo(j).salaT()==peliculas_.iesimo(i).second) {
                t++;
            } j++;
          }
          os << t;
          os << ')';
          if(i != peliculas_.longitud()-1){os << ',';}
          i++;
      }
      os << ']';
      os << ' ';
      os << '[';
      while (i<peliculas_.longitud()) {
          os << '(';
          os << peliculas_.iesimo(i).second;
          os << ',';
          os << '(';
          (peliculas_.iesimo(i).first).guardar(os);
          os << ')';
          os << ')';
          if(i != espectadores_.longitud()-1){os << ',';}
          i++;
      }
      os << ']';
  }

void Cine::mostrar(std::ostream& os) const {
      cout << "Cine: ";
      cout << nombre_ << endl;
      cout << "Salas sin usar: ";
      int i=0;
      while (i<salasSinUsar_.longitud()) {
          cout << salasSinUsar_.iesimo(i);
          if(i != salasSinUsar_.longitud()-1){cout << ',';}
          i++;
      }
      i=0;
      cout << endl;
      cout << "Espectadores por sala:";
      while (i<espectadores_.longitud()) {
          cout << "Sala ";
          cout << espectadores_.iesimo(i).first;
          cout << ": ";
          cout << espectadores_.iesimo(i).second;
          cout << ',';
          if(i != espectadores_.longitud()-1){cout << ',';}
          i++;
      }
      cout << endl;
      i=0;
      cout << "Peliculas por sala: ";
      while (i<peliculas_.longitud()) {
          cout << "Sala ";
          cout << peliculas_.iesimo(i).second;
          cout << ": ";
          cout << '(';
          (peliculas_.iesimo(i).first).mostrar(os);
          cout << ')';
          if(i != espectadores_.longitud()-1){cout << ',';}
          i++;
      }
      cout << endl;
      i=0;
      cout << "Tickets vendidos sin usar: ";
      while (i<ticketsVendidos_.longitud()) {
          cout << '(';
          ticketsVendidos_.iesimo(i).mostrar(os);
          cout << ')';
          if(i != espectadores_.longitud()-1){cout << ',';}
          i++;
      }
}
