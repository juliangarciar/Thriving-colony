#include "NeutralTree.h"
#include "ServiceNode.h"
#include "ResourceNode.h"
#include "HomeNode.h"
#include "ArmyNode.h"
#include "../IA.h"

NeutralTree::NeutralTree(Node *fatherPnt) : BehaviourTree() {
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
    children[0] = new ResourceNode(this);
    children[1] = new HomeNode(this);
    children[2] = new ServiceNode(this);
    children[3] = new ArmyNode(this);
}

NeutralTree::~NeutralTree() {
    delete father;
    delete[] children;    
}

void NeutralTree::question() {
    //First branch: Resources
    if (IA::Instance() -> getTree() -> needResourcesInvestment()) {
        children[0] -> question();
    } else {
        //Second branch: Homes
        if (IA::Instance() -> getTree() -> calculateCitizensRate() < IA::Instance() -> getTree() -> getCitizensThreshold()) {
            children[1] -> question();
        } else {
            //Third branch: Services
            if (IA::Instance() -> getHappiness() < IA::Instance() -> getTree() -> getHappinessThreshold()) {
                children[2] -> question();
            } else {
                //Fourth branch: Army
                if (IA::Instance() -> getTree() -> needArmyInvestment()) {
                    children[3] -> question();
                } else {
                    //std::cout << "No hago nada" << std::endl;
                    // Ultima oportunidad
                    children[1] -> question();
                }
            }
        }
    }
}

/**
 * Determines wheter or not you are ready to attack
 */
bool NeutralTree::readyToAttack() {
    //ToDo: Determinar cuando se esta listo
    return false;
}