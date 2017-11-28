#include "MarketNode.h"

MarketNode::MarketNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

MarketNode::~MarketNode(){
    delete father;
}

void MarketNode::question() {
    //std::cout << "Contruyo un mercado" << std::endl;
    //ToDo: Construir mercado
}