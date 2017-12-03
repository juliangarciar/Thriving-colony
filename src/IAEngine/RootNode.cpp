#include "RootNode.h"
#include "AttackNode.h"
#include "DefendNode.h"
#include "DevelopCityNode.h"
#include "VeryHappyTree.h"


RootNode::RootNode() : Node() {
    father = 0;
    children = new Node*[3];
    children[0] = new AttackNode(this);
    children[1] = new DefendNode(this);
    children[2] = new VeryHappyTree(this);
}

RootNode::~RootNode(){
    delete father;
    delete[] children;
}

void RootNode::question() {
    //First branch: Attacking the enemy
    if (tree -> readyToAttack()) {
        children[0] -> question();
    } else  {
        //Second branch: Being attacked
        if (tree -> getUnderAttack()){
            children[1] -> question();
        } else {
            //Third branch: Peaceful, develop the city
            children[2] -> question();
        }
    }
}