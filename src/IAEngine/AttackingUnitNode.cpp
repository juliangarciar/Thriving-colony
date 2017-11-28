#include "AttackingUnitNode.h"
#include "RangeAttackNode.h"
#include "MeleeAttackNode.h"

AttackingUnitNode::AttackingUnitNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = new Node*[2];
    children[0] = new RangeAttackNode(this);
    children[1] = new MeleeAttackNode(this); 
}

AttackingUnitNode::~AttackingUnitNode(){
    delete father;
    delete[] children;
}

void AttackingUnitNode::question() {

}