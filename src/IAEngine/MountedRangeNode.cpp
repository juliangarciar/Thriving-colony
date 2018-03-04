#include "MountedRangeNode.h"
#include "BarnNode.h"
#include <IA.h>

MountedRangeNode::MountedRangeNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
    /*
    children = new Node*[1];
    children[0] = new BarnNode(this);
    */
}

MountedRangeNode::~MountedRangeNode() {
    delete father;
    //delete[] children;
}

void MountedRangeNode::question() {

    IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::TrainMountedRanged);
    if (IA::Instance() -> getBuildingManager() -> getAmount(Enumeration::BuildingType::Barn) > 0) {
        //std::cout << "Genero un soldado montado de rango" << std::endl;
        if (IA::Instance() -> getUnitManager() -> isSolvent(Enumeration::UnitCost::MountedRangedMetalCost, Enumeration::UnitCost::MountedRangedCrystalCost)) {
            // Unit type
            Enumeration::UnitType unitData = Enumeration::UnitType::AdvancedR; 
            IA::Instance() -> getUnitManager() -> createTroop(unitData);
        }
    } else {
        IA::Instance() -> getTree() -> setRequireBarn(true);
        //children[0] -> question();
    }
}