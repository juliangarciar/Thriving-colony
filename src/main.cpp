#include <iostream>
#include "numero.h"
using namespace std;


int main(){
    int sumaTotal;
    numero a = numero(3);
    numero b = numero(4);

    sumaTotal = a.suma(b);

    cout << "Hello world." << endl;
    cout << "Tu suma de prueba es: " << sumaTotal << endl;
    return 0;
}