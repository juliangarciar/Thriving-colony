#include "CreatureNode.h"
#include "BarnNode.h"
#include "../IA.h"

CreatureNode::CreatureNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = new Node*[1];
    children[0] = new BarnNode(this);
}

CreatureNode::~CreatureNode(){
    delete father;
}

void CreatureNode::question() {

    IA::getInstance() -> setChoiceIndex(Enumeration::IAChoices::TrainCreature);
    if (IA::getInstance() -> getBarnBuilt()) {
        //std::cout << "Genero una criatura" << std::endl;
        if (IA::getInstance() -> getUnitManager() -> isSolvent(Enumeration::UnitCost::CreatureMetalCost, Enumeration::UnitCost::CreatureCrystalCost, Enumeration::Team::IA)) {
            // Unit type
            Enumeration::UnitType unitData = Enumeration::UnitType::Idol;
            // WTF?
            //Vector3<float>* vectorData = new Vector3<float>();

            IA::getInstance() -> getUnitManager() -> createTroop(unitData);
        }
    } else {
        children[0] -> question();
    }
}