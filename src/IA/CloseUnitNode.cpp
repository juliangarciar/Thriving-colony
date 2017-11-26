#include "CloseUnitNode.h"
#include "RangeAttackNode.h"
#include "MeleeAttackNode.h"

CloseUnitNode::CloseUnitNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = new Node*[2];
    children[0] = new RangeAttackNode(this);
    children[1] = new MeleeAttackNode(this);
}

CloseUnitNode::~CloseUnitNode(){

}