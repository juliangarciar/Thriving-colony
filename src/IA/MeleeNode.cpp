#include "MeleeNode.h"
#include "CreatureNode.h"
#include "MountedMeleeNode.h"
#include "MeleeFootmenNode.h"

MeleeNode::MeleeNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = new Node*[3];
    children[0] = new CreatureNode(this);
    children[1] = new MountedMeleeNode(this);
    children[2] = new MeleeFootmenNode(this);
}

MeleeNode::~MeleeNode(){

}

void MeleeNode::question() {
    //std::cout << Voy a hacer melees
    if (IA::getInstance()->getCityLevel() >= tree -> getCreatureMilestone()) {
            children[0] -> question();
        } else {
            //First subsubsubbranch: With creature
            if (IA::getInstance()->getCityLevel() >= tree -> getMountedCreatureMilestone()) {
                children[1] -> question();
            } else {
                //Second subsubsubbranch: Without creature
                children[2] -> question();
            }
        }
}