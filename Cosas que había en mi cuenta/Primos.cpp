#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

int raiz(const long long a) {
    for (int i=0;i<=a;i++){
        if (i*i==a){
            return i;
        }
    } return 0;
}

bool esPrimo(long b) {
    if (b<0) {
        b=-b;
    } for (int c=2;c<=sqrt(b);c++){
        if (b%c==0){
            return false;
        }
    } return true;
}

int sumar(const int a[], const int n) {
    int res=0;
    for (int i=0;i<n;i++) {
        res+=a[i];
    } return res;
}

void porx(int arr[], const int x, const int n){
    int carry=0;
    for (int i=1;i<=n;i++) {
        arr[n-i]=arr[n-i]*x+carry;
        carry=0;
        while (arr[n-i]>=10) {
            arr[n-i]=arr[n-i]-10;
            carry++;
        }
    }
}

int sumaDiv(const int n) {
    int div=1;
    for (int i=2;i<=sqrt(n);i++) {
        if (n%i==0) {
            div=div+i;
            if (i*i!=n) {
                div=div+n/i;
            }
        }
    } return div;
}

int problema21(){
    int acum=0;
    for (int i=2;i<=10000;i++) {
        int sumadiv=sumaDiv(i);
        if (i!=sumadiv) {
            int reciproco=sumaDiv(sumadiv);
            if (i==reciproco) {
                cout << i << '\t' << sumadiv << endl;
                acum += i;
            }
        }
    } return acum;
};

bool esAbundante(const int n) {
    int div=sumaDiv(n);
    if (div>n) {
        return true;
    } return false;
}

bool Nosumade2Ab(const int x) {
    for (int i=1;i<=x/2;i++) {
        if (esAbundante(i) && esAbundante(x-i)){
            return false;
        }
    } return true;
}

int problema23(int l){
    int suma=0;
    for (int i=1;i<=l;i++) {
        if (Nosumade2Ab(i)) {
            cout << i << endl;
            suma=suma+i;
        }
    } return suma;
}

long long potencia(const int a,const int b){
    unsigned long long res=1;
    for (int i=1;i<=b;i++){
        //cout << res << " ";
        res=res*a;
    } return res;
}

void incrementar(int arr[], const int n) {
    int carry=1;
    for (int i=0;i<=n-1;i++) {
        arr[n-1-i]=arr[n-1-i]+carry;
        if (arr[n-1-i]>=10) {
            arr[n-1-i]=arr[n-1-i]-10;
            carry=1;
        } else {
            carry=0;
            i=n;
        }
    }
}

int cifras(const int arr[], const int n) {
    int i=0;
    while (arr[i]==0) {i++;}
    return n-i;
}

void devolver(const int arr[], const int n) {
    for (int i=n-cifras(arr,n);i<n;i++) {
        cout << arr[i];
    } //cout << endl;
}

bool sinRepes(const int arr[]) {
    int contados[10];
    int ncontados=0;
    for (int i=0;i<10;i++) {
        for (int j=0;j<ncontados;j++){
            if (arr[i]==contados[j]) {
                return false;
            }
        } contados[ncontados]=arr[i];
        ncontados++;
    } return true;
}

void problema24(){
    int n[10];
    for (int i=0;i<10;i++) {n[i]=i;}
    long lim=potencia(10,6);
    int con=0;int temp;
    while (con<=lim) {
        if (sinRepes(n)){
            con++;
            if (con%10000==0) {
                cout << con << ": ";
                devolver(n,10);
            } if (n[8]<n[9]) {
                temp=n[8];
                n[8]=n[9];
                n[9]=temp;
            } else {
                incrementar(n,10);
            }
        } else {
            incrementar(n,10);
        }
    }
};

bool estaArr(const int arr[], const int elem, const int n) {
    for (int i=0;i<n;i++) {
        if (arr[i]==elem) {
            return true;
        }
    } return false;
}

//(26) reciproco: devuelve el período de 1/n

