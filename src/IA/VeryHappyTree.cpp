#include "VeryHappyTree.h"
<<<<<<< HEAD
#include "ServiceNode.h"
#include "ResourceNode.h"
#include "HomeNode.h"
#include "ArmyNode.h"
#include "../IA.h"
#include <iostream>

VeryHappyTree::VeryHappyTree(Node *fatherPnt) : BehaviourTree() {
=======
#include "../IA.h"
#include <iostream>

VeryHappyTree::VeryHappyTree() : BehaviourTree() {
>>>>>>> 171f5e90efc080f46f18c0f6e47090ea89178dc8
    happinessThreshold = 80;
    quarryMilestone = 50;
    mountedCreatureMilestone = 80;
    wallMilestone = 70;
    towerMilestone = 90;
    barnMilestone = 60;
    workshopMilestone = 65;
    creatureMilestone = 100;

    metalThreshold = 0.6;
    crystalThreshold = 0.4;
    citizensThreshold = 0.3;
    armyThreshold = 0.2;
    meleeThreshold = 0.5;
    rangeThreshold = 0.45;
    siegeThreshold = 0.05;

    father = fatherPnt;
    children = new Node*[4];
    children[0] = new ServiceNode(this);
    children[1] = new ResourceNode(this);
    children[2] = new HomeNode(this);
    children[3] = new ArmyNode(this);
}

VeryHappyTree::~VeryHappyTree() {
    delete father;
    delete[] children;
}
///TODO quitar IA de los arboles

void VeryHappyTree::question() {
    //First branch: Services
    if (IA::getInstance() -> getHappiness() < tree -> getHappinessThreshold()) {
        children[0] -> question();
    } else {
        //Second branch: Resources
        if (tree -> needResourcesInvestment()) {
            children[1] -> question();
        } else {
            //Third branch: Homes
            if (tree -> calculateCitizensRate() < tree -> getCitizensThreshold()) {
                children[2] -> question();
            } else {
                //Fourth branch: Army
                if (tree -> needArmyInvestment()) {
                    children[3] -> question();
                } else {
                    //std::cout << "No hago nada" << std::endl;
                    // Ultima oportunidad
                    children[2] -> question();
                }
            }
        }
    }
}

/**
 * Determines wheter or not you are ready to attack
 */
bool VeryHappyTree::readyToAttack() {
    //ToDo: Determinar cuando se esta listo
    return false;
}