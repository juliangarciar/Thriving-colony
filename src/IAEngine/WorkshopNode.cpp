#include "WorkshopNode.h"
#include "../IA.h"

WorkshopNode::WorkshopNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

WorkshopNode::~WorkshopNode(){
    delete father;
}

void WorkshopNode::question() {
    //std::cout << Construyo un taller << std::endl;
    if (IA::getInstance() -> getBuildingManager() -> isSolvent(Enumeration::BuildingCost::WorkshopMetalCost, Enumeration::BuildingCost::WorkshopCrystalCost, Enumeration::Team::IA)) {
        Vector3<float> v = IA::getInstance() -> determinatePositionBuilding();
        IA::getInstance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::Workshop, Enumeration::Team::IA);
    }
}