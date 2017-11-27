#include "RetractTroopsNode.h"
#include "../IA.h"

RetractTroopsNode::RetractTroopsNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

RetractTroopsNode::~RetractTroopsNode(){
    delete father;
}

void RetractTroopsNode::question() {
    //std::cout << Despliego mis tropas para defender << std::endl;
    //ToDo: Desplegar tropas
    IA::getInstance()-> retractTroops();
}