#include "RangeNode.h"
#include "MountedRangeNode.h"
#include "RangeFootmenNode.h"

RangeNode::RangeNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = new Node*[2];
    children[0] = new MountedRangeNode(this);
    children[1] = new RangeFootmenNode(this);
}

RangeNode::~RangeNode(){

}