#include "RamNode.h"
#include "WorkshopNode.h"
#include <IA.h>

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

    IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::TrainRam);
    if (IA::Instance() -> getBuildingManager() -> getAmount(Enumeration::BuildingType::Workshop) > 0) {
        //std::cout << "Genero un ariete" << std::endl;
        if (IA::Instance() -> getUnitManager() -> isSolvent(Enumeration::UnitCost::RamMetalCost, Enumeration::UnitCost::RamCrystalCost)) {
            // Unit type
            Enumeration::UnitType unitData = Enumeration::UnitType::Desintegrator;
            IA::Instance() -> getUnitManager() -> createTroop(unitData);
        }
    } else {
        IA::Instance() -> getTree() -> setRequireWorkshop(true);
        //children[0] -> question();
    }
}