//#ifndef NUMERO_H
//#define NUMERO_H
#include <iostream>

class numero{
private:
    int numero1;
    int numero2;
    int numero3;
    std::string nombre;
public:
    numero(int a, std::string obj);
    numero(const numero& orig);
    virtual ~numero();
    int suma(numero b);
    int getNumero(){
        return numero1;
    };
    std::string getName(){
        return nombre;
    };
};
//#endif /* NUMERO_H */