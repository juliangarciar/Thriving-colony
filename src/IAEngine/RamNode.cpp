#include "RamNode.h"
#include "../IA.h"

RamNode::RamNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

RamNode::~RamNode(){
    delete father;
}

void RamNode::question() {
    std::cout << "Genero un ariete" << std::endl;
    //ToDo: Generar ariete
    //IA::getInstance()-> increaseSiegeAmount();
    if (IA::getInstance() -> getUnitManager() -> isSolvent(Enumeration::UnitCost::RamMetalCost, Enumeration::UnitCost::RamCrystalCost, Enumeration::Team::IA)) {
        // Unit type
        Enumeration::UnitType unitData; 
        unitData.unitClass = Enumeration::UnitType::Class::Ranged; // ????????????
        unitData.unitSubClass = Enumeration::UnitType::SubClass::Desintegrator;
        // WTF?
        Vector3<float>* vectorData = new Vector3<float>();

        IA::getInstance() -> getUnitManager() -> createTroop(vectorData, unitData);
    }
}