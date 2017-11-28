#include "CloseBuildingNode.h"

CloseBuildingNode::CloseBuildingNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

CloseBuildingNode::~CloseBuildingNode(){
    delete father;
}

void CloseBuildingNode::question() {

}