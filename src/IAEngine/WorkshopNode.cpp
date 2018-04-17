#include "WorkshopNode.h"
#include <IA.h>

WorkshopNode::WorkshopNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

WorkshopNode::~WorkshopNode() {
    delete father;
}

void WorkshopNode::question() {
    IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::BuildWorkshop);
    //std::cout << Construyo un taller << std::endl;
    if (IA::Instance() -> getBuildingManager() -> getAmount("Quarry") == 0) {
        IA::Instance() -> getTree() -> setRequireCrystal(true);
    } else {
        if (IA::Instance() -> getBuildingManager() -> checkCanPay("Workshop")) {
            IA::Instance() -> getTree() -> setRequireBarrack(false);
            Vector2<f32> v = IA::Instance() -> determinatePositionBuilding();
            IA::Instance() -> getBuildingManager() -> createBuilding(v, "Workshop");
        }
    }
}