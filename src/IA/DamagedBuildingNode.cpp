#include "DamagedBuildingNode.h"

DamagedBuildingNode::DamagedBuildingNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

DamagedBuildingNode::~DamagedBuildingNode(){

}