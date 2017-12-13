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
    Vector3<float> *v = IA::getInstance() -> determinatePositionBuilding();
    IA::getInstance() -> getBuildings() -> buildBuilding(550, v, Enumeration::BuildingType::School, false);
}