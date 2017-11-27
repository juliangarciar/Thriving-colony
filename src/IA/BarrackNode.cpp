#include "BarrackNode.h"
#include "../IA.h"


BarrackNode::BarrackNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

BarrackNode::~BarrackNode(){
    delete father;
}

void BarrackNode::question() {
    //std::cout << Construyo un cuartel << std::endl;
    //ToDo: Construir cuartel
    IA::getInstance()->buildBarrack();
}