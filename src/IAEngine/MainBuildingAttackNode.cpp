#include "MainBuildingAttackNode.h"

MainBuildingAttackNode::MainBuildingAttackNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

MainBuildingAttackNode::~MainBuildingAttackNode(){
    delete father;
}

void MainBuildingAttackNode::question() {

}