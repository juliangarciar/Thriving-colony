#include "DevelopCityNode.h"
#include "ServiceNode.h"
#include "ResourceNode.h"
#include "HomeNode.h"
#include "ArmyNode.h"
#include "../IA.h"

DevelopCityNode::DevelopCityNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = new Node*[4];
    children[0] = new ServiceNode(this);
    children[1] = new ResourceNode(this);
    children[2] = new HomeNode(this);
    children[3] = new ArmyNode(this);
}

DevelopCityNode::~DevelopCityNode(){
    delete father;
    delete[] children;
}

void DevelopCityNode::question() {

    //std::cout << "Voy a desarrollar la ciudad" << std::endl;
    /**
     *  TODO
     *  ESTE ES EL DE MUY FELIZ, HAY QUE ENCONTRAR LA MEJOR FORMA DE HACER QUE VALGA PARA TODOS
     *  O EN EL PEOR DE LOS CASOS HACER NODOS DE DESARROLLAR LA CIUDAD PARA CADA UNO DE LOS TIPOS DE
     *  ARBOL AUNQUE ESTARIAMOS EN EL MISMO PROBLEMA PORQUE EL NODO RAZI NECESITARIA SABER QUE TIPO DE ARBOL
     *  ES PARA CREAR LOS HIJOS
     */
    if (IA::getInstance() -> getHappiness() < tree -> getHappinessThreshold()) {
        children[0] -> question();
    } else {
        //Second branch: Resources
        if (tree -> needResourcesInvestment()) {
            children[1] -> question();
        } else {
            //Third branch: Homes
            if (tree -> calculateCitizensRate() < tree -> getCitizensThreshold()) {
                children[2] -> question();
            } else {
                //Fourth branch: Army
                std::cout << "Llega" << std::endl;
                if (tree -> needArmyInvestment()) {
                    children[3] -> question();
                } else {
                    //std::cout << "No hago nada" << std::endl;
                    // Ultima oportunidad
                    children[1] -> question();
                }
            }
        }
    }
}