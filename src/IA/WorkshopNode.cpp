#include "WorkshopNode.h"

WorkshopNode::WorkshopNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

WorkshopNode::~WorkshopNode(){

}