#include "CatapultNode.h"

CatapultNode::CatapultNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

CatapultNode::~CatapultNode(){

}