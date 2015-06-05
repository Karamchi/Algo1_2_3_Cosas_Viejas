#include<iostream>

#include "test.h"

#define ASSERT(x, msg) \
    if (! (x)) \
    { \
        cout << "ERROR!! Assert " << #x << " failed" << endl; \
        cout << " on line " << __LINE__  << endl; \
        cout << " in file " << __FILE__ << endl;  \
        cout << " msg: " << msg << endl << endl; \
        errores++; \
        fallo = true; \
    }

using namespace std;

int errores;

bool fallo;

#include <vector>
#include "cine.h"

vector<Ticket> tiques;
vector<Cine> cines;
vector<Pelicula> pelis;

void TestCine()
{
  Cine a((Nombre) "Cine1");

  if(a.nombreC()!="Cine1") fallo=1,cout<<"Falla nombreC"<<endl;

  a.abrirSalaC(1);
  a.abrirSalaC(3);
  a.abrirSalaC(5);

  if(a.salasC().longitud()!=3) fallo=1,cout<<"Falla abrirSalaC"<<endl;
  if(!a.salasC().pertenece(1)) fallo=1,cout<<"Falla abrirSalaC"<<endl;
  if(!a.salasC().pertenece(3)) fallo=1,cout<<"Falla abrirSalaC"<<endl;
  if(!a.salasC().pertenece(5)) fallo=1,cout<<"Falla abrirSalaC"<<endl;

  a.agregarPeliculaC(pelis[0],1);
  a.agregarPeliculaC(pelis[1],3);
  a.agregarPeliculaC(pelis[2],5);

  if(a.peliculasC().longitud()!=3) fallo=1,cout<<"Falla agregarPeliculaC"<<endl;
  if(!a.peliculasC().pertenece(pelis[0])) fallo=1,cout<<"Falla agregarPeliculaC"<<endl;
  if(!a.peliculasC().pertenece(pelis[1])) fallo=1,cout<<"Falla agregarPeliculaC"<<endl;
  if(!a.peliculasC().pertenece(pelis[2])) fallo=1,cout<<"Falla agregarPeliculaC"<<endl;

  a.cerrarSalaC(1);
  if(a.salasC().longitud()!=2) fallo=1,cout<<"Falla cerrarSalaC"<<endl;
  if(!a.salasC().pertenece(3)) fallo=1,cout<<"Falla cerrarSalaC"<<endl;
  if(!a.salasC().pertenece(5)) fallo=1,cout<<"Falla cerrarSalaC"<<endl;
  if(a.peliculasC().longitud()!=2) fallo=1,cout<<"Falla cerrarSalaC"<<endl;
  if(!a.peliculasC().pertenece(pelis[1])) fallo=1,cout<<"Falla cerrarSalaC"<<endl;
  if(!a.peliculasC().pertenece(pelis[2])) fallo=1,cout<<"Falla cerrarSalaC"<<endl;

  if(!(a.peliculaC(3)==pelis[1])) fallo=1,cout<<"Falla peliculaC" <<endl;
  if(!(a.peliculaC(5)==pelis[2])) fallo=1,cout<<"Falla peliculaC" <<endl;


  a.pasarA3DUnaPeliculaC("Peli2");
  if(!a.peliculaC(3).es3DP()) fallo=1,cout<<"Falla pasarA3D" <<endl;

  Ticket t;
  t = a.venderTicketC("Peli3");
  if(t.usadoT()) fallo=1,cout<<"Falla venderTicketC"<<endl;
  if(t.salaT()!=5) fallo=1,cout<<"Falla venderTicketC"<<endl;
  if(!(t.peliculaT()==pelis[2])) fallo=1,cout<<"Falla venderTicketC"<<endl;
  a.venderTicketC("Peli3");

  if(a.ticketsVendidosSinUsarC().longitud()!=2) fallo=1,cout<<"Falla ticketsVendidosSinUsarC"<<endl;
  if(!a.ticketsVendidosSinUsarC().pertenece(t)) fallo=1,cout<<"Falla ticketsVendidosSinUsarC"<<endl;

  a.ingresarASalaC(5,t);
  if(a.espectadoresC(5)!=1) fallo=1,cout<<"Falla ingresarASalaC"<<endl;
  if(a.ticketsVendidosSinUsarC().longitud()!=1) fallo=1,cout<<"Falla ingresarASalaC"<<endl;
  if(!a.ticketsVendidosSinUsarC().pertenece(t)) fallo=1,cout<<"Falla ingresarASalaC"<<endl;
  t = a.ingresarASalaC(5,t);
  if(a.espectadoresC(5)!=2) fallo=1,cout<<"Falla ingresarASalaC"<<endl;
  if(a.ticketsVendidosSinUsarC().longitud()!=0) fallo=1,cout<<"Falla ingresarASalaC"<<endl;
  if(!t.usadoT()) fallo=1,cout<<"Falla ingresarASalaC"<<endl;

  a.cerrarSalasC(1);

  if(a.peliculasC().longitud()!=1) fallo=1,cout<<"Falla cerrarSalasC1"<<endl;
  if(!a.peliculasC().pertenece(pelis[2])) fallo=1,cout<<"Falla cerrarSalasC2"<<endl;

  ///void cerrarSalasDeLaCadenaC(Lista<Cine> &cs, int e) const;
}

