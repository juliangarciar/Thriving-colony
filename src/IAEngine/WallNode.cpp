#include "WallNode.h"
#include <IA.h>

WallNode::WallNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

WallNode::~WallNode() {
    delete father;
}

void WallNode::question() {
    IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::BuildWall);
    //std::cout << Construyo una muralla << std::endl;
    if (IA::Instance() -> getBuildingManager() -> checkCanPay("Wall")) {
        Vector2<f32> v = IA::Instance() -> determinatePositionBuilding();
        IA::Instance() -> getBuildingManager() -> createBuilding(v, "Wall");
    }
}