#include "BarrackNode.h"
#include "../IA.h"


BarrackNode::BarrackNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

BarrackNode::~BarrackNode(){
    delete father;
}

void BarrackNode::question() {
    //std::cout << Construyo un cuartel << std::endl;
    //ToDo: Mirar coordenadas donde construir y ponerselas en el vector3
    IA::getInstance() -> getBuildings() -> buildBuilding(720, new Vector3<float>(0, 0, 0), Enumeration::BuildingType::Barrack, false);
}