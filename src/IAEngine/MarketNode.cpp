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
    if (IA::Instance() -> getBuildingManager() -> checkCanPay("Market")) {
        Vector2<f32> v = IA::Instance() -> determinatePositionBuilding();
        IA::Instance() -> getBuildingManager() -> createBuilding(v, "Market");
    }
}