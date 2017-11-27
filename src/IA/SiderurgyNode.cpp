#include "SiderurgyNode.h"
#include "../IA.h"

SiderurgyNode::SiderurgyNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

SiderurgyNode::~SiderurgyNode(){
    delete father;
}

void SiderurgyNode::question() {
    //std::cout << Construyo una siderurgia << std::endl;
    //ToDo: Construir siderurgia
    IA::getInstance()->increaseSiderurgyAmount();
}