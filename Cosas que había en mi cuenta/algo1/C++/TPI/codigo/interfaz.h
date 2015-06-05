#ifndef INTERFAZ_H
#define INTERFAZ_H

#include <iostream>
#include <fstream>
#include "pelicula.h"
#include "ticket.h"
#include "cine.h"
#include "interfaz.cpp"

using namespace std;

void MenuPrincipal();
void MenuPelicula();
Pelicula MenuCrearPelicula();
void MenuTicket();
Ticket MenuCrearTicket();
void MenuCine();
Cine MenuCrearCine();

//AUX
int LeerOpcion(int maxOpcion);
void Pausar();
void Salir();
void LimpiarPantalla();
void AbrirArchivoParaLeer(ifstream &archivo);
void AbrirArchivoParaEscribir(ofstream &archivo);

#endif // INTERFAZ_H
