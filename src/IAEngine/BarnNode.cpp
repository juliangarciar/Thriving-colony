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
    IA::getInstance() -> buildBuilding(1100, new Vector3<float>(0, 0, 0), Enumeration::BuildingType::Barn, false);
}