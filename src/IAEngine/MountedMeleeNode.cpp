#include "MountedMeleeNode.h"
#include "BarnNode.h"
#include "../IA.h"

MountedMeleeNode::MountedMeleeNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
    /*
    children =  new Node*[1];
    children[0] = new BarnNode(this);
    */
}

MountedMeleeNode::~MountedMeleeNode() {
    delete father;
    //delete[] children;
}

void MountedMeleeNode::question() {
    IA::getInstance() -> setChoiceIndex(Enumeration::IAChoices::TrainMountedMelee);
    if (IA::getInstance() -> getBuildingManager() -> getAmount(Enumeration::BuildingType::Barn) > 0) {
    //std::cout << "Genero un soldado montado melee" << std::endl;
        if (IA::getInstance() -> getUnitManager() -> isSolvent(Enumeration::UnitCost::MountedMeleeMetalCost, Enumeration::UnitCost::MountedMeleeCrystalCost)) {
            // Unit type
            Enumeration::UnitType unitData = Enumeration::UnitType::AdvancedM; 
            IA::getInstance() -> getUnitManager() -> createTroop(unitData);
        }
    } else {
        IA::getInstance() -> getTree() -> setRequireBarn(true);
        //children[0] -> question();
    }
}