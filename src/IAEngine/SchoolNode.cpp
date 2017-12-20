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
    std::cout << "Contruyo una escuela" << std::endl;
    //ToDo: Mirar coordenadas donde construir y ponerselas en el vector3
    if (IA::getInstance() -> getBuildingManager() -> isSolvent(Enumeration::BuildingCost::SchoolMetalCost, Enumeration::BuildingCost::SchoolCrystalCost, Enumeration::Team::IA)) {
        Vector3<float> *v = IA::getInstance() -> determinatePositionBuilding();
        IA::getInstance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::School, Enumeration::Team::IA);
    }
}