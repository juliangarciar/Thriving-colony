#include "MeleeNode.h"
#include "CriatureNode.h"
#include "MountedMeleeNode.h"
#include "MeleeFootmenNode.h"

MeleeNode::MeleeNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = new Node*[3];
    children[0] = new CriatureNode(this);
    children[1] = new MountedMeleeNode(this);
    children[2] = new MeleeFootmenNode(this);
}

MeleeNode::~MeleeNode(){

}