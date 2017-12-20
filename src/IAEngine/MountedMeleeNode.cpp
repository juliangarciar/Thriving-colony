#include "MountedMeleeNode.h"
#include "../IA.h"

MountedMeleeNode::MountedMeleeNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

MountedMeleeNode::~MountedMeleeNode(){
    delete father;
}

void MountedMeleeNode::question() {
    std::cout << "Genero un soldado montado melee" << std::endl;
    //ToDo: Generar soldado montado melee
    //IA::getInstance()-> increaseMeleeAmount();
    if (IA::getInstance() -> getUnitManager() -> isSolvent(Enumeration::UnitCost::MountedMeleeMetalCost, Enumeration::UnitCost::MountedMeleeCrystalCost, Enumeration::Team::IA)) {
        // Unit type
        Enumeration::UnitType unitData; 
        unitData.unitClass = Enumeration::UnitType::Class::Melee; 
        unitData.unitSubClass = Enumeration::UnitType::SubClass::AdvancedM;
        // WTF?
        Vector3<float>* vectorData = new Vector3<float>();

        IA::getInstance() -> getUnitManager() -> createTroop(vectorData, unitData);
    }
}