//(27) pricos: primos consecutivos generados por x^2+ax+b

bool iguales(const int p[], const int q[]) {
    for (int i=0;i<25;i++) {
        if (p[i]!=q[i]) {
            return false;
        }
    } return true;
}

bool esta(const int p[], const int todos[][25], const int res) {
    for (int i=0;i<res;i++) {
        if (iguales(p,todos[i])) {
            return true;
        }
    } return false;
}

void descomponer(int n, const int e, int p[], const int primos[]) {
    for (int i=0;i<25;i++) {p[i]=0;}
    for (int i=0;i<25;i++) {
        if (n%primos[i]==0) {
            p[i]+=e;
            n=n/primos[i];
            i--;
        }
    }
}

void problema29() {
    int primos[25];
    int pos=0;
    for (int i=2;i<100;i++) {
        if (esPrimo(i)) {
            primos[pos]=i;
            pos++;
        }
    } int todos[9801][25];
    int res=0;
    int p[25];
    for (int i=2;i<=100;i++) {
        for (int j=2;j<=100;j++) {
            descomponer(i,j,p,primos);
            if (!esta(p,todos,res)) {
                cout << res+1 << ": " ;
                for (int x=0;x<25;x++) {
                    todos[res][x]=p[x];
                    cout << p[x] << " ";
                } cout << endl;
                res++;
            }
        }
    }
} //764ms

long arr2long(const int arr[], const int n) {
    long res=0;
    for (int i=1;i<=n;i++) {
        res+=arr[n-i]*potencia(10,i-1);
    } return res;
}

void concatenar(int r[], int q[], const int tamr, const int tamq) {
    int n=cifras(q,tamq);
    for (int i=0;i<tamr-n;i++) {
        r[i]=r[i+n];
    } for (int i=tamr-n;i<tamr;i++) {
        r[i]=q[i-(tamr-tamq)];
    }
}

bool pandigital(const int arr[], const int n) {
    int c=cifras(arr,n);
    for (int i=n-c;i<n;i++) {
        if (arr[i]==0 || arr[i]>c) {
            return false;
        }
    } int usados[c];
    int j=0;
    for (int i=n-c;i<n;i++) {
        for (int k=0;k<j;k++) {
            if (usados[k]==arr[i]) {
                return false;
            }
        } usados[j]=arr[i];
        j++;
    } return true;
}

void producto(const int p[], const int q[], int r[], const int n){
    for(int i=0;i<n;i++){r[i]=0;}
    for(int i=0;i<n;i++) {
        for (int j=0;j<n;j++) {
            if (n-((n-i)+(n-j))+1>0) {
                r[n-((n-i)+(n-j))+1] += (p[i]*q[j]);
            }
        }
    } porx(r,1,n);
}

void problema32() {
    int p[9];for(int i=0;i<9;i++){p[i]=0;}
    p[8]=1;
    int q[9];
    int r[9];
    long lim=31427;
    for (int i=0;i<lim;i++) {
        for (int k=0;k<9;k++){q[k]=p[k];}
        int n=0;
        for (int j=i;n<=9;j++) {
            producto(p,q,r,9);
            n=cifras(p,9)+cifras(q,9)+cifras(r,9);
            if (n==9) {
                concatenar(r,q,9,9);
                concatenar(r,p,9,9);
                if (pandigital(r,9)) {
                    cout << arr2long(p,9)*arr2long(q,9) << endl;
                }
            } incrementar(q,9);
        } incrementar(p,9);
    }
}

long factorial(const int i) {
    int res=1;
    for (int j=2;j<=i;j++) {
        res=res*j;
    } return res;
}

void problema34() {
    int p[7];for (int i=0;i<7;i++) {p[i]=0;}
    p[6]=1;
    long lim=7*factorial(9);
    for (long i=1;i<lim;i++) {
        long sumafact=0;
        for (int j=7-cifras(p,7);j<7;j++) {
            sumafact+=factorial(p[j]);
        }
        if (sumafact==i) {
            devolver(p,7);
        } incrementar(p,7);
    }
}

