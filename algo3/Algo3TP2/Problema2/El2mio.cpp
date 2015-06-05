#include <iostream>
#include <stdlib.h>

using namespace std;

struct nodo{
	int sobrev;
	char viene_de;
	nodo(int a, char b){
		sobrev=a;
		viene_de=b;
	}
};

int cuantosZombies(int i, int j, char dir, int m, int zombies[][2]) { //Cuantos zombies al moverse "hacia" una esquina en un sentido
//zombies[i*m+j][0]=zombies(i,j,'R')=zombies(i,j+1,'L')
	if (dir=='L') return zombies[i*m+j][0];
	else if (dir=='R') return zombies[i*m+(j-1)][0];

//zombies[i*m+j][1]=zombies(i,j,'D')=zombies(i+1,j,'U')
	else if (dir=='U') return zombies[i*m+j][1];
	else if (dir=='D') return zombies[(i-1)*m+j][1];
}

int maximo(int cand[], int n) {
	int ind=0;
	int mx=cand[0];
	for(int i=1;i<n;i++) {
		if (cand[i]>mx) {
			mx=cand[i]; 
			ind=i;
		}
	} return ind;
}

int cuantosQuedan(int x, int y, char dir, nodo vieja[], int m, int zombies[][2]) {
	int habia=(vieja[y*m+x]).sobrev;
	int perdidas=cuantosZombies(y,x,dir,m,zombies)-habia;
	if (perdidas<0) perdidas=0;
	int res=habia-perdidas;
	if (res<0) res=0;
	return res;
	
}

void actualizar(nodo vieja[], nodo nueva[], int x, int y, int m, int n, int iter, int zombies[][2]) {
	if (x>0 or y>0) {
		int cand[4];
		for (int i=0;i<4;i++) cand[i]=-1;
		if ((x >= 1) and (x-1+y<=iter) and (x-1 <m) and (y<n))
			cand[0]=cuantosQuedan(x-1,y,'L',vieja,m,zombies);
		if ((x+y-1<=iter) and (x < m) and (y >= 1)  and (y-1<n))
			cand[1]=cuantosQuedan(x,y-1,'U',vieja,m,zombies);
		if ((x+1+y<=iter) and (x+1 < m) and (y<n))
			cand[2]=cuantosQuedan(x+1,y,'R',vieja,m,zombies);
		if ((x+y+1<=iter) and (x < m)  and (y+1<n))
			cand[3]=cuantosQuedan(x,y+1,'D',vieja,m,zombies);

		string dirs="LURD";
		int mn=maximo(cand,4);

		nueva[y*m+x]=nodo(cand[mn],dirs[mn]);
	}
}

void devolver(nodo matriz[], int f, int c) {
	for (int i=0;i<f;i++) {
		for (int j=0;j<c;j++)
			cout << '{' << matriz[i*c+j].sobrev << ',' << matriz[i*c+j].viene_de << "} ";
		cout << endl;
	} cout << endl;
}

int main(){
	
	int n,m,s;
	cin >> n >> m >> s;
	int ih,iv,bh,bv;
	cin >> ih >> iv >> bh >> bv;

	int zombies[n*m][2];

	for (int i=0;i<n-1;i++) {
		for (int j=0;j<m-1;j++)
			cin >> zombies[i*m+j][0];
		for (int j=0;j<m;j++)
			cin >> zombies[i*m+j][1];
	} for (int j=0;j<m-1;j++)
		cin >> zombies[(n-1)*m+j][0];

	nodo* vieja=(nodo*)malloc(n*m*8);
	nodo* nueva=(nodo*)malloc(n*m*8);
	nodo* swap;
	vieja[iv*m+ih]=nodo(s,'S');
	nueva[iv*m+ih]=nodo(s,'S');
	for(int i=0;i<n*m;i++){
		int x=ih-i;
		if (x<0) x=0;
		for (;x<=i && x<m;x++) {
			int y=iv-i;
			if (y<0) y=0;
			for (;(x+y)<=i && y<n;y++) {
				actualizar(vieja,nueva,x,y,m,n,i,zombies);
//				devolver(nueva,n,m);
				
			}
		}
//		devolver(nueva,n,m);
		swap=(nodo*)vieja;
		vieja=(nodo*)nueva;
		nueva=(nodo*)swap;
	}

	//buscar el camino y devolver (devolver probablemente tenga que ir aparte)
	if (vieja[bh*m+bv].sobrev==0) {cout << 0 << endl;return 0;}
	cout << vieja[bh*m+bv].sobrev << endl;

	int i=bv;
	int j=bh;
	char dir;
	int is[n*m];
	int js[n*m];
	int pasos;
	for (pasos=0;dir!='S';pasos++) {
		is[pasos]=i;
		js[pasos]=j;
		dir = vieja[i*m+j].viene_de;	
		if (dir=='L')
			j--;
		else if	(dir=='U')
			i--;
		else if (dir=='R')
			j++;
		else if (dir=='D')
			i++;
	}

	for (int i=0;i<pasos;i++)
		cout << is[i] << ' ' << js[i] << endl;

	free(vieja);
	free(nueva);

}
//el problema es la complejidad
