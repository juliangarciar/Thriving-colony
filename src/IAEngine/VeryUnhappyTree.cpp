#include "VeryUnhappyTree.h"
#include "ServiceNode.h"
#include "ResourceNode.h"
#include "HomeNode.h"
#include "ArmyNode.h"
#include "RetractTroopsNode.h"
#include <IA.h>

VeryUnhappyTree::VeryUnhappyTree(Node *fatherPnt) : BehaviourTree() { 
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
    children = new Node*[5];
    children[0] = new RetractTroopsNode(this);
    children[1] = new ArmyNode(this);
    children[2] = new HomeNode(this);
    children[3] = new ResourceNode(this);
    children[4] = new ServiceNode(this);
}

VeryUnhappyTree::~VeryUnhappyTree() {
    delete father;
    delete[] children;    
}
void VeryUnhappyTree::question() {
    if (IA::Instance() -> getUnitManager() -> areTroopsInMap() == true) {
        children[0] -> question();
    } else {
        //First branch: Army
        if (IA::Instance() -> getTree() -> needArmyInvestment()) {
            children[1] -> question();
        } else {
            //Second branch: Homes
            if (IA::Instance() -> getTree() -> calculateCitizensRate() < IA::Instance() -> getTree() -> getCitizensThreshold()) {
                children[2] -> question();
            } else {
                //Third branch: Resources
                if (IA::Instance() -> getTree() -> needResourcesInvestment()) {
                    children[3] -> question();
                } else {
                    //Fourth branch: Services
                    if (IA::Instance() -> getHappiness() < IA::Instance() -> getTree() -> getHappinessThreshold()) {
                        children[4] -> question();
                    } else {
                        //std::cout << "No hago nada" << std::endl;
                        // Ultima oportunidad
                        children[2] -> question();
                    }
                }
            }
        }
    }
}

/**
 * Determines wheter or not you are ready to attack
 */
bool VeryUnhappyTree::readyToAttack() {
    if (IA::Instance() -> getArmyLevel() > IA::Instance() -> getTree() -> getAttackThreshold()) {
        return true;
    } else{
        return false;
    }
}