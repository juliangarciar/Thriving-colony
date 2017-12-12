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
    //std::cout << Construyo una muralla << std::endl;
    //ToDo: Mirar coordenadas donde construir y ponerselas en el vector3
    //IA::getInstance() -> buildBuilding(200, new Vector3<float>(0, 0, 0), Enumeration::BuildingType::Wall, false);
    IA::getInstance()-> increaseWallAmount();
}