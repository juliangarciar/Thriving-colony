#include "RangeNode.h"
#include "MountedRangeNode.h"
#include "RangeFootmenNode.h"
#include "../IA.h"

RangeNode::RangeNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = new Node*[2];
    children[0] = new MountedRangeNode(this);
    children[1] = new RangeFootmenNode(this);
}

RangeNode::~RangeNode() {
    delete father;
    delete[] children;
}

void RangeNode::question() {
    //std::cout << "Voy a hacer rangos" << std::endl;
    //First subsubsubbranch: With creature
    if (IA::getInstance() -> getCityLevel() >= IA::getInstance() -> getTree()  -> getMountedCreatureMilestone()) {
        children[0] -> question();
    } else {
        //Second subsubsubbranch: Without creature
        children[1] -> question();
    }
}