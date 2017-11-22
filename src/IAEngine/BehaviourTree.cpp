#include "BehaviourTree.h"

BehaviourTree::BehaviourTree(IA *iaPnt) {
    ia=iaPnt;
}

BehaviourTree::~BehaviourTree() {

}

/**
 * Behaviour methods
 */

void BehaviourTree::makeChoice() {
    //First branch: Attacking the enemy
    if (readyToAttack()) {
        //To Do: Attack the enemy
    } else  {
        //Second branch: Being attacked
        if (underAttack){
            //To Do:
        } else {
            //Third branch: Peaceful, develop the city
            developCity();
        }
    }
}

void BehaviourTree::serviceBranch() {
    //ToDo: Elegir el servicio a construir
}

void BehaviourTree::unitsBranch() {
    //First subsubbranch: Melee
    if (calculateMeleeRate() < meleeThreshold) {
        //First subsubsubbranch: Creature
        if (ia->getCityLevel() >= creatureMilestone) {
            //To do: generar criatura
        } else {
            //First subsubsubbranch: With creature
            if (ia->getCityLevel() >= mountedCreatureMilestone) {
                //To do: generar melees en criatura
            } else {
                //Second subsubsubbranch: Without creature
                //To do: generar melees
            }
        }
    } else {
        //Second subsubbranch: Range
        if (calculateRangeRate() < rangeThreshold) {
            //First subsubsubbranch: With creature
            if (ia->getCityLevel() >= mountedCreatureMilestone) {
                //To do: generar rango en criatura
            } else {
                //Second subsubsubbranch: Without creature
                //To do: generar rango
            }
        } else {
            //Third subsubbranch: Siege
            if (calculateSiegeRate() < siegeThreshold) {
                //First subsubsubbranch: Ram
                if (ia->getRamAmount() <= ia->getCatapultAmount()) {
                    //To do: generar ariete
                } else {
                    //Second subsubsubbranch: Catapult
                    //To do: generar catapulta
                }
            }
        }
    }
}

/**
 * Decision making methods
 */

/**
* Calculates the ratio between metal production and city level
*/
float BehaviourTree::calculateMetalProductionRate() {
    int cityLvl = ia->getCityLevel();
    int metalPr = ia->getMetalProduction();
    return (metalPr / cityLvl);
}

/**
* Calculates the ratio between crystal production and city level
*/
float BehaviourTree::calculateCrystalProductionRate() {
    int cityLvl = ia->getCityLevel();
    int crystalPr = ia->getCrystalProduction();
    return (crystalPr / cityLvl);
}

/**
* Calculates the ratio between citizens and city level
*/
float BehaviourTree::calculateCitizensRate() {
    int cityLvl = ia->getCityLevel();
    int citizens = ia->getCitizens();
    return (citizens / cityLvl);
}

/**
* Calculates the ratio between citizens and army
*/
float BehaviourTree::calculateArmyCitizensRate() {
    int armySize = ia->getArmySize();
    // Numbers of soldiers / Number of total cicitzens (citizens + soldiers)
    int totalCitizens = ia->getCitizens() + armySize;
    return (armySize / totalCitizens);
}

/**
* Calculates the ratio between army and melee soldiers
*/
float BehaviourTree::calculateMeleeRate() {
    int meleeAmt = ia->getMeleeAmount();
    int armySize = ia->getArmySize();
    return (meleeAmt / armySize);
}

/**
* Calculates the ratio between army and range soldiers
*/
float BehaviourTree::calculateRangeRate() {
    int rangeAmt = ia->getRangeAmount();
    int armySize = ia->getArmySize();
    return (rangeAmt / armySize);
}

/**
* Calculates the ratio between army and siege soldiers
*/
float BehaviourTree::calculateSiegeRate() {
    int siegeAmt = ia->getSiegeAmount();
    int armySize = ia->getArmySize();
    return (siegeAmt / armySize);
}

bool BehaviourTree::readyToAttack() {}

void BehaviourTree::developCity() {}