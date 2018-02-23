#include "AttackNode.h"
#include "MoveTroopsNode.h"
#include "RetractTroopsNode.h"
#include <IA.h>


AttackNode::AttackNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = new Node*[4];
    children[0] = new MoveTroopsNode(this);
    children[1] = new RetractTroopsNode(this);

}

AttackNode::~AttackNode() {
    delete father;
    delete[] children;
}

void AttackNode::question() {
    //To Do: Attack the enemy
    if (IA::Instance() -> getUnitManager() -> areTroopsDeployed() == false) {
        children[0] -> question();
    } else {
        if (IA::Instance() -> losingBattle()) {
            children[1] -> question();
        } else {
            //Game::Instance() -> getEvents() -> triggerEvent(Enumeration::EventType::DeployTroops);
        }
    }
}