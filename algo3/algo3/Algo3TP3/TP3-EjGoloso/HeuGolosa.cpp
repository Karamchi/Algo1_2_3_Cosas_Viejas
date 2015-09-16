#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <assert.h>
#include <time.h>

using namespace std;

struct nodoGr {
	list<int> adyacentes;
	bool enDominio; //Si ya está en el res o alguien de res es adyacente a él.  
	int grado;  
};

void printLDA(vector<nodoGr> &LDA, int n, int m);
int mayorGrado(vector<nodoGr> &LDA, int sizeVector);
void sacarNodoYVecinos(vector<nodoGr> &LDA,int &n, int maxNodo);
void sacarNodo(vector<nodoGr> &LDA, int nodo);
void printList(list<int> res);

int main(){
	
	//Cargar
	int n, m; //vertices y aristas de G
	cin >> n >> m;
	vector<nodoGr> LDA (n);//Lista de Adyacencia
	int u, v; //extremos de la arista
	for (int i=0; i<m; i++){
		cin >> u >> v;
		LDA[u-1].adyacentes.push_back(v);
		LDA[v-1].adyacentes.push_back(u);
	}
	for (int i=0; i<n; i++){
		LDA[i].enDominio = false;
		LDA[i].grado = LDA[i].adyacentes.size();
	}
	list<int> res;//Los vertices de la CIDM
	//Terminado el cargado

    clock_t t;
    t = clock();
	
	//Prueba imprimir la LDA
	//printLDA(LDA, n, m);
	//Termina Prueba
	
	//Heuristica Golosa
	int sizeVector = n;
	int maxNodo; //Nodo con mayor grado
	while(n!=0){
		maxNodo = mayorGrado(LDA,sizeVector); //maxNodo indexado desde 1 a n
		res.push_back(maxNodo);
		sacarNodoYVecinos(LDA,n,maxNodo); //versión que disminuye los grados en vez de sacarlos
	}
	//Termina Heuristica Golosa
	
	ofstream tiempo;
	t = clock() - t;
	tiempo.open("Tiempo",ios::app);
	tiempo << (long int)t << endl;

	//Devuelvo el Res
	cout << res.size() << ' ';
	printList(res);
	//Termino
	
	return 0;	
}

void printLDA(vector<nodoGr> &LDA, int n, int m){
	cout << n << ' ' << m << endl;
	for (int i=0; i<n; i++){
		cout << i+1 << ' ';
		for (list<int>::iterator it = LDA[i].adyacentes.begin(); it != LDA[i].adyacentes.end(); it++){
			cout << *it << ' ';
		}
		cout << endl;
	}
}

int mayorGrado(vector<nodoGr> &LDA, int sizeVector){
	int maxNodo;
	int gradoMax = -1;
	for (int i=0; i<sizeVector; i++){
		if (LDA[i].enDominio == false){
			if (LDA[i].grado > gradoMax){
				gradoMax = LDA[i].grado;
				maxNodo = i+1;
			}
		}
	}
	return maxNodo;
}

void sacarNodoYVecinos(vector<nodoGr> &LDA,int &n, int maxNodo){
	//maxNodo-1 es la posición del nodo a sacar!
	int nodosAdyaNoEnDom = 0;
	for (list<int>::iterator it = LDA[maxNodo-1].adyacentes.begin(); it != LDA[maxNodo-1].adyacentes.end(); it++){//si el nodo adyacente estaba enDominio, entonces no hay que volver a sacarlo
		if(LDA[(*it)-1].enDominio == false){
			sacarNodo(LDA, *it); //saca el nodo y sus aristas, incluso lo saca de LDA[maxNodo-1].adyacentes.
			nodosAdyaNoEnDom++;
		}
	}
	assert(LDA[maxNodo-1].grado == 0);
	LDA[maxNodo-1].enDominio = true;
	n = n-(nodosAdyaNoEnDom+1); //cantidad de nodos no enDominio.
}

void sacarNodo(vector<nodoGr> &LDA, int nodo){//reduce el grado de los vecinos al nodo y marca como enDominio a nodo.
	for (list<int>::iterator it = LDA[nodo-1].adyacentes.begin(); it != LDA[nodo-1].adyacentes.end(); it++){
		if(LDA[(*it)-1].enDominio == false){
			LDA[(*it)-1].grado--;
			LDA[nodo-1].grado--;
		}
	}
	assert(LDA[nodo-1].grado == 0);
	LDA[nodo-1].enDominio = true;
}

void printList(list<int> res){
	for (list<int>::iterator it = res.begin(); it != res.end(); it++){
		cout << *it << ' ';
	}
	cout << endl;
}
