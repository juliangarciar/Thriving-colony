#include "CreatureNode.h"
#include "../IA.h"

CreatureNode::CreatureNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

CreatureNode::~CreatureNode(){
    delete father;
}

bool CreatureNode::question() {
    return IA::getInstance()->getCityLevel() >= tree -> getCreatureMilestone();
}

void CreatureNode::response(){
    //std::cout << Genero una criatura << std::endl;
    //ToDo: Generar criatura
    IA::getInstance()-> increaseMeleeAmount();
}