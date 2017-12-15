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
    Vector3<float> *v = IA::getInstance() -> determinatePositionBuilding();
    IA::getInstance() -> getBuildings() -> buildBuilding(v, Enumeration::BuildingType::Workshop, Enumeration::Team::IA);
}