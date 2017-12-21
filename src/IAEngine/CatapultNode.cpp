#include "CatapultNode.h"
#include "../IA.h"

CatapultNode::CatapultNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

CatapultNode::~CatapultNode(){
    delete father;
}

void CatapultNode::question() {
    //std::cout << "Genero una catapulta" << std::endl;
    //ToDo: Generar catapulta
    //TODO PRECIO
    //IA::getInstance()-> increaseSiegeAmount();
    if (IA::getInstance() -> getUnitManager() -> isSolvent(Enumeration::UnitCost::CatapultMetalCost, Enumeration::UnitCost::CatapultCrystalCost, Enumeration::Team::IA)) {
        // Unit type
        Enumeration::UnitType unitData; 
        unitData.unitClass = Enumeration::UnitType::Class::Ranged; // ????????????
        unitData.unitSubClass = Enumeration::UnitType::SubClass::Launcher;
        // WTF?
        //Vector3<float>* vectorData = new Vector3<float>();

        IA::getInstance() -> getUnitManager() -> createTroop(unitData);
    }
}