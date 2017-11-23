#include "CriatureNode.h"

CriatureNode::CriatureNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

CriatureNode::~CriatureNode(){

}