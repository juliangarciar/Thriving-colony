#include "RetractTroopsNode.h"
#include "../Game.h"

RetractTroopsNode::RetractTroopsNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

RetractTroopsNode::~RetractTroopsNode(){
    delete father;
}

void RetractTroopsNode::question() {
    //std::cout << "Me retiro" << std::endl;
    Game::Instance() -> getEvents() -> triggerEvent(Enumeration::EventType::RetractTroopsIA);
}