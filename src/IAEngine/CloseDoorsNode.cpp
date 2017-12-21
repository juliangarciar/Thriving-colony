#include "CloseDoorsNode.h"
#include "../Game.h"

CloseDoorsNode::CloseDoorsNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

CloseDoorsNode::~CloseDoorsNode(){
    delete father;
}

void CloseDoorsNode::question() {
    //std::cout << "Cierro las puertas" << std::endl;
    //ToDo: Cerrar puertas
    Game::Instance() -> getEvents() -> triggerEvent(Enumeration::EventType::CloseDoorsIA);
}