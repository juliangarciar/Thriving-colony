#include "CatapultNode.h"
#include "WorkshopNode.h"
#include <IA.h>

CatapultNode::CatapultNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
    /*
    children = new Node*[1];
    children[0] = new WorkshopNode(this);
    */
}

CatapultNode::~CatapultNode() {
    delete father;
    //delete[] children;
}

void CatapultNode::question() {

    IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::TrainCatapult);
    if (IA::Instance() -> getBuildingManager() -> getAmount(Enumeration::BuildingType::Workshop) > 0) {
        //std::cout << "Genero una catapulta" << std::endl;
        if (IA::Instance() -> getUnitManager() -> isSolvent(Enumeration::UnitCost::CatapultMetalCost, Enumeration::UnitCost::CatapultCrystalCost)) {
            // Unit type
            Enumeration::UnitType unitData = Enumeration::UnitType::Launcher; 
            IA::Instance() -> getUnitManager() -> createTroop(unitData);
        }
    } else {
        IA::Instance() -> getTree() -> setRequireWorkshop(true);
        //children[0] -> question();
    }
}