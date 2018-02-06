#include "HomeNode.h"
#include "../IA.h"

HomeNode::HomeNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

HomeNode::~HomeNode() {
    delete father;
}

void HomeNode::question() {

    IA::getInstance() -> setChoiceIndex(Enumeration::IAChoices::BuildHome);
    //std::cout << "Voy a invertir en casas" << std::endl;
    if (IA::getInstance() -> getBuildingManager() -> isSolvent(Enumeration::BuildingCost::HomeMetalCost, Enumeration::BuildingCost::HomeCrystalCost)) {
        IA::getInstance() -> getTree() -> setRequireCitizens(false);
        Vector3<float> v = IA::getInstance() -> determinatePositionBuilding();
        IA::getInstance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::House);
    }
}