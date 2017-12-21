#include "MeleeFootmenNode.h"
#include "BarrackNode.h"
#include "../IA.h"

MeleeFootmenNode::MeleeFootmenNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = new Node*[1];
    children[0] = new BarrackNode(this);
}

MeleeFootmenNode::~MeleeFootmenNode(){
    delete father;
    delete[] children;
}

void MeleeFootmenNode::question() {
    if (IA::getInstance() -> getBarrackBuilt()) {
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
    } else {
        children[0] -> question();
    }
}