void rotar (int arr[], const int n) {
    int temp=arr[6-n];
    for (int i=6-n;i<6;i++) {
        arr[i]=arr[i+1];
    } arr[5]=temp;
}

bool circular (int p[]){
    int q[6]; for (int i=0;i<6;i++) {q[i]=p[i];}
    int n=cifras(p,6);
    for (int j=0;j<n+1;j++) {
        if (!esPrimo(arr2long(p,6))) {
            for (int i=0;i<6;i++) {p[i]=q[i];}
            return false;
        } rotar(p, n);
    } for (int i=0;i<6;i++) {p[i]=q[i];}
    return true;
}

void problema35() {
    int con=0;
    int p[6]; for (int i=0;i<6;i++) {p[i]=0;}
    p[5]=2;
    long lim=potencia(10,6);
    for (int i=2;i<lim;i++) {
        if (circular(p)) {
            con++;
            cout << con << " " << i << endl;
        } incrementar(p,6);
    }
}

bool esPalindromo(const int a[], const int n) {
    int lim=cifras(a,n);
    for (int i=0;i<lim;i++) {
        if (a[n-i-1]!=a[n-(lim-i)]) {
            return false;
        }
    } return true;
}

void bin2arr(const int a[], int b[], const int n) {
    for (int i=0;i<n;i++) {b[i]=0;}
    for (int i=1;i<=n;i++) {
        b[n-1]+=a[n-i]*potencia(2,i-1);
    } int carry=0;
    porx(b,1,n);
}

void incBin(int arr[], int n) {
    int carry=1;
    for (int i=0;i<=n-1;i++) {
        arr[n-1-i]=arr[n-1-i]+carry;
        if (arr[n-1-i]>=2) {
            arr[n-1-i]=arr[n-1-i]-2;
            carry=1;
        } else {
            carry=0;
            i=n;
        }
    }
}

int problema36() {
    int a[20];for(int i=0;i<20;i++) {a[i]=0;}
    a[19]=1;
    int b[20];
    int lim=potencia(10,6);
    int suma=0;
    for (int i=1;i<lim;i++) {
        if (esPalindromo(a,20)) {
            bin2arr(a,b,20);
            if (esPalindromo(b,20)) {
                suma+=i;
                devolver(b,20);
            }
        } incBin(a,20);
    } return suma;
}

bool truncable(const int arr[]) {
    if (arr[9]==1||arr[9]==5) {
        return false;
    } int n=cifras(arr,10);
    if (arr[10-n]==1) {
        return false;
    } int p[10]; for (int i=0;i<10;i++) {p[i]=arr[i];}
    for (int i=0;i<n;i++) {
        long t=arr2long(p,10);
        if (!esPrimo(t)) {
            return false;
        } p[10-n+i]=0;
    }
    for (int i=0;i<10;i++) {p[i]=arr[i];}
    for (int i=0;i<n-1;i++) {
        for (int i=1;i<10;i++) {
            p[10-i]=p[10-i-1];
        } p[0]=0;
        long t=arr2long(p,10);
        if (!esPrimo(t)||t==1) {
            return false;
        }
    } return true;
}

bool hayPar(const int p[]) {
    int a=cifras(p,10);
    if (p[10-a]%2==0 && p[10-a]!=2) {
            return true;
    } for (int i=1;i<a;i++) {
        if (p[10-i]%2==0) {
            return true;
        }
    } return false;
}

void problema37() {
    int con=0;
    int p[10]; for (int i=0;i<10;i++) {p[i]=0;}
    p[8]=1;p[9]=1;
    while (con<11) {
        if (truncable(p)) {
            devolver(p,10);
            con++;
        } incrementar(p,10);
        while (hayPar(p)) {incrementar(p,10);}
    }
}

bool pandigital0(const int arr[], const int n) {
    int usados[n];
    int j=0;
    for (int i=0;i<n;i++) {
        for (int k=0;k<j;k++) {
            if (usados[k]==arr[i]) {
                return false;
            }
        }
        usados[j]=arr[i];
        j++;
    } return true;
}

