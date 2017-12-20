#include "MountedRangeNode.h"
#include "../IA.h"

MountedRangeNode::MountedRangeNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

MountedRangeNode::~MountedRangeNode(){
    delete father;
}

void MountedRangeNode::question() {
    //std::cout << "Genero un soldado montado de rango" << std::endl;
    //ToDo: Generar soldado montado de rango
    //IA::getInstance()-> increaseRangeAmount();
    if (IA::getInstance() -> getUnitManager() -> isSolvent(Enumeration::UnitCost::MountedRangedMetalCost, Enumeration::UnitCost::MountedRangedCrystalCost, Enumeration::Team::IA)) {
        // Unit type
        Enumeration::UnitType unitData; 
        unitData.unitClass = Enumeration::UnitType::Class::Ranged; 
        unitData.unitSubClass = Enumeration::UnitType::SubClass::StandardR;
        // WTF?
        Vector3<float>* vectorData = new Vector3<float>();

        IA::getInstance() -> getUnitManager() -> createTroop(vectorData, unitData);
    }
}