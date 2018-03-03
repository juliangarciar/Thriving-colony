#include "VeryHappyTree.h"
#include "RetractTroopsNode.h"
#include "ServiceNode.h"
#include "ResourceNode.h"
#include "HomeNode.h"
#include "ArmyNode.h"
#include <IA.h>

VeryHappyTree::VeryHappyTree(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = new Node*[5];
    children[0] = new RetractTroopsNode(this);
    children[1] = new ServiceNode(this);
    children[2] = new ResourceNode(this);
    children[3] = new HomeNode(this);
    children[4] = new ArmyNode(this);
}

VeryHappyTree::~VeryHappyTree() {
    delete father;
    delete[] children;
}
///TODO quitar IA de los arboles

void VeryHappyTree::question() {
    if (IA::Instance() -> getUnitManager() -> areTroopsInMap() == true) {
        children[0] -> question();
    } else {
        //First branch: Services
        if (IA::Instance() -> getHappiness() < IA::Instance() -> getTree() -> getHappinessThreshold()) {
            //std::cout << "Servicios" << std::endl;
            children[1] -> question();
        } else {
            //Second branch: Resources
            if (IA::Instance() -> getTree() -> needResourcesInvestment()) {
                //std::cout << "Recursos" << std::endl;
                children[2] -> question();
            } else {
                //Third branch: Homes
                if (IA::Instance() -> getTree() -> calculateCitizensRate() < IA::Instance() -> getTree() -> getCitizensThreshold()) {
                    //std::cout << "Viviendas" << std::endl;
                    children[3] -> question();
                    //ToDo: Si no hay cosas de hacer ejercito, da violacion de segmento
                } else {
                    //Fourth branch: Army
                    if (IA::Instance() -> getTree() -> needArmyInvestment()) {
                        //std::cout << "Ejercito" << std::endl;
                        children[4] -> question();
                    } else {
                        //std::cout << "No hago nada" << std::endl;
                        // Ultima oportunidad
                        children[3] -> question();
                    }
                }
            }
        }
    }
}

/**
 * Determines wheter or not you are ready to attack
 */
bool VeryHappyTree::readyToAttack() {
    if (IA::Instance() -> getArmyLevel() > IA::Instance() -> getTree() -> getAttackThreshold()) {
        return true;
    } else{
        return false;
    }
}