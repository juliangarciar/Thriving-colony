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
    //ToDo: Mirar coordenadas donde construir y ponerselas en el vector3
    if (IA::getInstance() -> getBuildings() -> isSolvent(Enumeration::BuildingCost::MarketMetalCost, Enumeration::BuildingCost::MarketCrystalCost, Enumeration::Team::IA)) {
        Vector3<float> *v = IA::getInstance() -> determinatePositionBuilding();
        IA::getInstance() -> getBuildings() -> buildBuilding(v, Enumeration::BuildingType::Market, Enumeration::Team::IA);
    }
}