#include "HospitalNode.h"
#include <IA.h>

HospitalNode::HospitalNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

HospitalNode::~HospitalNode() {
    delete father;
}

void HospitalNode::question() {
    IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::BuildHospital);
    if (IA::Instance() -> getBuildingManager() -> getAmount("Quarry") == 0) {
        IA::Instance() -> getTree() -> setRequireCrystal(true);
    } else {
        //std::cout << "Contruyo un hospital" << std::endl;
        if (IA::Instance() -> getBuildingManager() -> checkCanPay("Hospital")) {
            Vector2<f32> v = IA::Instance() -> determinatePositionBuilding();
            IA::Instance() -> getBuildingManager() -> createBuilding(v, "Hospital");
        }
    }
}