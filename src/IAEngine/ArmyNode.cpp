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

ArmyNode::~ArmyNode(){
    delete father;
    delete[] children;
}

void ArmyNode::question() {
    //First subbranch: Units
    // Goal oriented behaviour
    //requirement have higher priority
    if (IA::getInstance() -> getTree() -> getRequireBarrack() || IA::getInstance() -> getTree() -> getRequireBarn() || IA::getInstance() -> getTree() -> getRequireWorkshop()) {
        children[1] -> question();
        return;
    } 
    if (IA::getInstance() -> getTree() -> getNeedSoldiers()){
        if (IA::getInstance() -> getCitizens() < 10) {
            IA::getInstance() -> getTree() -> setRequireCitizens(true);
        } else {
            children[0] -> question();
        }
    } else {
        //Second subbranch: Buildings
        if (IA::getInstance() -> getTree() -> getNeedBuildings()) {
            children[1] -> question();
        }
    }
}