#include "numero.h"

numero::numero(int a, std::string cadena){
    numero1 = a;
    numero2 = a - 1;
    numero3 = a - 2;
    nombre = cadena;
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