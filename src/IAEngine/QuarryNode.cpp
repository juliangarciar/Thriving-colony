#include "QuarryNode.h"
#include <IA.h>

QuarryNode::QuarryNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

QuarryNode::~QuarryNode() {
    delete father;
}

void QuarryNode::question() {

    IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::BuildQuarry);
    //std::cout << "Construyo una cantera" << std::endl;
    if (IA::Instance() -> getBuildingManager() -> isSolvent(Enumeration::BuildingCost::QuarryMetalCost, Enumeration::BuildingCost::QuarryCrystalCost)) {
        IA::Instance() -> getTree() -> setRequireCrystal(false);
        Vector2<f32> v = IA::Instance() -> determinatePositionBuilding();
        IA::Instance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::Quarry, false);
    }
}