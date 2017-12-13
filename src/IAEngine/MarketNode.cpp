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
    Vector3<float> *v = IA::getInstance() -> determinatePositionBuilding();
    IA::getInstance() -> getBuildings() -> buildBuilding(600, v, Enumeration::BuildingType::Market, false);
}