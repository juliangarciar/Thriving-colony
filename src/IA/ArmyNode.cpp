#include "ArmyNode.h"
#include "UnitNode.h"
#include "BuildingNode.h"


ArmyNode::ArmyNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = new Node*[2];
    children[0] = new UnitNode(this);
    children[1] = new BuildingNode(this);
}

ArmyNode::~ArmyNode(){

}

void ArmyNode::question() {
    //First subbranch: Units
    if (IA::getInstance() -> getTree() -> calculateArmyCitizensRate() < armyThreshold){
        std::cout << "Voy a hacer unidades" << std::endl;
        unitsBranch();
    } else {
        //Second subbranch: Buildings
        std::cout << "Voy a hacer edificios" << std::endl;
        if (ia->getBarrackBuilt() != true || (ia->getCityLevel() >= barnMilestone && ia->getBarnBuilt() != true) || (ia->getCityLevel() >= workshopMilestone && ia->getWorkshopBuilt() != true) || (ia->getCityLevel() >= wallMilestone && ia->getWallBuilt() != true) || ia->getCityLevel() >= towerMilestone) {
            buildingsBranch();
        }
    }
}