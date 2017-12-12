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
    IA::getInstance() -> getBuildings() -> buildBuilding(1100, new Vector3<float>(1600, 300, 1500), Enumeration::BuildingType::Barn, false);
}