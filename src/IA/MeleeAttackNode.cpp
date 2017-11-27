#include "MeleeAttackNode.h"

MeleeAttackNode::MeleeAttackNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

MeleeAttackNode::~MeleeAttackNode(){
    delete father;
}