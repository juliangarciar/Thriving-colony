#include "RootNode.h"
#include "AttackNode.h"
#include "DefendNode.h"
#include "DevelopCityNode.h"


RootNode::RootNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = new Node*[4];
    children[0] = new AttackNode(this);
    children[1] = new DefendNode(this);
    children[1] = new DevelopCityNode(this);

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