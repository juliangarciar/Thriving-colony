#include "SiegeNode.h"
#include "RamNode.h"
#include "CatapultNode.h"

SiegeNode::SiegeNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = new Node*[2];
    children[0] = new RamNode(this);
    children[1] = new CatapultNode(this);
}

SiegeNode::~SiegeNode(){

}