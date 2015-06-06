#include <iostream>
#include <cstdlib>
#include <time.h>
#include <fstream>

using namespace std;

struct __attribute__((packed)) instancia{
	int tiempo:32;
	short vehiculo:8;
};

struct __attribute__((packed)) tripla{
	int bmx:32;
	int moto:32;
	int buggy:32;
};

int main(){

	int buggies;
	int motos;
	int etapas;

	cin >> etapas;
	cin >> motos;
	cin >> buggies;

	int fila = buggies+1;

	instancia** matrices = (instancia**)malloc(((etapas)+1)*8);
	tripla* tiempos = (tripla*) malloc(12*(etapas+1));

	int i;
	int m;
	int b;
	int e=1;

	matrices[0] = (instancia*) malloc(5*fila*2);

	while(e<=etapas){
		cin >> i;
		cin >> m;
		cin >> b;

		tiempos[e].bmx = i;
		tiempos[e].moto = m;
		tiempos[e].buggy = b;

		matrices[e] = (instancia*) malloc(5*fila*(motos+1));

		e++;
	}

	clock_t t;
	t = clock();
	
	matrices[0][0].tiempo=0;

	for(e=1; e<=etapas; e++){
		for(m=0; ((m<=e)and(m<=motos)); m++){
			for(b=0; (((b+m)<=e)and(b<=buggies)); b++){
				if((b>0)and((m==0)or((matrices[e-1][m*fila+b-1].tiempo+tiempos[e].buggy)<=(matrices[e-1][(m-1)*fila+b].tiempo+tiempos[e].moto)))){
					if(((b+m)==e)or((matrices[e-1][m*fila+b-1].tiempo+tiempos[e].buggy)<=(matrices[e-1][m*fila+b].tiempo+tiempos[e].bmx))){
			 			matrices[e][m*fila+b].tiempo = matrices[e-1][m*fila+b-1].tiempo + tiempos[e].buggy;
			 			matrices[e][m*fila+b].vehiculo = 3;
			 		}else{
			 			matrices[e][m*fila+b].tiempo = matrices[e-1][m*fila+b].tiempo + tiempos[e].bmx;
			 			matrices[e][m*fila+b].vehiculo = 1;
			 		}
				}else{
					if((m>0)and(((b+m)==e)or(matrices[e-1][(m-1)*fila+b].tiempo+tiempos[e].moto)<=(matrices[e-1][m*fila+b].tiempo+tiempos[e].bmx))){
			 			matrices[e][m*fila+b].tiempo = matrices[e-1][(m-1)*fila+b].tiempo + tiempos[e].moto;
			 			matrices[e][m*fila+b].vehiculo = 2;
			 		}else{
			 			matrices[e][m*fila+b].tiempo = matrices[e-1][m*fila+b].tiempo + tiempos[e].bmx;
			 			matrices[e][m*fila+b].vehiculo = 1;
			 		}
				}
			}
		}
	}

	int minx = 0;
	int miny = 0;
	m = 0;
	b = 1;

	while(m<=motos){
		while((b<=buggies) and (b+m<=etapas)){
			if((matrices[etapas][m*fila+b].tiempo) < (matrices[etapas][miny*fila+minx].tiempo)){
				minx=b;
				miny=m;
			}
			b++;
		}
		b=0;
		m++;
	}

	minx = miny*fila+minx;

	i = matrices[etapas][minx].tiempo;

	for(e=etapas;e>0;e--){
		tiempos[e].bmx = matrices[e][minx].vehiculo;
		if(matrices[e][minx].vehiculo == 3){
			minx--;
		}else if(matrices[e][minx].vehiculo == 2){
			minx = minx - fila;
		}
	}

	ofstream tiempo;
	t = clock() - t;
	tiempo.open("Tiempo",ios::app);
	//tiempo << "Clocks: "<< (long int)t << " segundos: " << ((float)t)/CLOCKS_PER_SEC << endl;

	tiempo << etapas << ' ' << motos << ' ' << buggies << ' ' << (long int)t << endl;

	cout << i;

	for(e=1;e<=etapas;e++){
		cout << ' ' << tiempos[e].bmx;
	}

	cout << endl;

	for(e=0;e<=etapas;e++){
		free(matrices[e]);
	}

	free(matrices);
	free(tiempos);
}
