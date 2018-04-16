#include "SchoolNode.h"
#include <IA.h>

SchoolNode::SchoolNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

SchoolNode::~SchoolNode() {
    delete father;
}

void SchoolNode::question() {
    IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::BuildSchool);
    //std::cout << "Contruyo una escuela" << std::endl;
    if (IA::Instance() -> getBuildingManager() -> checkCanPay("School")) {
        Vector2<f32> v = IA::Instance() -> determinatePositionBuilding();
        IA::Instance() -> getBuildingManager() -> createBuilding(v, "School");
    }
}