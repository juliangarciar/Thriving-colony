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
    if (IA::getInstance() -> getBuildingManager() -> isSolvent(Enumeration::BuildingCost::SiderurgyMetalCost, Enumeration::BuildingCost::SiderurgyCrystalCost, Enumeration::Team::IA)) {
        Vector3<float> *v = IA::getInstance() -> determinatePositionBuilding();
        IA::getInstance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::Siderurgy, Enumeration::Team::IA);
    }
}