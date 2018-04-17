#include "HomeNode.h"
#include <IA.h>

HomeNode::HomeNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

HomeNode::~HomeNode() {
    delete father;
}

void HomeNode::question() {

    IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::BuildHome);
    //std::cout << "Voy a invertir en casas" << std::endl;
    if (IA::Instance() -> getBuildingManager() -> isSolvent(Enumeration::BuildingCost::HomeMetalCost, Enumeration::BuildingCost::HomeCrystalCost)) {
        IA::Instance() -> getTree() -> setRequireCitizens(false);
        Vector3<f32> v = IA::Instance() -> determinatePositionBuilding();
        IA::Instance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::House, false);
    }
}