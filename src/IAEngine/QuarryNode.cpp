#include "QuarryNode.h"
#include "../IA.h"

QuarryNode::QuarryNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

QuarryNode::~QuarryNode(){
    delete father;
}

void QuarryNode::question() {
    std::cout << "Construyo una cantera" << std::endl;
    //ToDo: Mirar coordenadas donde construir y ponerselas en el vector3
    if (IA::getInstance() -> getBuildings() -> isSolvent(Enumeration::BuildingCost::QuarryMetalCost, Enumeration::BuildingCost::QuarryCrystalCost, Enumeration::Team::IA)) {
        Vector3<float> *v = IA::getInstance() -> determinatePositionBuilding();
        IA::getInstance() -> getBuildings() -> buildBuilding(v, Enumeration::BuildingType::Quarry, Enumeration::Team::IA);
    }
}