#include "TowerAttackNode.h"

TowerAttackNode::TowerAttackNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

TowerAttackNode::~TowerAttackNode(){
    delete father;
}

void TowerAttackNode::question() {

}