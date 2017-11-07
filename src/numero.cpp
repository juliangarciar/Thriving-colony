#include "numero.h"

numero::numero(int a){
    numero1 = a;
    numero2 = a - 1;
    numero3 = a - 2;
}
numero::numero(const numero& orig){

}
numero::~numero(){
}
int numero::suma(numero b){
    int resultado;
    resultado = numero1 + b.getNumero();
    return resultado;
}