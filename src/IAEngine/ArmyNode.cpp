#include "ArmyNode.h"
#include "UnitNode.h"
#include "BuildingNode.h"
#include "../IA.h"

ArmyNode::ArmyNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = new Node*[2];
    children[0] = new UnitNode(this);
    children[1] = new BuildingNode(this);
}

ArmyNode::~ArmyNode() {
    delete father;
    delete[] children;
}

void ArmyNode::question() {
    //First subbranch: Units
    // Goal oriented behaviour
    //requirement have higher priority
    if (IA::Instance() -> getTree() -> getRequireBarrack() || IA::Instance() -> getTree() -> getRequireBarn() || IA::Instance() -> getTree() -> getRequireWorkshop()) {
        children[1] -> question();
        return;
    } 
    if (IA::Instance() -> getTree() -> getNeedSoldiers()) {
        if (IA::Instance() -> getCitizens() < 10) {
            IA::Instance() -> getTree() -> setRequireCitizens(true);
        } else {
            children[0] -> question();
        }
    } else {
        //Second subbranch: Buildings
        if (IA::Instance() -> getTree() -> getNeedBuildings()) {
            children[1] -> question();
        }
    }
}