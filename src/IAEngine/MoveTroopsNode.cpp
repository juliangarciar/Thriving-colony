#include "MoveTroopsNode.h"
#include <IA.h>
#include <Game.h>

MoveTroopsNode::MoveTroopsNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

MoveTroopsNode::~MoveTroopsNode(){
    delete father;
}

void MoveTroopsNode::question() {
    IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::Attacking);
    //ToDo: Fijar centro de mando como objetivo
    IO::Instance() -> getEventManager() -> triggerEvent(Enumeration::EventType::DeployTroopsIA);
}