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

void BehaviourTree::resourcesBranch(){
    //First subbranch: Siderurgy
    if (calculateMetalProductionRate() < metalThreshold) {
        //To do: Construir siderurgia
    } else {
        //Second subbranch: Quarry
        //To do: Construir cantera
    }
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

void BehaviourTree::buildingsBranch(){
    //First subsubbranch: Barrack
    if (ia->getBarrackBuilt() != true){
        //To do: construir barraca
    } else {
        //Second subsubbranch: Barn
        if (ia->getCityLevel() >= barnMilestone && ia->getBarnBuilt() != true) {
            //To do: construir establo
        } else {
            //Third subsubbranch: Workshop
            if (ia->getCityLevel() >= workshopMilestone && ia->getWorkshopBuilt() != true) {
                //To do: construir taller
            } else {
                //Fourth subsubranch: Wall
                if (ia->getCityLevel() >= wallMilestone && ia->getWallBuilt() != true) {
                    //To do: construir muralla
                } else {
                    //Fifth subsubbranch: Tower
                    if (ia->getCityLevel() >= towerMilestone) {
                        //To do: construir torre
                    }
                }
            }
        }
    }
}

void BehaviourTree::armyBranch(){
    //First subbranch: Units
    if (calculateArmyCitizensRate() < armyThreshold){
        unitsBranch();
    } else {
        //Second subbranch: Buildings
        if (ia->getBarrackBuilt() != true || (ia->getCityLevel() >= barnMilestone && ia->getBarnBuilt() != true) || (ia->getCityLevel() >= workshopMilestone && ia->getWorkshopBuilt() != true) || (ia->getCityLevel() >= wallMilestone && ia->getWallBuilt() != true) || ia->getCityLevel() >= towerMilestone) {
            buildingsBranch();
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