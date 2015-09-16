#include <iostream>
#include <vector>
#include <list>
#include "time.h"
#include <fstream>

using namespace std;

struct nodo{
	int adyEsDominado;
	int adyEsSolucion;
	bool esSolucion;
	vector<int>* adyacentes;
};

struct grafo{
	int dominados;
	int dominantes;
	int gradoZero;
	vector<nodo>* nodos;
};


void agregar(int n, grafo* graf);
void sacar(int n, grafo* graf);
int mayor(vector<int>* camino, grafo* graf);

int main(){
	int cantNodos;
	int cantAristas;

	cin >> cantNodos;
	cin >> cantAristas;

	vector<nodo> nodos (cantNodos);

	grafo* graf = new grafo;

	graf->nodos = &nodos;
	graf->dominados = 0;
	graf->dominantes = 0;
	graf->gradoZero = 0;

	int i;

	for(i=0; i<cantNodos; i++){
		nodos[i].adyEsDominado = 0;
		nodos[i].adyEsSolucion = 0;
		nodos[i].esSolucion = false;
		nodos[i].adyacentes = new vector<int> (0);
	}

	int j;

	while(cantAristas>0){

		cin >> i;
		cin >> j;

		i--;
		j--;

		nodos[i].adyacentes->push_back(j);

		nodos[j].adyacentes->push_back(i);

		cantAristas--;

	}

	clock_t t = clock();

	vector<int> iniciales;
	vector<int> camino;
	vector<int> solucion;

	for(i=0; i<cantNodos; i++){
		if(nodos[i].adyacentes->size()){
			camino.push_back(i);
		}else{
			iniciales.push_back(i);
			graf->gradoZero++;
		}
	}

	if(camino.size()){

		int masGradoso = mayor(&camino, graf);

		while((graf->dominantes+graf->dominados) < camino.size()){
			agregar(masGradoso, graf);
			solucion.push_back(masGradoso);
			masGradoso = mayor(&camino, graf);
		}

	}

	ofstream tiempo;
	t = clock() - t;
	tiempo.open("Tiempo",ios::app);
	tiempo << (long int) t << endl;

	cout << graf->gradoZero+solucion.size();

	for(i=0; i<graf->gradoZero; i++){
		cout << ' ' << 'i' << iniciales[i]+1;
	}

	for(i=0; i<solucion.size(); i++){
		cout << ' ' << 'i' << solucion[i]+1;
	}

	cout << endl;

	for(i=0; i<cantNodos; i++){
		delete nodos[i].adyacentes;
	}

	delete graf;
}

void agregar(int n, grafo* graf){
	
	(*(graf->nodos))[n].esSolucion = true;

	graf->dominantes++;

	vector<int>* adyacentes = graf->nodos->at(n).adyacentes;
	vector<int>* adyacentesPrimos;

	int j;

	for(int i=0; i<adyacentes->size();i++){
		if(graf->nodos->at(adyacentes->at(i)).adyEsSolucion == 0){
			graf->dominados++;
			adyacentesPrimos = (*(graf->nodos))[adyacentes->at(i)].adyacentes;
			for(j=0; j<adyacentesPrimos->size();j++){
				graf->nodos->at(adyacentesPrimos->at(j)).adyEsDominado++;
			}
		}
		graf->nodos->at(adyacentes->at(i)).adyEsSolucion++;
	}

	return;

}

void sacar(int n, grafo* graf){
	
	(*(graf->nodos))[n].esSolucion = false;

	graf->dominantes--;

	vector<int>* adyacentes = (*(graf->nodos))[n].adyacentes;
	vector<int>* adyacentesPrimos;

	int j;

	for(int i=0; i<adyacentes->size();i++){
		(*(graf->nodos))[(*adyacentes)[i]].adyEsSolucion--;
		if(graf->nodos->at(adyacentes->at(i)).adyEsSolucion == 0){
			graf->dominados--;
			adyacentesPrimos = (*(graf->nodos))[adyacentes->at(i)].adyacentes;
			for(j=0; j<adyacentesPrimos->size();j++){
				graf->nodos->at(adyacentesPrimos->at(j)).adyEsDominado--;
			}
		}
	}

	return;
}

int mayor(vector<int>* camino, grafo* graf){

	int maxGrado = -1;
	int maxNodo = -1;
	int grado;

	int j = camino->at(0);

	if((!graf->nodos->at(j).esSolucion) and (graf->nodos->at(j).adyEsSolucion == 0)){
		maxGrado = (graf->nodos->at(j).adyacentes->size() - graf->nodos->at(j).adyEsDominado);
		maxNodo = 0;
	}

	for(int i=1; i < camino->size(); i++){
		j = camino->at(i);
		if((!graf->nodos->at(j).esSolucion) and (graf->nodos->at(j).adyEsSolucion == 0)){
			grado = ((graf->nodos->at(j)).adyacentes->size() - graf->nodos->at(j).adyEsDominado);
			if(grado>maxGrado){
				maxNodo = j;
				maxGrado = grado;
			}
		}
	}

	return maxNodo;
}
