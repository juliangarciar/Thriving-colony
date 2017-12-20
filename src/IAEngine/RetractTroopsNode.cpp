#include "RetractTroopsNode.h"
#include "../IA.h"

RetractTroopsNode::RetractTroopsNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

RetractTroopsNode::~RetractTroopsNode(){
    delete father;
}

void RetractTroopsNode::question() {
    std::cout << "Me retiro" << std::endl;
    //ToDo: Retirar tropas tropas
    IA::getInstance()-> retractTroops();
}