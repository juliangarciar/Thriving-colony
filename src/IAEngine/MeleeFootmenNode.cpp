#include "MeleeFootmenNode.h"
#include "../IA.h"

MeleeFootmenNode::MeleeFootmenNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

MeleeFootmenNode::~MeleeFootmenNode(){
    delete father;
}

void MeleeFootmenNode::question() {
    std::cout << "Genero un soldado a pie melee" << std::endl;
    //ToDo: Generar soldado a pie melee
    //Esto va en el constructor
    //IA::getInstance()-> increaseMeleeAmount();
    if (IA::getInstance() -> getUnitManager() -> isSolvent(Enumeration::UnitCost::MeleeFootmenMetalCost, Enumeration::UnitCost::MeleeFootmenCrystalCost, Enumeration::Team::IA)) {
        // Unit type
        Enumeration::UnitType unitData; 
        unitData.unitClass = Enumeration::UnitType::Class::Melee; 
        unitData.unitSubClass = Enumeration::UnitType::SubClass::StandardM;
        // WTF?
        Vector3<float>* vectorData = new Vector3<float>();

        IA::getInstance() -> getUnitManager() -> createTroop(vectorData, unitData);
    }
}