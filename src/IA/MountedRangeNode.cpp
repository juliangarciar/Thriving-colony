#include "MountedRangeNode.h"

MountedRangeNode::MountedRangeNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

MountedRangeNode::~MountedRangeNode(){

}