#include "MountedMeleeNode.h"
#include "BarnNode.h"
#include "../IA.h"

MountedMeleeNode::MountedMeleeNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children =  new Node*[1];
    children[0] = new BarnNode(this);
}

MountedMeleeNode::~MountedMeleeNode(){
    delete father;
    delete[] children;
}

void MountedMeleeNode::question() {
<<<<<<< HEAD
    //std::cout << "Genero un soldado montado melee" << std::endl;
    //ToDo: Generar soldado montado melee
    //IA::getInstance()-> increaseMeleeAmount();
    if (IA::getInstance() -> getUnitManager() -> isSolvent(Enumeration::UnitCost::MountedMeleeMetalCost, Enumeration::UnitCost::MountedMeleeCrystalCost, Enumeration::Team::IA)) {
        // Unit type
        Enumeration::UnitType unitData; 
        unitData.unitClass = Enumeration::UnitType::Class::Melee; 
        unitData.unitSubClass = Enumeration::UnitType::SubClass::AdvancedM;
        // WTF?
        //Vector3<float>* vectorData = new Vector3<float>();

        IA::getInstance() -> getUnitManager() -> createTroop(unitData);
=======
    if (IA::getInstance() -> getBarnBuilt()) {
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
    } else {
        children[0] -> question();
>>>>>>> 2210761c7f7933c48fc17aecec7fd00d54da97fd
    }
}