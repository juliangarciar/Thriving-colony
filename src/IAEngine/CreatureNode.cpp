#include "CreatureNode.h"
#include "BarnNode.h"
#include <IA.h>

CreatureNode::CreatureNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
    /*
    children = new Node*[1];
    children[0] = new BarnNode(this);
    */
}

CreatureNode::~CreatureNode() {
    delete father;
    //delete children;
}

void CreatureNode::question() {

    IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::TrainCreature);
    if (IA::Instance() -> getBuildingManager() -> getAmount(Enumeration::BuildingType::Barn) > 0) {
        //std::cout << "Genero una criatura" << std::endl;
        if (IA::Instance() -> getUnitManager() -> isSolvent(Enumeration::UnitCost::CreatureMetalCost, Enumeration::UnitCost::CreatureCrystalCost)) {
            // Unit type
            Enumeration::UnitType unitData = Enumeration::UnitType::Idol;
            IA::Instance() -> getUnitManager() -> createTroop(unitData);
        }
    } else {
        IA::Instance() -> getTree() -> setRequireBarn(true);
        //children[0] -> question();
    }
}