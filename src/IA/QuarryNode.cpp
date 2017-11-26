#include "QuarryNode.h"

QuarryNode::QuarryNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

QuarryNode::~QuarryNode(){
    delete father;
}

void QuarryNode::question() {
    //std::cout << Construyo una cantera << std::endl;
    //ToDo: Construir cantera
    IA::getInstance()->increaseQuarryAmount();
}