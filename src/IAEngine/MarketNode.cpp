#include "MarketNode.h"
#include <IA.h>

MarketNode::MarketNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

MarketNode::~MarketNode() {
    delete father;
}

void MarketNode::question() {

    IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::BuildMarket);
    //std::cout << "Contruyo un mercado" << std::endl;
    if (IA::Instance() -> getBuildingManager() -> isSolvent(Enumeration::BuildingCost::MarketMetalCost, Enumeration::BuildingCost::MarketCrystalCost)) {
        Vector2<f32> v = IA::Instance() -> determinatePositionBuilding();
        IA::Instance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::Market, false);
    }
}