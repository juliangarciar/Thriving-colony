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
    IA::getInstance() -> buildBuilding(750, new Vector3<float>(0, 0, 0), Enumeration::BuildingType::Hospital, false);
}