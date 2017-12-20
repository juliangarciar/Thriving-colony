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
    std::cout << "Construyo un establo" << std::endl;
    //ToDo: Mirar coordenadas donde construir y ponerselas en el vector3
    Vector3<float> *v = IA::getInstance() -> determinatePositionBuilding();
    IA::getInstance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::Barn, Enumeration::Team::IA);
}