void iniciarDatosCine() {
}

void TestPelicula()
{

  Actor actor[5] = {"Actor1","Actor2","Actor3","Actor4","Actor5"};
  Lista<Genero> gen1,gen2,gen3;
  gen1.agregarAtras((Genero)1);
  gen1.agregarAtras((Genero)2);
  gen2.agregarAtras((Genero)2);
  gen2.agregarAtras((Genero)3);
  gen3.agregarAtras((Genero)4);
  Lista<Actor> act1,act2,act3;
  act1.agregarAtras(actor[0]);
  act1.agregarAtras(actor[2]);
  act1.agregarAtras(actor[3]);
  act2.agregarAtras(actor[1]);
  act3.agregarAtras(actor[1]);
  act3.agregarAtras(actor[2]);
  act3.agregarAtras(actor[3]);
  act3.agregarAtras(actor[4]);

  Pelicula a("Peli1",gen1,act1,0);
  Pelicula b("Peli2",gen2,act2,0);
  Pelicula c("Peli3",gen3,act3,1);

  if(a.nombreP()!="Peli1") fallo=1,cout << "Falla nombreP"<< endl;
  if(b.nombreP()!="Peli2") fallo=1,cout << "Falla nombreP"<< endl;
  if(c.nombreP()!="Peli3") fallo=1,cout << "Falla nombreP"<< endl;

  if(!(a.generosP()==gen1)) fallo=1,cout<<"Falla generosP"<<endl;
  if(!(b.generosP()==gen2)) fallo=1,cout<<"Falla generosP"<<endl;
  if(!(c.generosP()==gen3)) fallo=1,cout<<"Falla generosP"<<endl;

  if(a.es3DP()) fallo=1,cout<<"Falla es3DP" << endl;
  if(b.es3DP()) fallo=1,cout<<"Falla es3DP" << endl;
  if(!c.es3DP()) fallo=1,cout<<"Falla es3DP" << endl;

  if(!(a.actoresP()==act1)) fallo=1,cout<<"Falla actoresP" << endl;
  if(!(b.actoresP()==act2)) fallo=1,cout<<"Falla actoresP" << endl;
  if(!(c.actoresP()==act3)) fallo=1,cout<<"Falla actoresP" << endl;

  Lista<Pelicula> ps;
  ps.agregarAtras(a);
  ps.agregarAtras(b);
  ps.agregarAtras(c);
  Lista<std::pair<Genero,Lista<Pelicula> > > ans1,ans2,ans3;

  Lista<std::pair<Genero,Lista<Pelicula> > > res = a.agruparPelisPorGeneroP(ps);
  if(res.longitud()!=4) fallo=1,cout << "Falla agruparPelis" << endl;
  Lista<Pelicula> l1,l2,l3,l12,l21;
  l1.agregarAtras(a);
  l2.agregarAtras(b);
  l3.agregarAtras(c);
  l12.agregarAtras(a);
  l12.agregarAtras(b);
  l21.agregarAtras(b);
  l21.agregarAtras(a);

  if(!(res.pertenece(make_pair((Genero) 1, l1)))) fallo=1,cout << "Falla agruparPelis" << endl;
  if(!(res.pertenece(make_pair((Genero) 3, l2)))) fallo=1,cout << "Falla agruparPelis" << endl;
  if(!(res.pertenece(make_pair((Genero) 4, l3)))) fallo=1,cout << "Falla agruparPelis" << endl;
  if(!(res.pertenece(make_pair((Genero) 2, l12)) || res.pertenece(make_pair((Genero) 2, l21)))) fallo=1,cout << "Falla agruparPelis" << endl;

  Lista<Nombre> noms;
  noms.agregarAtras("P1");
  noms.agregarAtras("P2");
  noms.agregarAtras("P3");

  if(a.generarSagaDePeliculasP(act1,gen2,noms).longitud()!=3) fallo=1,cout<<"Falla generarSagaDePeliculas" << endl;

  pelis.push_back(a);
  pelis.push_back(b);
  pelis.push_back(c);
}

