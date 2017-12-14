#include "SiderurgyNode.h"
#include "../IA.h"

SiderurgyNode::SiderurgyNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

SiderurgyNode::~SiderurgyNode(){
    delete father;
}

void SiderurgyNode::question() {
    //std::cout << Construyo una siderurgia << std::endl;
    //ToDo: Mirar coordenadas donde construir y ponerselas en el vector3
    IA::getInstance() -> getBuildings() -> buildBuilding(1000, new Vector3<float>(0, 0, 0), Enumeration::BuildingType::Siderurgy, false);
}