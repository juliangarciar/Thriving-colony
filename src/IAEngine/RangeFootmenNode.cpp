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

    IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::TrainRangedFootman);
    if (IA::Instance() -> getBuildingManager() -> getAmount(Enumeration::BuildingType::Barrack) > 0) {
        //std::cout << "Genero un soldado a pie de rango" << std::endl;
        if (IA::Instance() -> getUnitManager() -> isSolvent(Enumeration::UnitCost::RangedFootmenMetalCost, Enumeration::UnitCost::RangedFootmenCrystalCost)) {
            // Unit type
            Enumeration::UnitType unitData = Enumeration::UnitType::StandardR;
            IA::Instance() -> getUnitManager() -> createTroop(unitData);
        }
    } else {
        IA::Instance() -> getTree() -> setRequireBarrack(true);
        //children[0] -> question();
    }
}