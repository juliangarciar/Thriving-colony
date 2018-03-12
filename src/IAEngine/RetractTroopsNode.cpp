#include "RetractTroopsNode.h"

#include <IA.h>
#include <IOEngine/IO.h>

RetractTroopsNode::RetractTroopsNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

RetractTroopsNode::~RetractTroopsNode() {
    delete father;
}

void RetractTroopsNode::question() {
    IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::RetractingTroops);
    //std::cout << "Me retiro" << std::endl;
    IO::Instance() -> getEventManager() -> triggerEvent(Enumeration::EventType::RetractTroopsIA);
}