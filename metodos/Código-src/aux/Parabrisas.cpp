#include <vector>
#include "Parabrisas.h"
#include <iostream>
#include <math.h>

using namespace std;

Parabrisas::Parabrisas(){}

Parabrisas::Parabrisas(int largo, int ancho, long double h, int radio, int temp, int cantidad){
	
	vector<long double> A(cantidad);
	vector<long double> B(cantidad);
	_sangx=A;
	_sangy=B;
	_largo=largo;
	_ancho=ancho;
	_radio=radio;
	_h=h;
	_temp=temp;
	_k=cantidad;
	
}

void Parabrisas::agSanguijuela(long double x,long double y, int i) {

	_sangx[i]=x; 
	_sangy[i]=y;

}

void Parabrisas::elimSanguijuela(int i) {
	for (int j=i;j<_k-1;j++) {
		_sangx[j]=_sangx[j+1];
		_sangy[j]=_sangy[j+1]; 	
	} _sangx.resize(_sangx.size()-1);
	_sangy.resize(_sangy.size()-1);
	_k--;
}

void Parabrisas::elimSanguijuelaMasCercana(int &x, int &y) {
	double centrox=_ancho/2;
	double centroy=_largo/2;
	double dmin=_ancho+_largo;
	double dist;
	int smin;
	for (int i=0;i<_k;i++){
		dist=sqrt(pow((_sangx[i]-centrox),2)+pow((_sangy[i]-centroy),2));
		if (dist<=dmin) {
			dmin=dist;
			smin=i;
		}
	x=_sangx[smin];
	y=_sangy[smin];
	} elimSanguijuela(smin);
}

vector <long double> Parabrisas::SangX() {

	return _sangx;

}

vector <long double> Parabrisas::SangY() {

	return _sangy;

}

int Parabrisas::largo(){

	return _largo;

}

int Parabrisas::ancho(){

	return _ancho;

}

int Parabrisas::radio(){

	return _radio;

}

long double Parabrisas::h(){

	return _h;

}

int Parabrisas::temp(){

	return _temp;

}

int Parabrisas::cantidad(){

	return _k;

}
