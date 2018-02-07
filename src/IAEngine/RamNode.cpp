#include "RamNode.h"
#include "WorkshopNode.h"
#include "../IA.h"

RamNode::RamNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
    /*
    children = new Node*[1];
    children[0] = new WorkshopNode(this);
    */
}

RamNode::~RamNode() {
    delete father;
    //delete[] children;
}

void RamNode::question() {

    IA::getInstance() -> setChoiceIndex(Enumeration::IAChoices::TrainRam);
    if (IA::getInstance() -> getBuildingManager() -> getAmount(Enumeration::BuildingType::Workshop) > 0) {
        //std::cout << "Genero un ariete" << std::endl;
        if (IA::getInstance() -> getUnitManager() -> isSolvent(Enumeration::UnitCost::RamMetalCost, Enumeration::UnitCost::RamCrystalCost)) {
            // Unit type
            Enumeration::UnitType unitData = Enumeration::UnitType::Desintegrator;
            IA::getInstance() -> getUnitManager() -> createTroop(unitData);
        }
    } else {
        IA::getInstance() -> getTree() -> setRequireWorkshop(true);
        //children[0] -> question();
    }
}