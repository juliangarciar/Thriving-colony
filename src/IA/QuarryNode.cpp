#include "QuarryNode.h"

QuarryNode::QuarryNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

QuarryNode::~QuarryNode(){

}