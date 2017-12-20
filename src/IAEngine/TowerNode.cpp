#include "TowerNode.h"
#include "../IA.h"

TowerNode::TowerNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

TowerNode::~TowerNode(){
    delete father;
}

void TowerNode::question() {
    //std::cout << "Construyo un torre" << std::endl;
    //ToDo: Mirar coordenadas donde construir y ponerselas en el vector3
    if (IA::getInstance() -> getBuildingManager() -> isSolvent(Enumeration::BuildingCost::TowerMetalCost, Enumeration::BuildingCost::TowerCrystalCost, Enumeration::Team::IA)) {
        Vector3<float> *v = IA::getInstance() -> determinatePositionBuilding();
        IA::getInstance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::Tower, Enumeration::Team::IA);
        //AUmentar el numero de torres va en el constructorinoinoioinoino
    }
}