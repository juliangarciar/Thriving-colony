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
    //std::cout << "Ataco al enemigo" << std::endl;
    //ToDo: Fijar cento de mando como objetivo
    IA::getInstance()-> deployTroops();
}