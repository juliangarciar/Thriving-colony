#include "RangeFootmenNode.h"
#include "BarrackNode.h"
#include "../IA.h"

RangeFootmenNode::RangeFootmenNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
    /*
    children = new Node*[1];
    children[0] = new BarrackNode(this);
    */
}

RangeFootmenNode::~RangeFootmenNode() {
    delete father;
    //delete[] children;
}

void RangeFootmenNode::question() {

    IA::getInstance() -> setChoiceIndex(Enumeration::IAChoices::TrainRangedFootman);
    if (IA::getInstance() -> getBuildingManager() -> getAmount(Enumeration::BuildingType::Barrack) > 0) {
        //std::cout << "Genero un soldado a pie de rango" << std::endl;
        if (IA::getInstance() -> getUnitManager() -> isSolvent(Enumeration::UnitCost::RangedFootmenMetalCost, Enumeration::UnitCost::RangedFootmenCrystalCost, Enumeration::Team::IA)) {
            // Unit type
            Enumeration::UnitType unitData = Enumeration::UnitType::StandardR;
            IA::getInstance() -> getUnitManager() -> createTroop(unitData);
        }
    } else {
        IA::getInstance() -> getTree() -> setRequireBarrack(true);
        //children[0] -> question();
    }
}