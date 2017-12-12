#include "TowerNode.h"
#include "../IA.h"

TowerNode::TowerNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

TowerNode::~TowerNode(){
    delete father;
}

void TowerNode::question() {
    //std::cout << Construyo un torre << std::endl;
    //ToDo: Mirar coordenadas donde construir y ponerselas en el vector3
    IA::getInstance() -> getBuildings() -> buildBuilding(500, new Vector3<float>(0, 0, 0), Enumeration::BuildingType::Tower, false);
    IA::getInstance() -> increaseTowerAmount();
}