#include "BarrackNode.h"
#include "../IA.h"


BarrackNode::BarrackNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

BarrackNode::~BarrackNode() {
    delete father;
}

void BarrackNode::question() {

    IA::getInstance() -> setChoiceIndex(Enumeration::IAChoices::BuildBarrack);
    //std::cout << "Construyo un cuartel" << std::endl;
    if (IA::getInstance() -> getBuildingManager() -> isSolvent(Enumeration::BuildingCost::BarrackMetalCost, Enumeration::BuildingCost::BarrackCrystalCost)) {
        IA::getInstance() -> getTree() -> setRequireBarrack(false);
        Vector3<float> v = IA::getInstance() -> determinatePositionBuilding();
        IA::getInstance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::Barrack, true);
    }
}