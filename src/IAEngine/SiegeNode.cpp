#include "SiegeNode.h"
#include "RamNode.h"
#include "CatapultNode.h"
#include "../IA.h"

SiegeNode::SiegeNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = new Node*[2];
    children[0] = new RamNode(this);
    children[1] = new CatapultNode(this);
}

SiegeNode::~SiegeNode() {
    delete father;
    delete[] children;
}

void SiegeNode::question() {
    //std::cout << "Voy a hacer asedio" << std::endl;
    //First subsubsubbranch: Ram
    if (IA::getInstance() -> getBuildingManager() -> getAmount(Enumeration::BuildingType::Workshop) > 0) {
        if (IA::getInstance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::Desintegrator) <= IA::getInstance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::Launcher)) {
            children[0] -> question();
        } else {
            //Second subsubsubbranch: Catapult
            children[1] -> question();
        }
    } else {
        IA::getInstance() -> getTree() -> setRequireWorkshop(true);
        //children[0] -> question();
    }
}