void iniciarDatosPelicula()
{
}

void TestTicket()
{
  Ticket a(pelis[0],1,1);
  Ticket b(pelis[1],2,0);
  Ticket c(pelis[2],3,1);

  if(!(a.peliculaT()==pelis[0])) fallo=1,cout<<"Falla peliculaT"<<endl;
  if(!(b.peliculaT()==pelis[1])) fallo=1,cout<<"Falla peliculaT"<<endl;
  if(!(c.peliculaT()==pelis[2])) fallo=1,cout<<"Falla peliculaT"<<endl;

  if(a.salaT()!=1) fallo=1,cout<<"Falla salaT"<<endl;
  if(b.salaT()!=2) fallo=1,cout<<"Falla salaT"<<endl;
  if(c.salaT()!=3) fallo=1,cout<<"Falla salaT"<<endl;

  Lista<Ticket> ts;
  ts.agregarAtras(b);
  ts.agregarAtras(b);
  ts.agregarAtras(b);

  if(!a.usadoT()) fallo=1,cout<<"Falla usadoT" << endl;
  if(b.usadoT()) fallo=1,cout<<"Falla usadoT" << endl;
  if(!c.usadoT()) fallo=1,cout<<"Falla usadoT" << endl;
  b.usarT();
  if(!b.usadoT()) fallo=1,cout<<"Falla usarT" << endl;

  ts.agregarAtras(b);

  Lista<Ticket> ts3;
  ts3 = ts;

  ts.agregarAtras(a);
  ts.agregarAtras(c);
  ts.agregarAtras(a);
  ts.agregarAtras(c);
  if(!(a.peliculaMenosVistaT(ts)==pelis[1])) fallo=1,cout<<"Falla peliculaMenosVistaT" << endl;
  Lista<Ticket> ts2;
  ts2 = ts;

  ts = a.cambiarSalaT(ts,2,4);
  for(int i = 0; i < ts.longitud(); i++) {
    if(!((ts2.iesimo(i).salaT() == 2 && ts.iesimo(i).salaT() == 4) || (ts2.iesimo(i).salaT() != 2 && ts.iesimo(i).salaT() == ts2.iesimo(i).salaT()))) fallo = 1, cout << "Falla cambiarSalaT" << endl;
  }
  if(a.todosLosTicketsParaLaMismaSalaT(ts)) fallo = 1, cout << " Falla todosLosTicketsParaLaMismaSalaT" << endl;
  if(a.todosLosTicketsParaLaMismaSalaT(ts2)) fallo = 1, cout << " Falla todosLosTicketsParaLaMismaSalaT" << endl;
  if(!a.todosLosTicketsParaLaMismaSalaT(ts3)) fallo = 1, cout << " Falla todosLosTicketsParaLaMismaSalaT" << endl;

  ///Ticket ingresarASalaC(Sala s, const Ticket &t);
  ///

}

void iniciarDatosTicket()
{
}

int correrTests()
{
    errores = 0;
    fallo = false;

    iniciarDatosPelicula();
    TestPelicula();

    iniciarDatosTicket();
    TestTicket();

    iniciarDatosCine();
    TestCine();

    if(fallo){
        cout << "Hay errores en la implementación." << endl;
    }
    else
        cout << "Los tests han finalizado correctamente." << endl;

    return fallo;
}
