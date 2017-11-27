#include "VeryUnhappyTree.h"
#include "../IA.h"

VeryUnhappyTree::VeryUnhappyTree() : BehaviourTree() { 
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
}

VeryUnhappyTree::~VeryUnhappyTree() {
    
}
void VeryUnhappyTree::developCity() {
    //First branch: Army
    if (needArmyInvestment()) {
        armyBranch();
    } else {
        //Second branch: Homes
        if (calculateCitizensRate() < citizensThreshold) {
            //ToDo: Construir viviendas
        } else {
            //Third branch: Resources
            if (needResourcesInvestment()) {
                resourcesBranch();
            } else{
                //Fourth branch: Services
                if (IA::getInstance()->getHappiness() < happinessThreshold) {
                    serviceBranch();
                }
            }
        }
    }
}

/**
 * Determines wheter or not you are ready to attack
 */
bool VeryUnhappyTree::readyToAttack() {
    //ToDo: Determinar cuando se esta listo
    return false;
}