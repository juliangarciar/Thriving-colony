#include "RangeFootmenNode.h"
#include "BarrackNode.h"
#include "../IA.h"

RangeFootmenNode::RangeFootmenNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = new Node*[1];
    children[0] = new BarrackNode(this);
}

RangeFootmenNode::~RangeFootmenNode(){
    delete father;
    delete[] children;
}

void RangeFootmenNode::question() {
    if (IA::getInstance() -> getBarrackBuilt()) {
        std::cout << "Genero un soldado a pie de rango" << std::endl;
        if (IA::getInstance() -> getUnitManager() -> isSolvent(Enumeration::UnitCost::RangedFootmenMetalCost, Enumeration::UnitCost::RangedFootmenCrystalCost, Enumeration::Team::IA)) {
            // Unit type
            Enumeration::UnitType unitData; 
            unitData.unitClass = Enumeration::UnitType::Class::Ranged; 
            unitData.unitSubClass = Enumeration::UnitType::SubClass::StandardR;
            // WTF?
            Vector3<float>* vectorData = new Vector3<float>();

            IA::getInstance() -> getUnitManager() -> createTroop(vectorData, unitData);
        }
    } else {
        children[0] -> question();
    }
}