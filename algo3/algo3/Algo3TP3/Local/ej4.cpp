#include <iostream>
#include <vector>
#include <list>
#include "time.h"
#include <fstream>

using namespace std;

struct nodo{
	int toques;
	int adyEsDominado;
	int adyEsSolucion;
	bool esSolucion;
	bool visto;
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
int sacarConCamino(int n, grafo* graf, vector<int>* camino);
void resolver(vector<int>* camino, grafo* graf, vector<int>* mejorSolucion, int index, vector<int>* caminoInicial);
void tocarAdyacentes(int n, grafo* graf, bool dominado);
void sacarToque(int n, grafo* graf, bool dominado);
void busquedaLocal(vector<int>* camino, grafo* graf, vector<int>* mejorSolucion, vector<int> &solucionLocal, int dlogaritmo, int index, vector<int>* caminoInicial);
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
		nodos[i].toques = 0;
		nodos[i].adyEsDominado = 0;
		nodos[i].adyEsSolucion = 0;
		nodos[i].esSolucion = false;
		nodos[i].visto = false;
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
	vector<int> caminoInicial;
	vector<int> mejorSolucion;
	vector<int> solucionLocal;

	for(i=0; i<cantNodos; i++){
		if(nodos[i].adyacentes->size()){
			caminoInicial.push_back(i);
		}else{
			iniciales.push_back(i);
			graf->gradoZero++;
		}
	}


	if(caminoInicial.size()){

		int masGradoso = mayor(&caminoInicial, graf);

		while((graf->dominantes+graf->dominados) < caminoInicial.size()){
			agregar(masGradoso, graf);
			mejorSolucion.push_back(masGradoso);
			masGradoso = mayor(&caminoInicial, graf);
		}

		int nod = 1;
		int dlogaritmo = 0;

		while(nod<cantNodos){
			dlogaritmo++;
			nod = nod << 1;
		}

		do{
			solucionLocal = mejorSolucion;
			busquedaLocal(&camino, graf, &mejorSolucion, solucionLocal, dlogaritmo, 0, &caminoInicial);
		}while(mejorSolucion.size()<solucionLocal.size());
	}

	ofstream tiempo;
	t = clock() - t;
	tiempo.open("Tiempo",ios::app);
	tiempo << (long int) t << endl;

	cout << graf->gradoZero+solucionLocal.size();

	for(i=0; i<graf->gradoZero; i++){
		cout << ' ' << 'i' << iniciales[i]+1;
	}

	for(i=0; i<solucionLocal.size(); i++){
		cout << ' ' << 'i' << solucionLocal[i]+1;
	}

	cout << endl;

	for(i=0; i<cantNodos; i++){
		delete nodos[i].adyacentes;
	}

	delete graf;
}

void busquedaLocal(vector<int>* camino, grafo* graf, vector<int>* mejorSolucion, vector<int> &solucionLocal, int dlogaritmo, int index, vector<int>* caminoInicial){
	int cuantosSalieron;
	for(int i=index;i<solucionLocal.size();i++){

		cuantosSalieron = sacarConCamino(solucionLocal[i], graf, camino);
		if((cuantosSalieron < dlogaritmo) and (index+1 < solucionLocal.size())){
			busquedaLocal(camino, graf, mejorSolucion, solucionLocal, dlogaritmo-cuantosSalieron, index+1, caminoInicial);
		}else{
			resolver(camino, graf, mejorSolucion, 0, caminoInicial);
		}
		/*while(cuantosSalieron > 0){
			camino->pop_back();
			cuantosSalieron--;
		}*/
		camino->resize(camino->size()-cuantosSalieron);
		agregar(solucionLocal[i], graf);

	}

	return;
}