bool substringdiv(const int p[],const int primos[]) {
    int q[3];
    for (int i=0;i<3;i++) {q[i]=p[i+1];}
    for (int i=4;i<10;i++) {
        if (arr2long(q,3)%primos[i-4]!=0) {
            return false;
        } q[0]=q[1];
        q[1]=q[2];
        q[2]=p[i];
    } return true;
}

void problema43() { //casi 4 minutos
    int p[10];for(int i=0;i<10;i++) {p[i]=i;}
    p[7]=7;
    p[8]=9;
    p[9]=9;
    int primos[7];
    primos[0]=2;primos[1]=3;primos[2]=5;primos[3]=7;primos[4]=11;primos[5]=13;primos[6]=17;
    for(long long i=123456799;i<9876543201 || p[0]>0;i++) {
        if (i%1000000000==0) {
            cout << i << endl;
        }
        if (pandigital0(p,10)) {
            if (substringdiv(p,primos)) {
                cout << "--> ";
                devolver(p,10);
            }
        } incrementar(p,10);
        for (int k=0;k<16 && (p[7]+p[8]+p[9])!=0 ;k++) {
            incrementar(p,10);
            i++;
        }
    }
}

int factDistintos(int n) {
    int div=0;
    if (esPrimo(n)) {
        return 1;
    } for (int i=2;i<=n;i++) {
        bool sumar=false;
        while (n%i==0) {
            n=n/i;
            sumar=true;
        } if (sumar) {
            div++;
        }
    } return div;
}

int problema47(){
    int con=0;
    int i;
    for (i=1;con<4;i++) {
        int res=factDistintos(i);
        if (res==4) {
            con++;
        } else {
            con=0;
        }
    } cout << i-4 << endl;
    cout << i-3 << endl;
    cout << i-2 << endl;
    cout << i-1 << endl;
    return i-4;
}

bool esPermutacion(const int a[], const int b[], int n) {
    for (int i=0;i<n;i++) {
        int aparece=0;
        for (int j=0;j<n;j++) {
            if (a[i]==a[j]) {
                aparece++;
            } if (a[i]==b[j]) {
                aparece--;
            }
        } if (aparece!=0) {
            return false;
        }
    } return true;
}

void problema49() {
    int a[4];for (int i=0;i<4;i++) {a[i]=0;}
    int b[4];
    a[0]=1;
    int primos[24];
    for (int i=1000;i<10000;i++) {
        int pos=0;
        for (int j=0;j<4;j++) {b[j]=a[j];}
        for (int j=i;j<10000;j++) {
            if (esPermutacion(b,a,4)) {
                int bnum=arr2long(b,4);
                if (esPrimo(bnum)) {
                    primos[pos]=bnum;
                    pos++;
                }
            } incrementar(b,4);
        } if (pos>=3) {
            for (int k=0;k<pos;k++) {
                int inicial=primos[k];
                for (int j=k+1;j<pos;j++) {
                    int dist=primos[j]-primos[k];
                    for (int l=j+1;l<pos;l++) {
                        if (primos[l]-primos[j]==dist) {
                            cout << primos[k] << primos[j] << primos[l] << endl;
                        }
                    }
                }
            }
        } incrementar(a,4);
    }
}

bool mismosDigitos6 (const int a[]) {
    int b[6];
    for (int j=1;j<=6;j++) {
        for (int i=0;i<6;i++) {b[i]=a[i];}
        porx(b,j,6);
        if (!esPermutacion(a,b,6) || cifras(a,6)!=cifras(b,6)) {
            return false;
        }
    } return true;
}

int problema51() {
    int a[6]; for (int i=0;i<6;i++) {a[i]=0;}
    a[5]=1;
    for (int i=0;true;i++) {
        if (mismosDigitos6(a)) {
            return arr2long(a,6);
        } incrementar(a,6);
    }
}

