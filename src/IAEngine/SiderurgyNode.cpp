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
    //std::cout << "Construyo una siderurgia" << std::endl;
    //ToDo: Mirar coordenadas donde construir y ponerselas en el vector3
    Vector3<float> *v = IA::getInstance() -> determinatePositionBuilding();
    IA::getInstance() -> getBuildings() -> buildBuilding(v, Enumeration::BuildingType::Siderurgy, Enumeration::Team::IA);
}