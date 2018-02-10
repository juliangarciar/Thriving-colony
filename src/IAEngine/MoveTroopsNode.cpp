#include "MoveTroopsNode.h"
#include "../IA.h"

MoveTroopsNode::MoveTroopsNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

MoveTroopsNode::~MoveTroopsNode(){
    delete father;
}

void MoveTroopsNode::question() {
    IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::Attacking);
    //std::cout << "Ataco al enemigo" << std::endl;
    //ToDo: Fijar centro de mando como objetivo
    Vector3<f32> p = IA::Instance() -> getHallPosition();
    p.x = p.x + 100;
    IA::Instance() -> getUnitManager() -> deployAllTroops(p);
}