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
    Vector3<float> *v = IA::getInstance() -> determinatePositionBuilding();
    IA::getInstance() -> getBuildings() -> buildBuilding(v, Enumeration::BuildingType::Tower, Enumeration::Team::IA);
    IA::getInstance() -> increaseTowerAmount();
}