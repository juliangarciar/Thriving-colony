#include "WallAttackNode.h"

WallAttackNode::WallAttackNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

WallAttackNode::~WallAttackNode(){

}

void WallAttackNode::question() {

}