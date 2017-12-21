#include "AttackNode.h"
#include "MoveTroopsNode.h"
#include "RetractTroopsNode.h"
#include "../IA.h"
//#include "../Game.h"


AttackNode::AttackNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = new Node*[4];
    children[0] = new MoveTroopsNode(this);
    children[1] = new RetractTroopsNode(this);

}

AttackNode::~AttackNode(){
    delete father;
    delete[] children;
}

void AttackNode::question() {
    //std::cout << "Voy a atacar" << std::endl;
    //To Do: Attack the enemy
    if (IA::getInstance() -> getDeployedTroops()) {
        children[0] -> question();
    } else {
        if (IA::getInstance() -> losingBattle()) {
            children[1] -> question();
        } else {
            //Game::Instance() -> getEvents() -> triggerEvent(Enumeration::EventType::DeployTroops);
        }
    }
}