#include "RetractTroopsNode.h"
#include "../Game.h"
#include "../IA.h"

RetractTroopsNode::RetractTroopsNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

RetractTroopsNode::~RetractTroopsNode() {
    delete father;
}

void RetractTroopsNode::question() {

    IA::getInstance() -> setChoiceIndex(Enumeration::IAChoices::RetractingTroops);
    //std::cout << "Me retiro" << std::endl;
    Game::Instance() -> getEvents() -> triggerEvent(Enumeration::EventType::RetractTroopsIA);
}