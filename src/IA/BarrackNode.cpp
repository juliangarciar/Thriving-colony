#include "BarrackNode.h"

BarrackNode::BarrackNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

BarrackNode::~BarrackNode(){

}