#include "QuarryNode.h"
#include <IA.h>

QuarryNode::QuarryNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

QuarryNode::~QuarryNode() {
    delete father;
}

void QuarryNode::question() {
    IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::BuildQuarry);
    //std::cout << "Construyo una cantera" << std::endl;
    if (IA::Instance() -> getBuildingManager() -> checkCanPay("Quarry")) {
        IA::Instance() -> getTree() -> setRequireCrystal(false);
        Vector2<f32> v = IA::Instance() -> determinatePositionBuilding();
        IA::Instance() -> getBuildingManager() -> createBuilding(v, "Quarry");
    }
}