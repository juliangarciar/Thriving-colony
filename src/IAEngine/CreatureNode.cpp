#include "CreatureNode.h"
#include "BarnNode.h"
#include "../IA.h"

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

    IA::getInstance() -> setChoiceIndex(Enumeration::IAChoices::TrainCreature);
    if (IA::getInstance() -> getBuildingManager() -> getAmount(Enumeration::BuildingType::Barn) > 0) {
        //std::cout << "Genero una criatura" << std::endl;
        if (IA::getInstance() -> getUnitManager() -> isSolvent(Enumeration::UnitCost::CreatureMetalCost, Enumeration::UnitCost::CreatureCrystalCost)) {
            // Unit type
            Enumeration::UnitType unitData = Enumeration::UnitType::Idol;
            IA::getInstance() -> getUnitManager() -> createTroop(unitData);
        }
    } else {
        IA::getInstance() -> getTree() -> setRequireBarn(true);
        //children[0] -> question();
    }
}