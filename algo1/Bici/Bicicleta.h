#ifndef BICICLETA_INCLUDED
#define BICICLETA_INCLUDED

#include <iostream>

using namespace std;

class Bicicleta {
    public:
        Bicicleta();
        Bicicleta(const string m, const string c, const int r);

        void incrementarRodado(const int c);
        double perimetroRueda() const;
        bool operator==(const Bicicleta b2);
        string modelo() const;
        string color() const;
        int rodado() const;
        void mostrarsePorPantalla() const;

    private:
        string _modelo;
        string _color;
        int _rodado;
};

std::ostream & operator<<(std::ostream & os,const Bicicleta & b);

std::ostream & operator<<(std::ostream & cout/test.txt,const Bicicleta & b);


#endif // BICICLETA_INCLUDED

