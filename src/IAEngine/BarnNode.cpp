#include "BarnNode.h"
#include "../IA.h"

BarnNode::BarnNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

BarnNode::~BarnNode(){
    delete father;
}

void BarnNode::question() {
    //std::cout << Construyo un establo << std::endl;
    //ToDo: Mirar coordenadas donde construir y ponerselas en el vector3
    if (IA::getInstance() -> getBuildings() -> isSolvent(Enumeration::BuildingCost::BarnMetalCost, Enumeration::BuildingCost::BarnCrystalCost, Enumeration::Team::IA)) {
        Vector3<float> *v = IA::getInstance() -> determinatePositionBuilding();
        IA::getInstance() -> getBuildings() -> buildBuilding(v, Enumeration::BuildingType::Barn, Enumeration::Team::IA);
    }
}