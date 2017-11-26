#include "WallNode.h"

WallNode::WallNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

WallNode::~WallNode(){
    delete father;
}

void WallNode::question() {
    //std::cout << Construyo una muralla << std::endl;
    //ToDo: Construir muralla
    IA::getInstance()->increaseWallAmount();
}