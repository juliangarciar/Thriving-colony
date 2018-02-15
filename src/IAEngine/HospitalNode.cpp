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
    if (IA::Instance() -> getBuildingManager() -> getAmount(Enumeration::BuildingType::Quarry) == 0) {
        IA::Instance() -> getTree() -> setRequireCrystal(true);
    } else {
        //std::cout << "Contruyo un hospital" << std::endl;
        if (IA::Instance() -> getBuildingManager() -> isSolvent(Enumeration::BuildingCost::HospitalMetalCost, Enumeration::BuildingCost::HospitalCrystalCost)) {
            Vector3<f32> v = IA::Instance() -> determinatePositionBuilding();
            IA::Instance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::Hospital, true);
        }
    }
}