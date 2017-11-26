#include "TowerNode.h"

TowerNode::TowerNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

TowerNode::~TowerNode(){
    delete father;
}

void TowerNode::question() {
    //std::cout << Construyo un torre << std::endl;
    //ToDo: Construir torre
    IA::getInstance()->increaseTowerAmount();
}