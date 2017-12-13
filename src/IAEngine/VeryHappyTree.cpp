#include "VeryHappyTree.h"
#include "ServiceNode.h"
#include "ResourceNode.h"
#include "HomeNode.h"
#include "ArmyNode.h"
#include "../IA.h"

VeryHappyTree::VeryHappyTree(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = new Node*[4];
    children[0] = new ServiceNode(this);
    children[1] = new ResourceNode(this);
    children[2] = new HomeNode(this);
    children[3] = new ArmyNode(this);
}

VeryHappyTree::~VeryHappyTree() {
    delete father;
    delete[] children;
}
///TODO quitar IA de los arboles

void VeryHappyTree::question() {
    //First branch: Services
    if (IA::getInstance() -> getHappiness() < tree -> getHappinessThreshold()) {
        std::cout << "Servicios" << std::endl;
        children[0] -> question();
    } else {
        //Second branch: Resources
        if (tree -> needResourcesInvestment()) {
            std::cout << "Recursos" << std::endl;
            children[1] -> question();
        } else {
            //Third branch: Homes
            if (tree -> calculateCitizensRate() < tree -> getCitizensThreshold()) {
                std::cout << "Viviendas" << std::endl;
                children[2] -> question();
            } else {
                //Fourth branch: Army
                if (tree -> needArmyInvestment()) {
                    std::cout << "Ejercito" << std::endl;
                    children[3] -> question();
                } else {
                    std::cout << "No hago nada" << std::endl;
                    // Ultima oportunidad
                    children[2] -> question();
                }
            }
        }
    }
}

/**
 * Determines wheter or not you are ready to attack
 */
bool VeryHappyTree::readyToAttack() {
    //ToDo: Determinar cuando se esta listo
    return false;
}