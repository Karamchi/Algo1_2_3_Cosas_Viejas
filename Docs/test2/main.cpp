#include <iostream>

using namespace std;
void duplicar (int &a)
{
    a=2*a;
}

int main(int a)
{
    a=42;
    duplicar(a);
    cout << "El valor es " << a << endl;
    return 0;
}
