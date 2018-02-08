#include "MarketNode.h"
#include "../IA.h"

MarketNode::MarketNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

MarketNode::~MarketNode() {
    delete father;
}

void MarketNode::question() {

    IA::getInstance() -> setChoiceIndex(Enumeration::IAChoices::BuildMarket);
    //std::cout << "Contruyo un mercado" << std::endl;
    if (IA::getInstance() -> getBuildingManager() -> isSolvent(Enumeration::BuildingCost::MarketMetalCost, Enumeration::BuildingCost::MarketCrystalCost)) {
        Vector3<f32> v = IA::getInstance() -> determinatePositionBuilding();
        IA::getInstance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::Market, true);
    }
}