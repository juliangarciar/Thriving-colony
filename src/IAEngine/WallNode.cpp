#include "WallNode.h"
#include "../IA.h"

WallNode::WallNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

WallNode::~WallNode(){
    delete father;
}

void WallNode::question() {
    //std::cout << Construyo una muralla << std::endl;
    //ToDo: Mirar coordenadas donde construir y ponerselas en el vector3
    if (IA::getInstance() -> getBuildingManager() -> isSolvent(Enumeration::BuildingCost::WallMetalCost, Enumeration::BuildingCost::WallCrystalCost, Enumeration::Team::IA)) {
        Vector3<float> *v = IA::getInstance() -> determinatePositionBuilding();
        IA::getInstance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::Wall, Enumeration::Team::IA);
    //Esto va en el constructor
    //IA::getInstance()-> increaseWallAmount();
    }
}