#include "QuarryNode.h"
#include "../IA.h"

QuarryNode::QuarryNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

QuarryNode::~QuarryNode() {
    delete father;
}

void QuarryNode::question() {

    IA::getInstance() -> setChoiceIndex(Enumeration::IAChoices::BuildQuarry);
    //std::cout << "Construyo una cantera" << std::endl;
    if (IA::getInstance() -> getBuildingManager() -> isSolvent(Enumeration::BuildingCost::QuarryMetalCost, Enumeration::BuildingCost::QuarryCrystalCost)) {
        IA::getInstance() -> getTree() -> setRequireCrystal(false);
        Vector3<f32> v = IA::getInstance() -> determinatePositionBuilding();
        IA::getInstance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::Quarry, true);
    }
}