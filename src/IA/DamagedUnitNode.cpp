#include "DamagedUnitNode.h"
#include "RangeAttackNode.h"
#include "MeleeAttackNode.h"

DamagedUnitNode::DamagedUnitNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = new Node*[2];
    children[0] = new RangeAttackNode(this);
    children[1] = new MeleeAttackNode(this);
}

DamagedUnitNode::~DamagedUnitNode(){
    delete father;
    delete[] children;
}