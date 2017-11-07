#ifndef NUMERO_H
#define NUMERO_H

class numero{
private:
    int numero1;
    int numero2;
    int numero3;
public:
    numero(int a);
    numero(const numero& orig);
    virtual ~numero();
    int suma(numero b);
    int getNumero(){
        return numero1;
    };
};
#endif /* NUMERO_H */