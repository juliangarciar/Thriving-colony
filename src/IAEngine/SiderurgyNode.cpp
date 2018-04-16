#include "SiderurgyNode.h"
#include <IA.h>

SiderurgyNode::SiderurgyNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

SiderurgyNode::~SiderurgyNode() {
    delete father;
}

void SiderurgyNode::question() {

    IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::BuildSiderurgy);
    //std::cout << "Construyo una siderurgia" << std::endl;
    if (IA::Instance() -> getBuildingManager() -> checkCanPay("Siderurgy")) {
        Vector2<f32> v = IA::Instance() -> determinatePositionBuilding();
        IA::Instance() -> getBuildingManager() -> createBuilding(v, "Siderurgy");
    }
}