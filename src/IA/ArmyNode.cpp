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

}