void resolver(vector<int>* camino, grafo* graf, vector<int>* mejorSolucion, int index, vector<int>* caminoInicial){

	int actual = camino->at(index);
	
	bool puedoPoner = (graf->nodos->at(actual).adyEsSolucion == 0);
	bool puedoNoPoner = (graf->nodos->at(actual).toques < graf->nodos->at(actual).adyacentes->size());

	int i = 0;
	int j;

	if(puedoPoner){
		while((puedoNoPoner) and (i < graf->nodos->at(actual).adyacentes->size())){
			j = graf->nodos->at(actual).adyacentes->at(i);
			puedoNoPoner = (!graf->nodos->at(j).visto) or (graf->nodos->at(j).toques+1 < graf->nodos->at(j).adyacentes->size());
			i++;
		}
	}

	if((puedoNoPoner) and (index+1 < camino->size())){

		if(puedoPoner){
			tocarAdyacentes(actual, graf, false);
		}

		graf->nodos->at(actual).visto = true;		

		resolver(camino, graf, mejorSolucion, index+1, caminoInicial);

		graf->nodos->at(actual).visto = false;

		if(puedoPoner){
			sacarToque(actual, graf, false);
		}
	}
	
	if(puedoPoner){
		
		agregar(actual, graf);

		if((graf->dominantes+graf->dominados+1) >= (graf->nodos->size()-graf->gradoZero)){
			if(graf->dominantes<mejorSolucion->size()){
				mejorSolucion->resize(0);
				for(i=0;i<caminoInicial->size();i++){
					j = caminoInicial->at(i);
					if((graf->nodos->at(j).esSolucion) or (graf->nodos->at(j).adyEsSolucion == 0)){
						mejorSolucion->push_back(j);
					}
				}
			}
		}else{
			if((graf->dominantes+1 < mejorSolucion->size()) and (index+1 < camino->size())){
				resolver(camino, graf, mejorSolucion, index+1, caminoInicial);
			}
		}
		sacar(actual, graf);
	 }

	return; 
}

void agregar(int n, grafo* graf){
	
	(*(graf->nodos))[n].esSolucion = true;

	graf->dominantes++;

	vector<int>* adyacentes = graf->nodos->at(n).adyacentes;

	for(int i=0; i<adyacentes->size();i++){
		if(graf->nodos->at(adyacentes->at(i)).adyEsSolucion == 0){
			graf->dominados++;
			tocarAdyacentes(adyacentes->at(i), graf, true);
		}
		graf->nodos->at(adyacentes->at(i)).adyEsSolucion++;
	}

	return;

}

void sacar(int n, grafo* graf){
	
	(*(graf->nodos))[n].esSolucion = false;

	graf->dominantes--;

	vector<int>* adyacentes = (*(graf->nodos))[n].adyacentes;

	for(int i=0; i<adyacentes->size();i++){
		(*(graf->nodos))[(*adyacentes)[i]].adyEsSolucion--;
		if(graf->nodos->at(adyacentes->at(i)).adyEsSolucion == 0){
			graf->dominados--;
			sacarToque(adyacentes->at(i), graf, true);
		}
	}

	return;
}

int sacarConCamino(int n, grafo* graf, vector<int>* camino){
	
	(*(graf->nodos))[n].esSolucion = false;

	int sol = 1;

	graf->dominantes--;
	camino->push_back(n);

	vector<int>* adyacentes = (*(graf->nodos))[n].adyacentes;

	for(int i=0; i<adyacentes->size();i++){
		(*(graf->nodos))[(*adyacentes)[i]].adyEsSolucion--;
		if(graf->nodos->at(adyacentes->at(i)).adyEsSolucion == 0){
			graf->dominados--;
			camino->push_back(adyacentes->at(i));
			sol++;
			sacarToque(adyacentes->at(i), graf, true);
		}
		
	}

	return sol;
}

void tocarAdyacentes(int n, grafo* graf, bool dominado){
	vector<int>* adyacentes = (*(graf->nodos))[n].adyacentes;

	if(dominado){
		if(!graf->nodos->at(n).visto){
			for(int i=0; i<adyacentes->size();i++){
			graf->nodos->at(adyacentes->at(i)).adyEsDominado++;
			((*(graf->nodos))[(*adyacentes)[i]]).toques++;
			}
		}else{
			for(int i=0; i<adyacentes->size();i++){
				graf->nodos->at(adyacentes->at(i)).adyEsDominado++;
			}
		}
	}else{
		for(int i=0; i<adyacentes->size();i++){
			((*(graf->nodos))[(*adyacentes)[i]]).toques++;
		}
	}

	return;
}

void sacarToque(int n, grafo* graf, bool dominado){
	vector<int>* adyacentes = (*(graf->nodos))[n].adyacentes;

	if(dominado){
		if(!graf->nodos->at(n).visto){
			for(int i=0; i<adyacentes->size();i++){
				graf->nodos->at(adyacentes->at(i)).adyEsDominado--;
				((*(graf->nodos))[(*adyacentes)[i]]).toques--;
			}
		}else{
			for(int i=0; i<adyacentes->size();i++){
				graf->nodos->at(adyacentes->at(i)).adyEsDominado--;
			}
		}
	}else{
		for(int i=0; i<adyacentes->size();i++){
			((*(graf->nodos))[(*adyacentes)[i]]).toques--;
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
