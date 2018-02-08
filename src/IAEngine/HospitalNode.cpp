#include "HospitalNode.h"
#include "../IA.h"

HospitalNode::HospitalNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

HospitalNode::~HospitalNode() {
    delete father;
}

void HospitalNode::question() {

    IA::getInstance() -> setChoiceIndex(Enumeration::IAChoices::BuildHospital);
    if (IA::getInstance() -> getBuildingManager() -> getAmount(Enumeration::BuildingType::Quarry) == 0) {
        IA::getInstance() -> getTree() -> setRequireCrystal(true);
    } else {
        //std::cout << "Contruyo un hospital" << std::endl;
        if (IA::getInstance() -> getBuildingManager() -> isSolvent(Enumeration::BuildingCost::HospitalMetalCost, Enumeration::BuildingCost::HospitalCrystalCost)) {
            Vector3<f32> v = IA::getInstance() -> determinatePositionBuilding();
            IA::getInstance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::Hospital, true);
        }
    }
}