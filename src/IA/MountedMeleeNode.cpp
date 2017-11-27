#include "MountedMeleeNode.h"
#include "../IA.h"

MountedMeleeNode::MountedMeleeNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

MountedMeleeNode::~MountedMeleeNode(){
    delete father;
}

void MountedMeleeNode::question() {
    //std::cout << Genero un soldado montado melee << std::endl;
    //ToDo: Generar soldado montado melee
    IA::getInstance()-> increaseMeleeAmount();
}