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
    //std::cout << "Contruyo un mercado" << std::endl;
    //ToDo: Mirar coordenadas donde construir y ponerselas en el vector3
    IA::getInstance() -> getBuildings() -> buildBuilding(600, new Vector3<float>(0, 0, 0), Enumeration::BuildingType::Market, false);
}