#include "ResourceNode.h"
#include "SiderurgyNode.h"
#include "QuarryNode.h"

ResourceNode::ResourceNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = new Node*[2];
    children[0] = new SiderurgyNode(this);
    children[1] = new QuarryNode(this);
}

ResourceNode::~ResourceNode(){

}