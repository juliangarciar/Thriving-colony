#include "RamNode.h"
#include "WorkshopNode.h"
#include "../IA.h"

RamNode::RamNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = new Node*[1];
    children[0] = new WorkshopNode(this);
}

RamNode::~RamNode(){
    delete father;
    delete[] children;
}

void RamNode::question() {
    if (IA::getInstance() -> getWorkshopBuilt()) {
        std::cout << "Genero un ariete" << std::endl;
        if (IA::getInstance() -> getUnitManager() -> isSolvent(Enumeration::UnitCost::RamMetalCost, Enumeration::UnitCost::RamCrystalCost, Enumeration::Team::IA)) {
            // Unit type
            Enumeration::UnitType unitData; 
            unitData.unitClass = Enumeration::UnitType::Class::Ranged; // ????????????
            unitData.unitSubClass = Enumeration::UnitType::SubClass::Desintegrator;
            // WTF?
            Vector3<float>* vectorData = new Vector3<float>();

            IA::getInstance() -> getUnitManager() -> createTroop(vectorData, unitData);
        }
    } else {
        children[0] -> question();
    }
}