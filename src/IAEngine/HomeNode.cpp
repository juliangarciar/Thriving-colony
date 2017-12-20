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
    if (IA::getInstance() -> getBuildingManager() -> isSolvent(Enumeration::BuildingCost::HomeMetalCost, Enumeration::BuildingCost::HomeCrystalCost, Enumeration::Team::IA)) {
        Vector3<float> *v = IA::getInstance() -> determinatePositionBuilding();
        IA::getInstance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::House, Enumeration::Team::IA);
    }
}