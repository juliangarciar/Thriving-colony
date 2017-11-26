#include "MountedMeleeNode.h"

MountedMeleeNode::MountedMeleeNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

MountedMeleeNode::~MountedMeleeNode(){

}