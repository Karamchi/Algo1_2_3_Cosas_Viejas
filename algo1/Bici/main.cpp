#include <iostream>
#include "Bicicleta.h"

using namespace std;

int main() {
    Bicicleta b1("cross", "rojo", 20);
    Bicicleta b2("cross", "rojo", 26);
    Bicicleta b3;

    cout << "perimetro b1: " << b1.perimetroRueda() << endl;
    cout << b1;
    return 0;
}
