#include "SchoolNode.h"
#include "../IA.h"

SchoolNode::SchoolNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

SchoolNode::~SchoolNode(){
    delete father;
}

void SchoolNode::question() {
    //std::cout << "Contruyo una escuela" << std::endl;
    //ToDo: Mirar coordenadas donde construir y ponerselas en el vector3
    IA::getInstance() -> buildBuilding(550, new Vector3<float>(0, 0, 0), Enumeration::BuildingType::School, false);
}