#include "RootNode.h"
#include "AttackNode.h"
#include "DefendNode.h"
#include "VeryHappyTree.h"
#include "HappyTree.h"
#include "NeutralTree.h"
#include "UnhappyTree.h"
#include "VeryUnhappyTree.h"
#include "../IA.h"

#include <iostream>

RootNode::RootNode() : Node() {
    father = 0;
}

RootNode::~RootNode(){
    delete father;
    delete[] children;
}

void RootNode::question() {
    //First branch: Attacking the enemy
    if (IA::getInstance() -> getTree() -> readyToAttack()) {
        children[0] -> question();
    } else  {
        //Second branch: Being attacked
        if (IA::getInstance() -> getUnderAttack()){
            children[1] -> question();
        } else {
            //Third branch: Peaceful, develop the city
            children[2] -> question();
        }
    }
}

void RootNode::init(Enumeration::IABehaviour behaviour) {
    children = new Node*[3];
    children[0] = new AttackNode(this);
    children[1] = new DefendNode(this);
    // Determine the thrid child based on the chosen behaviour
    switch (behaviour) {
        case Enumeration::IABehaviour::VeryHappy: 
            children[2] = new VeryHappyTree(this);
        break;
        case Enumeration::IABehaviour::Happy: 
            children[2] = new HappyTree(this);  
        break;
        case Enumeration::IABehaviour::Neutral:
            children[2] = new NeutralTree(this);
        break;
        case Enumeration::IABehaviour::Unhappy: 
            children[2] = new UnhappyTree(this);
        break;
        case Enumeration::IABehaviour::VeryUnhappy: 
            children[2] = new VeryUnhappyTree(this);
        break;
    }
    
}