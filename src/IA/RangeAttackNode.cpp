#include "RangeAttackNode.h"

RangeAttackNode::RangeAttackNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

RangeAttackNode::~RangeAttackNode(){
    delete father;
}