void reemplazarDigitos(int a[], const int digitos[], int nv) {
    for (int i=0;i<6;i++) {
        if (digitos[i]==true) {
            a[i]=nv;
        }
    }
}

int largoFamilia(const int a[], const int digitos[]) {
    int res=0;
    int c[6];
    for (int j=0;j<=9;j++) {
        for (int i=0;i<6;i++) {c[i]=a[i];}
        reemplazarDigitos(c,digitos,j);
        if (cifras(c,6)==cifras(a,6)) {
            long int cnum=arr2long(c,6);
            if (esPrimo(cnum) && cnum>1) {
                res++;
            }
        }
    } return res;
}

void problema52() {
    int a[6];for (int i=0;i<6;i++) {a[i]=0;}
    int b[6];
    bool listo=false;
    for (int i=0;!listo;i++) {
        for (int j=0;j<6;j++) {b[j]=0;}
        for (int j=0;j<potencia(2,6)-1;j++) {
            incBin(b,6);
            while (sumar(b,6)%3!=0) {
                incBin(b,6);j++;
            } int largo=largoFamilia(a,b);
            if (largo>=8) {
                cout << arr2long(a,6) << ' ' << arr2long(b,6) << endl;
                listo=true;
            }
        } incrementar(a,6);
    }
} // 48s

long combinatorio(int a, float d) {
    int m=a-d;
    float res=1;
    float b=2;
    for (int i=m+1;i<=a;i++) {
        res=res*i;
        if (b<=d) {
            res=res/b;
            b++;
        }
    } return (long)res;
}

int problema53(){
    int res=0;
    for (int i=2;i<=100;i++) {
        for (int j=1;j<=i/2;j++) {
            if (combinatorio(i,j)>1000000) {
                res+=i-2*j+1; //si i es par, da 1, si no, da 2
                j=i/2+1;
            }
        }
    } return res;
} //42 ms

int decodificar(char arr[], int tam, char clave[]) {
    int res=0;
    bool fallo=false;
    for (int i=0;i<tam && !fallo;i++) {
        char a= arr[i]^clave[i%3];
        if (a<32 || a>122 || a==64) {
            fallo=true;
        } else {
            cout << a;
            res+=a;
        }
    } return res;
}

int problema59(){
    ifstream archivo;
    archivo.open("p059_cipher.txt");
    int leer=0;
    int leerant;
    char coma;
    char arr[5000];
    int i;
    for (i=0;leer!=73||leerant!=73;i++) {
        leerant=leer;
        archivo >> leer;
        archivo >> coma;
        arr[i]=leer;
    } i--;
    char clave[3];
    for (char j=97;j<=122;j++) {
        clave[0]='g';
        for (char k=97;k<=122;k++) {
            clave[1]='o';
            for (char l=97;l<=122;l++) {
                clave[2]='d';
                return decodificar(arr,i,clave);
                cout << endl;
            }
        }
    }
}

int problema62(){
    int a[50];for (int i=0;i<49;i++) {a[i]=0;}
    a[49]=2;
    int b[50];int c[50];int d[50];
    for (int i=2;i<40000;i++) {
        if (i%1000==0) {cout << i << endl;}
        for (int j=0;j<50;j++) {b[j]=a[j];}
        porx(b,i,50);
        porx(b,i,50);
        int perm=1;
        int cb=cifras(b,50);
        bool listo=false;
        for (int k=0;k<50;k++) {c[k]=a[k];}
        for (int j=i+1;!listo;j++) {
            incrementar(c,50);
            for (int k=0;k<50;k++) {d[k]=c[k];}
            porx(d,j,50);
            porx(d,j,50);
            if (cifras(d,50)>cb) {
                listo=true;
            } else if (esPermutacion(b,d,50)) {
                perm++;
                if (perm==5) {
                    return arr2long(b,50);
                }
            }
        } incrementar(a,50);
    }
}

