#include "MountedRangeNode.h"
#include "BarnNode.h"
#include "../IA.h"

MountedRangeNode::MountedRangeNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = new Node*[1];
    children[0] = new BarnNode(this);
}

MountedRangeNode::~MountedRangeNode(){
    delete father;
    delete[] children;
}

void MountedRangeNode::question() {
    if (IA::getInstance() -> getBarnBuilt()) {
        std::cout << "Genero un soldado montado de rango" << std::endl;
        if (IA::getInstance() -> getUnitManager() -> isSolvent(Enumeration::UnitCost::MountedRangedMetalCost, Enumeration::UnitCost::MountedRangedCrystalCost, Enumeration::Team::IA)) {
            // Unit type
            Enumeration::UnitType unitData; 
            unitData.unitClass = Enumeration::UnitType::Class::Ranged; 
            unitData.unitSubClass = Enumeration::UnitType::SubClass::StandardR;
            // WTF?
            //Vector3<float>* vectorData = new Vector3<float>();

            IA::getInstance() -> getUnitManager() -> createTroop(unitData);
        }
    } else {
        children[0] -> question();
    }
}