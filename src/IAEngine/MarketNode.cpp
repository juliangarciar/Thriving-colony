#include "MarketNode.h"
#include "../IA.h"

MarketNode::MarketNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

MarketNode::~MarketNode(){
    delete father;
}

void MarketNode::question() {
    std::cout << "Contruyo un mercado" << std::endl;
    if (IA::getInstance() -> getBuildingManager() -> isSolvent(Enumeration::BuildingCost::MarketMetalCost, Enumeration::BuildingCost::MarketCrystalCost, Enumeration::Team::IA)) {
        Vector3<float> *v = IA::getInstance() -> determinatePositionBuilding();
        IA::getInstance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::Market, Enumeration::Team::IA);
    }
}