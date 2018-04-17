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
    if (IA::Instance() -> getBuildingManager() -> checkCanPay("House")) {
        IA::Instance() -> getTree() -> setRequireCitizens(false);
        Vector2<f32> v = IA::Instance() -> determinatePositionBuilding();
        IA::Instance() -> getBuildingManager() -> createBuilding(v, "House");
    }
}