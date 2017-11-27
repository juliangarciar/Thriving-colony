#include "ArmyNode.h"
#include "UnitNode.h"
#include "BuildingNode.h"

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
    if (tree -> getNeedSoldiers()){
        children[0] -> question();
    } else {
        //Second subbranch: Buildings
        if (tree -> getNeedBuildings()) {
            children[1] -> question();
        }
    }
}