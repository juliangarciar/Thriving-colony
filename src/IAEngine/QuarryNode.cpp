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
    //std::cout << Construyo una cantera << std::endl;
    //ToDo: Mirar coordenadas donde construir y ponerselas en el vector3
    //IA::getInstance() -> buildBuilding(1000, new Vector3<float>(0, 0, 0), Enumeration::BuildingType::Quarry, false);
    IA::getInstance()->increaseQuarryAmount();
}