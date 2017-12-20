#include "WallNode.h"
#include "../IA.h"

WallNode::WallNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

WallNode::~WallNode(){
    delete father;
}

void WallNode::question() {
    std::cout << "Construyo una muralla" << std::endl;
    Vector3<float> *v = IA::getInstance() -> determinatePositionBuilding();
    IA::getInstance() -> getBuildings() -> buildBuilding(v, Enumeration::BuildingType::Wall, Enumeration::Team::IA);
    IA::getInstance()-> increaseWallAmount();
}