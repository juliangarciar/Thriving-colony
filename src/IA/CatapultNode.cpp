#include "CatapultNode.h"

CatapultNode::CatapultNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

CatapultNode::~CatapultNode(){
    delete father;
}

void CatapultNode::question() {
    //std::cout << Genero una catapulta << std::endl;
    //ToDo: Generar catapulta
    IA::getInstance()-> increaseSiegeAmount();
}