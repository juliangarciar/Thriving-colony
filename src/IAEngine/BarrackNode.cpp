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

    IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::BuildBarrack);
    //std::cout << "Construyo un cuartel" << std::endl;
    if (IA::Instance() -> getBuildingManager() -> isSolvent(Enumeration::BuildingCost::BarrackMetalCost, Enumeration::BuildingCost::BarrackCrystalCost)) {
        IA::Instance() -> getTree() -> setRequireBarrack(false);
        Vector3<f32> v = IA::Instance() -> determinatePositionBuilding();
        IA::Instance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::Barrack, true);
    }
}