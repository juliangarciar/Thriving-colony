#include "BarnNode.h"
#include <IA.h>

BarnNode::BarnNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

BarnNode::~BarnNode() {
    delete father;
}

void BarnNode::question() {
    IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::BuildBarn);
    //std::cout << "Construyo un establo" << std::endl;
    if (IA::Instance() -> getBuildingManager() -> getAmount(Enumeration::BuildingType::Quarry) == 0) {
        IA::Instance() -> getTree() -> setRequireCrystal(true);
    } else {
        if (IA::Instance() -> getBuildingManager() -> isSolvent(Enumeration::BuildingCost::BarnMetalCost, Enumeration::BuildingCost::BarnCrystalCost)) {
            IA::Instance() -> getTree() -> setRequireBarn(false);
            Vector3<f32> v = IA::Instance() -> determinatePositionBuilding();
            IA::Instance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::Barn, true);
        }
    }
}