#include "TowerNode.h"
#include <IA.h>

TowerNode::TowerNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

TowerNode::~TowerNode() {
    delete father;
}

void TowerNode::question() {

    IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::BuildTower);
    //std::cout << "Construyo un torre" << std::endl;
    if (IA::Instance() -> getBuildingManager() -> checkCanPay("Tower")) {
        Vector2<f32> v = IA::Instance() -> determinatePositionBuilding();
        IA::Instance() -> getBuildingManager() -> createBuilding(v, "Tower");
    }
}