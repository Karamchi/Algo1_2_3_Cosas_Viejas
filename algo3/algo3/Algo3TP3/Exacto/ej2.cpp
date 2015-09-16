#include <iostream>
#include <vector>
#include <list>
#include "time.h"
#include <fstream>
#include "malloc.h"

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
void resolver(vector<int>* camino, grafo* graf, vector<int>* mejorSolucion, int index);
void tocarAdyacentes(int n, grafo* graf, bool dominado);
void sacarToque(int n, grafo* graf, bool dominado);
int saleAlguno(grafo* graf);
void swap(vector<int> &array, int* swap_place, int x, int y);
void sort_heap(vector<int> &array, vector<nodo>* nodos);
void heapify(vector<int> &array, vector<nodo>* nodos);
void heap_bajar(vector<int> &array, vector<nodo>* nodos);

bool comp(int a, int b, grafo* graf){
	int gradoA = graf->nodos->at(a).adyacentes->size() - graf->nodos->at(a).adyEsSolucion - graf->nodos->at(a).adyEsDominado;
	int gradoB = graf->nodos->at(b).adyacentes->size() - graf->nodos->at(b).adyEsSolucion - graf->nodos->at(b).adyEsDominado;

	if(gradoA<gradoB){
		return true;
	}else{
		return false;
	}
}

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
	vector<int> mejorSolucion;

	for(i=0; i<cantNodos; i++){
		if(nodos[i].adyacentes->size()){
			camino.push_back(i);
		}else{
			iniciales.push_back(i);
			graf->gradoZero++;
		}
	}

	/*heapify(camino, &nodos);

	sort_heap(camino, &nodos);

	for(i=0; i<camino.size(); i++){
		cout << camino[i] << ' ';
	}

	cout << endl << endl;*/

	//int cota = min(((cantNodos-graf->gradoZero)/2), (cantNodos - graf->gradoZero - graf->dominados));

	int cota = cantNodos-graf->gradoZero;

	if(camino.size()){
		mejorSolucion.resize(cota);
		resolver(&camino, graf, &mejorSolucion, 0);
	}

	ofstream tiempo;
	t = clock() - t;
	tiempo.open("Tiempo",ios::app);
	tiempo << (long int) t << endl;

	cout << graf->gradoZero+mejorSolucion.size();

	for(i=0; i<graf->gradoZero; i++){
		cout << ' ' << 'i' << iniciales[i]+1;
	}

	for(i=0; i<mejorSolucion.size(); i++){
		cout << ' ' << 'i' << mejorSolucion[i]+1;
	}

	cout << endl;

	for(i=0; i<cantNodos; i++){
		
		delete nodos[i].adyacentes;
	}

	delete graf;
}

