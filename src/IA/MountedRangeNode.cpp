#include "MountedRangeNode.h"
#include "../IA.h"

MountedRangeNode::MountedRangeNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

MountedRangeNode::~MountedRangeNode(){
    delete father;
}

void MountedRangeNode::question() {
    //std::cout << Genero un soldado montado de rango << std::endl;
    //ToDo: Generar soldado montado de rango
    IA::getInstance()-> increaseRangeAmount();
}