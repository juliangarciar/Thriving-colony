#include "SchoolNode.h"
#include "../IA.h"

SchoolNode::SchoolNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

SchoolNode::~SchoolNode() {
    delete father;
}

void SchoolNode::question() {

    IA::getInstance() -> setChoiceIndex(Enumeration::IAChoices::BuildSchool);
    //std::cout << "Contruyo una escuela" << std::endl;
    if (IA::getInstance() -> getBuildingManager() -> isSolvent(Enumeration::BuildingCost::SchoolMetalCost, Enumeration::BuildingCost::SchoolCrystalCost)) {
        Vector3<f32> v = IA::getInstance() -> determinatePositionBuilding();
        IA::getInstance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::School, true);
    }
}