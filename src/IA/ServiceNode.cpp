#include "ServiceNode.h"
#include "SchoolNode.h"
#include "HospitalNode.h"
#include "MarketNode.h"

ServiceNode::ServiceNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = new Node*[3];
    children[0] = new SchoolNode(this);
    children[1] = new HospitalNode(this);
    children[2] = new MarketNode(this);
}

ServiceNode::~ServiceNode(){

}