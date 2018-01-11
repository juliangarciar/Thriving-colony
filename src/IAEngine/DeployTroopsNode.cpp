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
    std::cout<<"Despliego tropas"<<std::endl;
    Game::Instance() -> getEvents() -> triggerEvent(Enumeration::DeployTroopsIA);
}