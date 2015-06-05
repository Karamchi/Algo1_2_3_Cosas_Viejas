#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

struct Parabrisas
{
public:

Parabrisas();

Parabrisas(int largo, int ancho, long double h, int radio, int temp, int cantidad);

void agSanguijuela(long double x, long double y, int i);
void elimSanguijuela(int i);
void elimSanguijuelaMasCercana(int&, int&);
vector<long double> SangX();
vector<long double> SangY();
int largo();
int radio();
int ancho();
long double h();
int temp();
int cantidad();

private:

vector <long double> _sangx;
vector <long double> _sangy;		
int _largo;
int _ancho;
int _radio;
long double _h;
int _temp;
int _k;

};
