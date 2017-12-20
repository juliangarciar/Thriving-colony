#include "HomeNode.h"
#include "../IA.h"

HomeNode::HomeNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

HomeNode::~HomeNode(){
    delete father;
}

void HomeNode::question() {
    //std::cout << "Voy a invertir en casas" << std::endl;
    //ToDo: Mirar coordenadas donde construir y ponerselas en el vector3
    Vector3<float> *v = IA::getInstance() -> determinatePositionBuilding();
    IA::getInstance() -> getBuildings() -> buildBuilding(v, Enumeration::BuildingType::House, Enumeration::Team::IA);
}