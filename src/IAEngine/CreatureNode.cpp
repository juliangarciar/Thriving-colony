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
    if (IA::getInstance() -> getBarnBuilt()) {
        std::cout << "Genero una criatura" << std::endl;
        //ToDo: Generar criatura
        if (IA::getInstance() -> getUnitManager() -> isSolvent(Enumeration::UnitCost::CreatureMetalCost, Enumeration::UnitCost::CreatureCrystalCost, Enumeration::Team::IA)) {
            // Unit type
            Enumeration::UnitType unitData; 
            unitData.unitClass = Enumeration::UnitType::Class::Melee; 
            unitData.unitSubClass = Enumeration::UnitType::SubClass::Idol; //????????
            // WTF?
            Vector3<float>* vectorData = new Vector3<float>();

            IA::getInstance() -> getUnitManager() -> createTroop(vectorData, unitData);
        }
    } else {
        children[0] -> question();
    }
}