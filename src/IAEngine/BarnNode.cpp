#include "BarnNode.h"
#include "../IA.h"

BarnNode::BarnNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

BarnNode::~BarnNode(){
    delete father;
}

void BarnNode::question() {
    IA::getInstance() -> setChoiceIndex(Enumeration::IAChoices::BuildBarn);
    //std::cout << "Construyo un establo" << std::endl;
    if (IA::getInstance() -> getQuarryAmount() == 0) {
        IA::getInstance() -> getTree() -> setRequireCrystal(true);
    } else {
        if (IA::getInstance() -> getBuildingManager() -> isSolvent(Enumeration::BuildingCost::BarnMetalCost, Enumeration::BuildingCost::BarnCrystalCost, Enumeration::Team::IA)) {
            IA::getInstance() -> getTree() -> setRequireBarn(false);
            Vector3<float> v = IA::getInstance() -> determinatePositionBuilding();
            IA::getInstance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::Barn, Enumeration::Team::IA);
        }
    }
}