#include "MoveTroopsNode.h"

#include <IA.h>
#include <Human.h>
#include <IOEngine/IO.h>

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
    //Game::Instance() -> getEventManager() -> triggerEvent(Enumeration::EventType::DeployTroopsIA);
    IA::Instance() -> getUnitManager() -> deployAllTroops(Human::Instance()->getHallPosition());
}