#include <iostream>
#include <stdlib.h>
#include <list>
#include <queue>
#include <vector>

using namespace std;

struct nodo{
	pair<int, int> esquina;
	int sobreviven;
	pair<int, int> pred;
	int zombiesEnElCamino;
	nodo(pair<int, int> esq, int s, pair<int, int> p, int z){
		esquina = esq;
		sobreviven = s;
		pred = p;
		zombiesEnElCamino = z;
	}
};

struct direcciones {
	nodo Arr; nodo Aba; nodo Izq; nodo Der;
};

vector<vector<direcciones> > listaDeAdyacencia(int H[], int V[], int n, int m){
	vector<vector<direcciones> > LDA(n);//[n][m];
	for (int i=0;i<n;i++) LDA.resize(m);


	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(i-1 >= 0){
				LDA[i][j].Arr = nodo(make_pair(i-1, j), -1, make_pair(i,j), V[(i-1)*m+j]);
			}
			if(i+1 <= n-1){
				LDA[i][j].Aba = nodo(make_pair(i+1, j), -1, make_pair(i,j), V[i*m+j]);
			}
			if(j-1 >= 0){
				LDA[i][j].Izq = nodo(make_pair(i, j-1), -1, make_pair(i,j), H[i*(m-1)+j-1]);
			}
			if(j+1 <=m-1){
				LDA[i][j].Der = nodo(make_pair(i, j+1), -1, make_pair(i,j), H[i*(m-1)+j]);
			}
		}
	} return LDA;
}

bool BFS(vector<vector<direcciones> > grafo, int n, int m, int ih, int iv, int bh, int bv, int soldados){ 
	queue<nodo> cola;
	cola.push(nodo(make_pair(ih,iv),soldados,make_pair(-1,-1),0));
	while (!cola.empty()) {
		nodo nodoAEvaluar=cola.front();

		//Chequear si llegas al bunker
		if (nodoAEvaluar.esquina==make_pair(bh,bv)) {
			return true;
		}

		cola.pop();
		direcciones vecinos=grafo[nodoAEvaluar.esquina.first][nodoAEvaluar.esquina.second];
		if(i-1 >= 0){ //y no hay demasiados zombies
//			vecinos.Arr.sobreviven=
			cola.push(vecinos.Arr); 
		}
		if(i+1 <= n-1){
			cola.push(vecinos.Aba);
		}
		if(j-1 >= 0){	
			cola.push(vecinos.Izq);
		}
		if(j+1 <=m-1){
			cola.push(vecinos.Der);
		}		
	} return false;
	//Hay q ver si están indexadas desde cero.
	
}

vector<pair <int, int> > BFSrecover(vector<vector<direcciones> > grafoZombie, int n , int m, int ih, int iv, int bh, int bv, int i) {
}

int main(){
	//Cargar
	int n,m,s; //Calles Horizontales, Verticales y Soldados
	cin >> n >> m >> s;
	int ih,iv,bh,bv; //Ih Iv calle inicial, Bh Bv bunker
	cin >> ih >> iv >> bh >> bv;

	int zombiesH[n*(m-1)]; //Zombies en las Calles Horizontales
	int zombiesV[(n-1)*m]; //Zombies en las Calles Verticales
	for (int i=0;i<n-1;i++) {
		for (int j=0;j<m-1;j++)
			cin >> zombiesH[i*(m-1)+j];
		for (int j=0;j<m;j++)
			cin >> zombiesV[i*m+j];
	} 
	/*for (int j=0;j<m-1;j++){
		cin >> zombies[(n-1)*(m-1)+j][0];
	}*/
	//Crear Grafo
	vector<vector <direcciones> > grafoZombie = listaDeAdyacencia(zombiesH, zombiesV, n, m);
	//BFS por cantidad de Soldados
	bool existe;
	int vivos;
	list<nodo> l;
	for(int i=0;i<=s; i++){
		
		existe = BFS(grafoZombie, n, m, ih, iv, bh, bv, i); //devuelve 0 si no existe camino minimo  y 1 si existe. Tal vez convenga que se pase por copia.
		if(existe){
			vector<pair <int, int> > caminoMinimo = BFSrecover(grafoZombie, n ,m, ih, iv, bh, bv, i);
			vivos = s-i;
			break;
		}
	}
	if(existe){
		//devolver vivos y caminoMinimo;
	} else {
		return 0;
	}
	
}
