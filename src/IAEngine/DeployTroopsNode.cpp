#include "DeployTroopsNode.h"
#include "../IA.h"

DeployTroopsNode::DeployTroopsNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

DeployTroopsNode::~DeployTroopsNode(){
    delete father;
}

void DeployTroopsNode::question() {
    std::cout << "Despliego mis tropas para defender" << std::endl;
    //ToDo: Desplegar tropas
    IA::getInstance()-> deployTroops();
}