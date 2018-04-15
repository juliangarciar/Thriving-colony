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
    if (IA::Instance() -> getBuildingManager() -> getAmount("Workshop") > 0) {
        //std::cout << "Genero un ariete" << std::endl;
        if (IA::Instance() -> getUnitManager() -> checkCanPay("Desintegrator")) {
            // Unit type
            IA::Instance() -> getUnitManager() -> createTroop("Desintegrator");
        }
    } else {
        IA::Instance() -> getTree() -> setRequireWorkshop(true);
        //children[0] -> question();
    }
}