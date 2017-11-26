#include "BarnNode.h"

BarnNode::BarnNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

BarnNode::~BarnNode(){

}