bool permYconc(int a[][25]) {
    devolver(a[0],25);cout << '\t';
    devolver(a[1],25);cout << '\t';
    devolver(a[2],25);cout << '\t';
    devolver(a[3],25);cout << '\t';
    devolver(a[4],25);cout << endl;
    for (int i=0;i<5;i++) {
        for (int j=0;j<5;j++) {
            if (j!=i) {
                int b[25];for (int k=0;k<25;k++) {b[k]=0;}
                concatenar(b, a[i], 25, 25);
                concatenar(b, a[j], 25, 25);
                //devolver(b,25); cout << endl;
                if (!esPrimo(arr2long(b,25))) {
                    return false;
                }
            }
        }
    } return true;
}

int main(){
    int primos[250][25];
    int posp=0;
    int p[25]; for (int n=0;n<25;n++) {p[n]=0;}
    p[24]=2;
    for (int i=2;posp<250;i++) {
        if (esPrimo(arr2long(p,25))) {
            for (int k=0;k<25;k++) {
                primos[posp][k]=p[k];
            } posp++;
        } incrementar(p,25);
    } int chequeando[5][25];
    int b[25];
    int pos[4];
    for (int i=0;i<5;i++) {
        for (int j=0;j<25;j++) {
            chequeando[i][j]=2*(j==24);
        }
    } int k;
    for (int mx=0;mx<250;mx++) {
        cout << mx << endl;
        k=0;
        while (pos[0]<=mx) {
            for (int i=0;i<25;i++) {
                chequeando[k][i]=primos[pos[k]][i];
            }
            cout << k << ' ';
            for (int i=0;i<k;i++) {
                for (int j=0;j<25;j++) {b[j]=0;}
                concatenar(b, chequeando[i], 25, 25);
                concatenar(b, chequeando[k], 25, 25);
                devolver(b,25);
                cout << endl;
                if (!esPrimo(arr2long(b,25))) {
                    pos[k]++;
                    if (pos[k]>mx) {
                        pos[k]=0;
                        k-=2;
                    }
                } i=k;
            } if (k<4) {
                k++;
            } //else {
                devolver(chequeando[0],25);
                devolver(chequeando[1],25);
                devolver(chequeando[2],25);
                devolver(chequeando[3],25);
                devolver(chequeando[4],25);
            //}
        }
    }
};
/// en vez de chequear cada combinación, la forma correcta es pasar k si a[0]a[1] es compuesto
///Recordar que la idea era que chequeando[0] empiece n max
/*int main(){
    int primos[250][25];
    int posp=0;
    int p[25]; for (int n=0;n<25;n++) {p[n]=0;}
    p[24]=2;
    for (int i=2;posp<250;i++) {
        if (esPrimo(arr2long(p,25))) {
            for (int k=0;k<25;k++) {
                primos[posp][k]=p[k];
            } posp++;
        } incrementar(p,25);
    } int chequeando[5][25];
    int pos[4];
    for (int i=0;i<5;i++) {
        for (int j=0;j<25;j++) {
            chequeando[i][j]=2*(j==24);
        }
    } int k=3;
    for (int mx=0;mx<250;mx++) {
        cout << mx << endl;
        for (int i=0;i<25;i++) {
            chequeando[4][i]=primos[mx][i];
        } for (int i=0;i<4;i++) {
            pos[i]=0;
        } while (pos[0]<=mx) {
            for (int i=0;i<25;i++) {
                chequeando[k][i]=primos[pos[k]][i];
            } if (k==3 && permYconc(chequeando)) {
                int suma[25];for (int j=0;j<25;j++) {suma[j]=0;}
                for (int i=0;i<25;i++) {
                    for (int j=0;j<5;j++) {
                        suma[i]+=chequeando[j][i];
                    }
                } porx(suma,1,25);
                devolver(suma,25);
            } pos[k]++;
            if (pos[k]>=mx) {
                if (k>0) {
                    pos[k]=pos[k-1];
                    k--;
                }
            } else {
                k=3;
            }
        }
    }
};*/
