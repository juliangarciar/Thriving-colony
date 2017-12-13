#include "RootNode.h"
#include "AttackNode.h"
#include "DefendNode.h"
#include "DevelopCityNode.h"
#include "VeryHappyTree.h"

#include <iostream>

RootNode::RootNode() : Node() {
    clock = 200;
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
    if (clock == 0) {
        clock = 100;
        std::cout<<"llega2"<<std::endl;
        //First branch: Attacking the enemy
        if (tree -> readyToAttack()) {
            std::cout<<"llega3"<<std::endl;
            children[0] -> question();
        } else  {
            //Second branch: Being attacked
            if (tree -> getUnderAttack()){
                std::cout<<"llega4"<<std::endl;
                children[1] -> question();
            } else {
                //Third branch: Peaceful, develop the city
                std::cout<<"llega5"<<std::endl;
                children[2] -> question();
            }
        }
    } else {
        clock--;
    }
}