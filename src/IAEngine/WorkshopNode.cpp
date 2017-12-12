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
    //ToDo: Mirar coordenadas donde construir y ponerselas en el vector3
    //IA::getInstance() -> buildBuilding(800, new Vector3<float>(0, 0, 0), Enumeration::BuildingType::Workshop, false);
}