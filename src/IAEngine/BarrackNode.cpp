#include "BarrackNode.h"
#include "../IA.h"


BarrackNode::BarrackNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

BarrackNode::~BarrackNode(){
    delete father;
}

void BarrackNode::question() {
    //std::cout << "Construyo un cuartel" << std::endl;
    //ToDo: Mirar coordenadas donde construir y ponerselas en el vector3
    //TODO PRECIO
    if (IA::getInstance() -> getBuildingManager() -> isSolvent(Enumeration::BuildingCost::BarrackMetalCost, Enumeration::BuildingCost::BarrackCrystalCost, Enumeration::Team::IA)) {
        Vector3<float> *v = IA::getInstance() -> determinatePositionBuilding();
        IA::getInstance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::Barrack, Enumeration::Team::IA);
    }
}