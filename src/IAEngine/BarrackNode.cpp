#include "BarrackNode.h"
#include <IA.h>


BarrackNode::BarrackNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

BarrackNode::~BarrackNode() {
    delete father;
}

void BarrackNode::question() {

    IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::BuildBarrack);
    //std::cout << "Construyo un cuartel" << std::endl;
    if (IA::Instance() -> getBuildingManager() -> checkCanPay("Barrack")) {
        IA::Instance() -> getTree() -> setRequireBarrack(false);
        Vector2<f32> v = IA::Instance() -> determinatePositionBuilding();
        IA::Instance() -> getBuildingManager() -> createBuilding(v, "Barrack");
    }
}