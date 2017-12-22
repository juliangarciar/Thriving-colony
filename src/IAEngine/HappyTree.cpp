#include "HappyTree.h"
#include "ServiceNode.h"
#include "ResourceNode.h"
#include "HomeNode.h"
#include "ArmyNode.h"
#include "../IA.h"

HappyTree::HappyTree(Node *fatherPnt) : BehaviourTree(){
    happinessThreshold = 80;
    quarryMilestone = 50;
    mountedCreatureMilestone = 80;
    wallMilestone = 70;
    towerMilestone = 90;
    barnMilestone = 60;
    workshopMilestone = 65;
    creatureMilestone = 100;

    metalThreshold = 1.5;
    crystalThreshold = 1.2;
    citizensThreshold = 2.5;
    armyThreshold = 0.1;
    meleeThreshold = 0.5;
    rangeThreshold = 0.45;
    siegeThreshold = 0.05;

    father = fatherPnt;
    children = new Node*[4];
    children[0] = new HomeNode(this);
    children[1] = new ServiceNode(this);
    children[2] = new ResourceNode(this);
    children[3] = new ArmyNode(this);
}
 
HappyTree::~HappyTree() {
    delete father;
    delete[] children;
}

void HappyTree::question() {
    //First branch: Homes
    if (IA::getInstance() -> getTree() -> calculateCitizensRate() < IA::getInstance() -> getTree() -> getCitizensThreshold()) {
        children[0] -> question();
    } else{
        //Second branch: Services
        if (IA::getInstance() -> getHappiness() < IA::getInstance() -> getTree() -> getHappinessThreshold()) {
            children[1] -> question();
        } else {
            //Third branch: Resources
            if (IA::getInstance() -> getTree() -> needResourcesInvestment()) {
                children[2] -> question();
            } else {
                //Fourth branch: Army
                if (IA::getInstance() -> getTree() -> needArmyInvestment()) {
                    children[3] -> question();
                } else {
                    //std::cout << "No hago nada" << std::endl;
                    // Ultima oportunidad
                    children[0] -> question();
                }
            }
        }
    }
}

/**
 * Determines wheter or not you are ready to attack
 */
bool HappyTree::readyToAttack() {
    //ToDo: Determinar cuando se esta listo
    return false;
}