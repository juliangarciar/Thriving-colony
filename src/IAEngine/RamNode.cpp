#include "RamNode.h"
#include "../IA.h"

RamNode::RamNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

RamNode::~RamNode(){
    delete father;
}

void RamNode::question() {
    //std::cout << Genero un ariete << std::endl;
    //ToDo: Generar ariete
    IA::getInstance()-> increaseSiegeAmount();
}