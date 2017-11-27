#include "CreatureNode.h"
#include "../IA.h"

CreatureNode::CreatureNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

CreatureNode::~CreatureNode(){
    delete father;
}

void CreatureNode::question() {
    //std::cout << Genero una criatura << std::endl;
    //ToDo: Generar criatura
    IA::getInstance()-> increaseMeleeAmount();
}