#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;

struct frec {
        int i;
        int inicio;
        int fin;
        int costo;
};

int min(int a, int b) {
    if (a<b) {
        return a;
    } else {
        return b;
    }
}

void aplanar(frec res[], int& posRes) { //Por si queda la misma frecuencia en dos intervalos adyacentes
        res[posRes-1].fin=res[posRes].fin;
        posRes--;
}

void completar(frec res[], frec src[], int posSrc, int limSrc, int& posRes) {
    int i;
    for (i=posRes+1;posSrc<limSrc;i++) {
        frec copy=src[posSrc];
        res[i]=copy;
        posSrc++;
        if (res[i].i==res[i-1].i) aplanar(res,i); //Puede pasar en la primera iteración
    } posRes=i-1;
}

int mergear(frec parA[], frec parB[], frec res[], int limA, int limB) {
        int posA=0;
        int posB=0;
	int posRes;
        for (posRes=0;posA<limA && posB<limB;posRes++) { 

                frec& a=parA[posA];
                frec& b=parB[posB]; //voy a comparar estas dos para saber con cuál quedarme en un intervalo

                int minActual=min(a.inicio,b.inicio);
                int proxCorte=min(a.fin,b.fin);

                if (a.inicio<proxCorte && (a.inicio)>minActual) proxCorte=a.inicio;
                if (b.inicio<proxCorte && (b.inicio)>minActual) proxCorte=b.inicio;

                ///ProxCorte: se transmite en una frecuencia hasta que termina o aparece otra.

                if ((a.costo<b.costo && a.inicio<proxCorte) || b.inicio>=proxCorte) {
                        res[posRes].i=a.i;
                        res[posRes].costo=a.costo;
                } else { 
                        res[posRes].i=b.i;
                        res[posRes].costo=b.costo;
                }

                if (a.inicio<proxCorte) a.inicio=proxCorte;
                if (b.inicio<proxCorte) b.inicio=proxCorte;

                if (a.fin==proxCorte) posA++;
                if (b.fin==proxCorte) posB++; //Si agotamos el tiempo de un intervalo, pasamos al siguiente

                res[posRes].inicio=minActual;
                res[posRes].fin=proxCorte;
                if (res[posRes].i==res[posRes-1].i && posRes>0) aplanar(res,posRes);

                if (posA==limA) completar(res, parB, posB, limB, posRes);
                else if (posB==limB) completar(res, parA, posA, limA, posRes);

        }
    return posRes;
}

int resolver(frec frecs[], frec res[], int rangoi, int rangof) {
    if (rangof==rangoi) {
        frec sol=frecs[rangoi];
        res[0]=sol;
        return 1;
    } else {
        frec par[(rangof-rangoi)*2+2];
        frec par2[(rangof-rangoi)*2+2];
        int pivot=(rangof+rangoi)/2;
        int limA=1;
        int limB=1;
        limA=resolver(frecs,par,rangoi,pivot);
	limB=resolver(frecs,par2,pivot+1,rangof);
        return mergear(par,par2,res,limA,limB);
    }
}


void devolver(frec res[], int cant) {
        for (int i=0;i<cant;i++) {
                cout << res[i].i << ' ';
                cout << res[i].inicio << ' ';
                cout << res[i].fin << ' ';
                cout << endl;
        } cout << "-1" << endl;
}

int main() {
    int cant;
    cin >> cant;
    frec frecuencias[cant];
    for (int i=0;i<cant;i++) {
        frecuencias[i].i=i;
        cin >> frecuencias[i].costo;
        cin >> frecuencias[i].inicio;
        cin >> frecuencias[i].fin;
    }

    frec res[2*cant+2];

    clock_t t;
    t = clock();

    int cortes=resolver(frecuencias, res,0,cant-1);

	int total=0;
	for (int i=0;i<cant;i++) {
	       total+=(res[i].costo)*(res[i].fin-res[i].inicio);
	}

    /*ofstream tiempo;
    t = clock() - t;
    tiempo.open("Tiempo",ios::app);
    tiempo << "Clocks: "<< (long int)t << " segundos: " << ((float)t)/CLOCKS_PER_SEC << endl;


    ofstream tam;
    tam.open("Tam",ios::app);
    tam << cortes << endl;

    ofstream mins;
    mins.open("Mins",ios::app);
    mins << res[cortes-1].fin-res[0].inicio << endl;*/

	cout << total << endl;
    devolver(res,cortes);
}
