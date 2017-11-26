#include "UnitNode.h"
#include "MeleeNode.h"
#include "RangeNode.h"
#include "SiegeNode.h"

UnitNode::UnitNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = new Node*[3];
    children[0] = new MeleeNode(this);
    children[1] = new RangeNode(this);
    children[2] = new SiegeNode(this);
}

UnitNode::~UnitNode(){

}