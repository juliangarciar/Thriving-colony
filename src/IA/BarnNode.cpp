#include "BarnNode.h"
#include "../IA.h"

BarnNode::BarnNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

BarnNode::~BarnNode(){
    delete father;
}

void BarnNode::question() {
    //std::cout << Construyo un establo << std::endl;
    //ToDo: Construir establo
    IA::getInstance()->buildBarn();
}