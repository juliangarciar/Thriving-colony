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
    //std::cout << Despliego mis tropas para defender << std::endl;
    //ToDo: Desplegar tropas
    IA::getInstance()-> deployTroops();
}