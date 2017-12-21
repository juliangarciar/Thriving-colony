#include "DeployTroopsNode.h"
#include "../Game.h"

DeployTroopsNode::DeployTroopsNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

DeployTroopsNode::~DeployTroopsNode(){
    delete father;
}

void DeployTroopsNode::question() {
    //std::cout << "Despliego mis tropas para defender" << std::endl;
    Game::Instance() -> getEvents() -> triggerEvent(Enumeration::EventType::DeployTroopsIA);
}