#include "RangeFootmenNode.h"

RangeFootmenNode::RangeFootmenNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

RangeFootmenNode::~RangeFootmenNode(){
    delete father;
}

void RangeFootmenNode::question() {
    //std::cout << Genero un soldado a pie de rango << std::endl;
    //ToDo: Generar soldado a pie de rango
    IA::getInstance()-> increaseRangeAmount();
}