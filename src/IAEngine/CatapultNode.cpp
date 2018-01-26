#include "CatapultNode.h"
#include "WorkshopNode.h"
#include "../IA.h"

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

    IA::getInstance() -> setChoiceIndex(Enumeration::IAChoices::TrainCatapult);
    if (IA::getInstance() -> getWorkshopBuilt()) {
        //std::cout << "Genero una catapulta" << std::endl;
        if (IA::getInstance() -> getUnitManager() -> isSolvent(Enumeration::UnitCost::CatapultMetalCost, Enumeration::UnitCost::CatapultCrystalCost, Enumeration::Team::IA)) {
            // Unit type
            Enumeration::UnitType unitData = Enumeration::UnitType::Launcher; 
            IA::getInstance() -> getUnitManager() -> createTroop(unitData);
        }
    } else {
        IA::getInstance() -> getTree() -> setRequireWorkshop(true);
        //children[0] -> question();
    }
}