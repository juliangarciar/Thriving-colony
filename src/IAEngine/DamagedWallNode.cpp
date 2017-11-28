#include "DamagedWallNode.h"

DamagedWallNode::DamagedWallNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

DamagedWallNode::~DamagedWallNode(){
    delete father;
}

void DamagedWallNode::question() {

}