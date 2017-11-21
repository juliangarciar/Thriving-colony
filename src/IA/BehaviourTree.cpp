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
    //First subbranch: Quarry
    if (shortOnCrystal && ia->getCityLevel() >= quarryMilestone) {
        //To do: Construir Cantera
    } else {
        //Second subbranch: Siderurgy
        if (shortOnMetal) {            
        //To do: Construir siderurgia
        }
        
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
    if (needBarracks){
        //To do: construir barraca
    } else {
        //Second subsubbranch: Barn
        if (needBarn) {
            //To do: construir establo
        } else {
            //Third subsubbranch: Workshop
            if (needWorkshop) {
                //To do: construir taller
            } else {
                //Fourth subsubranch: Wall
                if (needWall) {
                    //To do: construir muralla
                } else {
                    //Fifth subsubbranch: Tower
                    if (needTower) {
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
  * Dictates wether or not one must invest in resource production
  */
bool BehaviourTree::needResourcesInvestment() {
    shortOnMetal = calculateMetalProductionRate() < metalThreshold;
    shortOnCrystal = calculateCrystalProductionRate() < crystalThreshold;
    return (shortOnMetal || shortOnCrystal);
}

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
 * Dictates wether or not one must invest in military
 */
bool BehaviourTree::needArmyInvestment() {
    needSoldiers = calculateArmyCitizensRate() < armyThreshold;

    /**
     * A recruitment building is considered needed when:
     * A player doesn't have it yet
     * A player requires it to create a unit OR a player's city level is high enough for it to be considered a need
     */
    needBarracks = !(ia->getBarrackBuilt()) && requireBarracks;
    needBarn = !(ia->getBarnBuilt()) && (requireBarn || ia->getCityLevel() >= barnMilestone);
    needWorkshop = !(ia->getWorkshopBuilt()) && (requireWorkshop || ia->getCityLevel() >= workshopMilestone);
    
    needWall = evaluateWallNeed();
    needTower = ia->getWallBuilt() && ia->getCityLevel() >= towerMilestone;

    return (needSoldiers || needBarracks || needBarn || needWorkshop || needWall || needTower);
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

bool BehaviourTree::evaluateWallNeed() {
    //ToDo: Analizar cuando la expansion de terreno edificable llega a donde hay que construir la muralla

    return ia->getCityLevel() >= wallMilestone && ia->getWallBuilt() != true;
}

bool BehaviourTree::readyToAttack() {
    return false;
}

void BehaviourTree::developCity() {}