void resolver(vector<int>* camino, grafo* graf, vector<int>* mejorSolucion, int index){

	int actual = camino->at(index);
	
	bool puedoPoner = ((!graf->nodos->at(actual).esSolucion) and (graf->nodos->at(actual).adyEsSolucion == 0));
	bool puedoNoPoner = (graf->nodos->at(actual).toques <= graf->nodos->at(actual).adyacentes->size());

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

		graf->nodos->at(j).visto = true;

		tocarAdyacentes(actual, graf, false);

		resolver(camino, graf, mejorSolucion, index+1);

		sacarToque(actual, graf, false);

		graf->nodos->at(j).visto = false;
	}
	
	if(puedoPoner){

		agregar(actual, graf);

		if((graf->dominantes+graf->dominados+1) >= camino->size()){
			
			if(graf->dominantes<mejorSolucion->size()){
				mejorSolucion->resize(0);

				for(i=0;i<camino->size();i++){
					j = camino->at(i);
					if((graf->nodos->at(j).esSolucion) or (graf->nodos->at(j).adyEsSolucion == 0)){
						mejorSolucion->push_back(j);
					}
				}
			}
		}else{
			if((graf->dominantes+1 < mejorSolucion->size()) and (index+1 < camino->size())){
				resolver(camino, graf, mejorSolucion, index+1);
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

void tocarAdyacentes(int n, grafo* graf, bool dominado){
	vector<int>* adyacentes = (*(graf->nodos))[n].adyacentes;

	if(dominado){
		for(int i=0; i<adyacentes->size();i++){
			graf->nodos->at(adyacentes->at(i)).adyEsDominado++;
			((*(graf->nodos))[(*adyacentes)[i]]).toques++;
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
		for(int i=0; i<adyacentes->size();i++){
			graf->nodos->at(adyacentes->at(i)).adyEsDominado--;
			((*(graf->nodos))[(*adyacentes)[i]]).toques--;
		}
	}else{
		for(int i=0; i<adyacentes->size();i++){
			((*(graf->nodos))[(*adyacentes)[i]]).toques--;
		}
	}

	return;
}

void heapify(vector<int> &array, vector<nodo>* nodos){
    int j = (array.size()-2)/2;
    int i;
    int izq;
    int der;
    int* swap_place = (int*) malloc(8);
    while(j>=0){
        i = j;
        izq = i*2+1;
        der = izq+1;
        while(izq<array.size()){
            if((der >= array.size()) or (((nodos->at(array[izq])).adyacentes->size()) < (nodos->at(array[der]).adyacentes->size()))){
                if((nodos->at(array[i]).adyacentes->size())>(nodos->at(array[izq]).adyacentes->size())){
                    swap(array, swap_place, i, izq);
                    i = izq;
                    izq = i*2+1;
                    der = izq+1;
                }else{
                    izq = array.size();
                }
            }else{
                if((nodos->at(array[i]).adyacentes->size())>(nodos->at(array[der]).adyacentes->size())){
                    swap(array, swap_place, i, der);
                    i = der;
                    izq = i*2+1;
                    der = izq+1;
                }else{
                    izq = array.size();
                }
            }
        }
        j--;        
    }
    return;
}

//Esta funcion restablece el invariante de un heap

void heap_bajar(vector<int> &array, vector<nodo>* nodos){
    int* swap_place = (int*) malloc(8);
    int i = 0;
    int izq = 1;
    int der = 2;
    while(izq<array.size()){
        if((der>=array.size()) or ((nodos->at(array[izq]).adyacentes->size())<(nodos->at(array[der]).adyacentes->size()))){
            if((nodos->at(array[izq]).adyacentes->size())<(nodos->at(array[i]).adyacentes->size())){
                swap(array, swap_place, i, izq);
                i = izq;
                izq = i*2+1;
                der = izq+1;
            }else{
                izq = array.size();
            }               
        }else{
            if((nodos->at(array[der]).adyacentes->size())<(nodos->at(array[i]).adyacentes->size())){
                swap(array, swap_place, i, der);
                i = der;
                izq = i*2+1;
                der = izq+1;
            }else{
                izq = array.size();
            }
        }
    }
}

//Segunda mitad del HeapSort, al final no lo usamos

void sort_heap(vector<int> &array, vector<nodo>* nodos){
    int* swap_place = (int*) malloc(8);
    int k = array.size();
    while(k>0){
        k--;
        swap(array, swap_place, 0, k);
        heap_bajar(array, nodos);
        }
    }


void swap(vector<int> &array, int* swap_place, int x, int y){
    swap_place[0] = array[x];
    array[x] = array[y];
    array[y] = swap_place[0];
}

int saleAlguno(grafo* graf){

	int maxGrado = -1;
	int maxNodo = -1;
	int grado;

	if((!graf->nodos->at(0).esSolucion) and (graf->nodos->at(0).adyEsSolucion == 0)){
		maxGrado = (graf->nodos->at(0).adyacentes->size() - graf->nodos->at(0).adyEsSolucion - graf->nodos->at(0).adyEsDominado);
		if(maxGrado){
			maxNodo = 0;
		}
	}

	for(int i=1; i < graf->nodos->size(); i++){
		if((!graf->nodos->at(i).esSolucion) and (graf->nodos->at(i).adyEsSolucion == 0)){
			grado = graf->nodos->at(i).adyacentes->size() - graf->nodos->at(i).adyEsSolucion - graf->nodos->at(i).adyEsDominado;
			if(grado>maxGrado){
				maxNodo = i;
				maxGrado = grado;
			}
		}
	}

	int cantNodos = graf->nodos->size() - (graf->dominados + graf->dominantes + graf->gradoZero);

	if((maxGrado*2) >= cantNodos){
		return maxNodo;
	}

	return -1;
}
