#include "ArmyNode.h"
#include "UnitNode.h"
#include "BuildingNode.h"
#include "../IA.h"

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
        if (IA::getInstance()->getBarrackBuilt() != true || (IA::getInstance()->getCityLevel() >= barnMilestone && IA::getInstance()->getBarnBuilt() != true) || (IA::getInstance()->getCityLevel() >= workshopMilestone && IA::getInstance()->getWorkshopBuilt() != true) || (IA::getInstance()->getCityLevel() >= wallMilestone && IA::getInstance()->getWallBuilt() != true) || IA::getInstance()->getCityLevel() >= towerMilestone) {
            buildingsBranch();
        }
    }
}