#include "HospitalNode.h"

HospitalNode::HospitalNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

HospitalNode::~HospitalNode(){
    delete father;
}

void HospitalNode::question() {
    //std::cout << "Contruyo un hospital" << std::endl;
    //ToDo: Construir hospital
}