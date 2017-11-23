#include "RamNode.h"

RamNode::RamNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

RamNode::~RamNode(){

}