#include "HomeNode.h"

HomeNode::HomeNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

HomeNode::~HomeNode(){
    delete father;
}

void HomeNode::question() {
    //std::cout << Voy a invertir en casas << std::endl;
    //ToDo: Construir casas
    IA::getInstance() ->increaseCitizens();
}