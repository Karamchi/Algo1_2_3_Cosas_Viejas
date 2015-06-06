#include <vector>
#include <iostream>

using namespace std;

typedef vector<long double> fila;

struct Matriz
{
public:

//generador basico, no se usa
Matriz();

//~Matriz();

//generador que te crea una matriz de un tamaño, no pide vectores
Matriz( int cantfilas, int cantcolumnas);

Matriz( int cantfilas, int cantcolumnas, int semiancho);

//generador que te crea la matriz con los vectores que le pasaste
Matriz( vector< vector<long double> > filas, int cantfilas, int cantcolumnas, vector<long double> indeps);

void Definir(long double adefinir, int fila, int columna);

void DefinirB(long double def,int fila);

void restarFilas(int filaRestada, int filaQueResta, long double multFilaARestar);

long double Posicion(int fila, int columna);

long double PosIndep(int fila);

int Cfilas();

int Ccolumnas();

int TamTotal();

int anchoBanda();	 

void mostrar();

private:

vector< vector<long double> > _array;

int _Cfilas;

int _Ccolumnas;

vector<long double> _indeps;

bool _banda;

int _anchoBanda;

};
