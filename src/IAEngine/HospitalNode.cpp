#include "HospitalNode.h"
#include "../IA.h"

HospitalNode::HospitalNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

HospitalNode::~HospitalNode(){
    delete father;
}

void HospitalNode::question() {
    //std::cout << "Contruyo un hospital" << std::endl;
    //ToDo: Mirar coordenadas donde construir y ponerselas en el vector3
    Vector3<float> *v = IA::getInstance() -> determinatePositionBuilding();
    IA::getInstance() -> getBuildings() -> buildBuilding(v, Enumeration::BuildingType::Hospital, Enumeration::Team::IA);
}