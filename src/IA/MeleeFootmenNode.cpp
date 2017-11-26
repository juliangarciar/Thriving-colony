#include "MeleeFootmenNode.h"

MeleeFootmenNode::MeleeFootmenNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

MeleeFootmenNode::~MeleeFootmenNode(){
    delete father;
}

void MeleeFootmenNode::question() {
    //std::cout << Genero un soldado a pie melee << std::endl;
    //ToDo: Generar soldado a pie melee
    IA::getInstance()-> increaseMeleeAmount();
}