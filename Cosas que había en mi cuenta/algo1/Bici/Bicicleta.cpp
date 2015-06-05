#include "Bicicleta.h"
#include <string>

Bicicleta::Bicicleta() {
    _modelo = "paseo";
    _color = "amarillo";
    _rodado = 20;
}

Bicicleta::Bicicleta(const string m, const string c, const int r) {
    _modelo = m;
    _color = c;
    _rodado = r;
}

void Bicicleta::incrementarRodado(const int c) {
    _rodado = _rodado + c;
}

double Bicicleta::perimetroRueda() const {
    double ret;
    ret = 3.14 * _rodado;
    return ret;
}

bool Bicicleta::operator==(const Bicicleta b2) {
    return (_modelo == b2._modelo) && (_color == b2._color);
}

string Bicicleta::modelo() const{
    return _modelo;
}

string Bicicleta::color() const{
    return _color;
}

int Bicicleta::rodado() const{
    return _rodado;
}


std::ostream & operator<<(std::ostream & os,const Bicicleta & b){
    os << "Modelo: " << b.modelo() << " Color: " << b.color()
    << " Rodado: " << b.rodado();
    return os;
}
