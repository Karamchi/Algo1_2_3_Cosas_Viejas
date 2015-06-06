#include <cstdio>
#include <cstdlib>
#include <vector>
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

void aplanar(vector<frec>& res, int& posRes) { //Por si queda la misma frecuencia en dos intervalos adyacentes
        res[posRes-1].fin=res[posRes].fin;
        posRes--;
}

void completar(vector<frec>& res, vector<frec>& src, int posSrc, int limSrc, int& posRes, int& total) {
    int i;
    for (i=posRes+1;posSrc<limSrc;i++) {
        frec copy=src[posSrc];
        res[i]=copy;
        posSrc++;
        total+=(copy.costo)*(copy.fin-copy.inicio);
        if (res[i].i==res[i-1].i) aplanar(res,i); //Puede pasar en la primera iteración
    } posRes=i-1;
}

int mergear(vector<frec>& parA,vector<frec>& parB, vector<frec>& res, int limA, int limB, int& posRes) {
        int posA=0;
        int posB=0;
        int total=0;
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
                        total+=(a.costo)*(proxCorte-minActual);
                } else { 
                        res[posRes].i=b.i;
                        res[posRes].costo=b.costo;
                        total+=(b.costo)*(proxCorte-minActual);
                }

                if (a.inicio<proxCorte) a.inicio=proxCorte;
                if (b.inicio<proxCorte) b.inicio=proxCorte;

                if (a.fin==proxCorte) posA++;
                if (b.fin==proxCorte) posB++; //Si agotamos el tiempo de un intervalo, pasamos al siguiente

                res[posRes].inicio=minActual;
                res[posRes].fin=proxCorte;
                if (res[posRes].i==res[posRes-1].i && posRes>0) aplanar(res,posRes);

                if (posA==limA) completar(res, parB, posB, limB, posRes, total);
                else if (posB==limB) completar(res, parA, posA, limA, posRes, total);

        }
    return total;
}

int resolver(vector<frec>& frecs, vector<frec>& res, int rangoi, int rangof, int& cortes) {
    if (rangof==rangoi) {
        frec sol=frecs[rangoi];
        res[0]=sol;
        return (sol.costo)*(sol.fin-sol.inicio);
    } else {
        vector<frec> par ((rangof-rangoi)*2+2);
        vector<frec> par2((rangof-rangoi)*2+2);
        int pivot=(rangof+rangoi)/2;
        int limA=1;
        int limB=1;
        resolver(frecs,par,rangoi,pivot,limA);
        resolver(frecs,par2,pivot+1,rangof,limB);
        return mergear(par,par2,res,limA,limB,cortes);
    }
}


void devolver(vector<frec>& res, int cant) {
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
    vector<frec> frecuencias(cant);
    for (int i=0;i<cant;i++) {
        frecuencias[i].i=i;
        cin >> frecuencias[i].costo;
        cin >> frecuencias[i].inicio;
        cin >> frecuencias[i].fin;
    }

    vector<frec> res(2*cant+2);
    int cortes=1;

    clock_t t;
    t = clock();

    int tot=resolver(frecuencias, res,0,cant-1, cortes);
    
    ofstream tiempo;
    t = clock() - t;
    tiempo.open("Tiempo",ios::app);
    tiempo << (long int)t << endl;


    /*ofstream tam;
    tam.open("Tam",ios::app);
    tam << cortes << endl;

    ofstream mins;
    mins.open("Mins",ios::app);
    mins << res[cortes-1].fin-res[0].inicio << endl;*/

    cout << tot << endl;
    devolver(res,cortes);
}
