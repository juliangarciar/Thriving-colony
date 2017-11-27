#include "UnitAttackNode.h"
#include "AttackingUnitNode.h"
#include "DamagedUnitNode.h"
#include "CloseUnitNode.h"

UnitAttackNode::UnitAttackNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = new Node*[3];
    children[0] = new AttackingUnitNode(this);
    children[1] = new DamagedUnitNode(this);
    children[2] = new CloseUnitNode(this);
}

UnitAttackNode::~UnitAttackNode(){
    delete father;
    delete[] children;
}