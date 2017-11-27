#include "WorkshopNode.h"
#include "../IA.h"

WorkshopNode::WorkshopNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

WorkshopNode::~WorkshopNode(){
    delete father;
}

void WorkshopNode::question() {
    //std::cout << Construyo un taller << std::endl;
    //ToDo: Construir taller
    IA::getInstance()->buildWorkshop();
}