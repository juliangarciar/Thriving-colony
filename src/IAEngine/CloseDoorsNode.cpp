#include "CloseDoorsNode.h"
#include "../Game.h"
#include "../IA.h"

CloseDoorsNode::CloseDoorsNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

CloseDoorsNode::~CloseDoorsNode() {
    delete father;
}

void CloseDoorsNode::question() {

    IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::ClosingDoors);
    //std::cout << "Cierro las puertas" << std::endl;
    Game::Instance() -> getEvents() -> triggerEvent(Enumeration::EventType::CloseDoorsIA);
}