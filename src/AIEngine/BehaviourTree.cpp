#include "BehaviourTree.h"
#include <IA.h>

BehaviourTree::BehaviourTree() {
    requireBarrack = true;
    requireBarn = true;
    requireWorkshop = true;

    requireCitizens = false;

    underAttack = false;
    requireCrystal = false;

    barracks = 0;
    barns = 0;
    workshops = 0;
}



BehaviourTree::~BehaviourTree() {

}

/**
 * Decision making methods
 */

 /**
  * Dictates wether or not one must invest in resource production
  */
bool BehaviourTree::needResourcesInvestment() {
    shortOnMetal = calculateMetalProductionRate() < metalThreshold;
    shortOnCrystal = requireCrystal || ((IA::Instance() -> getCityLevel() >= quarryMilestone) && (calculateCrystalProductionRate() < crystalThreshold));
    return (shortOnMetal || shortOnCrystal);
}

/**
* Calculates the ratio between metal production and city level
*/
f32 BehaviourTree::calculateMetalProductionRate() {
    f32 cityLvl = IA::Instance() -> getCityLevel();
    f32 metalPr = IA::Instance() -> getMetalProduction();
    return (metalPr / cityLvl);
}

/**
* Calculates the ratio between crystal production and city level
*/
f32 BehaviourTree::calculateCrystalProductionRate() {
    f32 cityLvl = IA::Instance() -> getCityLevel();
    f32 crystalPr = IA::Instance() -> getCrystalProduction();
    return (crystalPr / cityLvl);
}

/**
* Calculates the ratio between citizens and city level
*/
f32 BehaviourTree::calculateCitizensRate() {
    f32 cityLvl = IA::Instance() -> getCityLevel();
    f32 citizens = IA::Instance() -> getMaxPeople();
    return (citizens / cityLvl);
}

/**
* Calculates the ratio between citizens and army
*/
f32 BehaviourTree::calculateArmyCitizensRate() {
    f32 armySize = IA::Instance() -> getUnitManager() -> getTotalTroopAmount();
    // Numbers of soldiers / Number of total cicitzens (citizens + soldiers)
    f32 totalCitizens = IA::Instance() -> getCitizens() + armySize;
    return (armySize / totalCitizens);
}

/**
 * Dictates wether or not one must invest in military
 */
bool BehaviourTree::needArmyInvestment() {
    needSoldiers = calculateArmyCitizensRate() < armyThreshold;
    std::cout << needSoldiers << std::endl;
    /**
     * A recruitment building is considered needed when:
     * A player doesn't have it yet
     * A player requires it to create a unit OR a player's city level is high enough for it to be considered a need
     */
    needBarracks = !(IA::Instance() -> getBuildingManager() -> getAmount("Barrack")) && requireBarrack;
    needBarn = !(IA::Instance() -> getBuildingManager() -> getAmount("Barn")) && (requireBarn || IA::Instance() -> getCityLevel() >= barnMilestone);
    needWorkshop = !(IA::Instance() -> getBuildingManager() -> getAmount("Workshop")) && (requireWorkshop || IA::Instance() -> getCityLevel() >= workshopMilestone);
    
    needWall = evaluateWallNeed();
    needTower = IA::Instance() -> getBuildingManager() -> getAmount("Wall") && IA::Instance() -> getCityLevel() >= towerMilestone;

    return (needSoldiers || needBarracks || needBarn || needWorkshop || needWall || needTower);
}

/**
* Calculates the ratio between army and melee soldiers
*/
f32 BehaviourTree::calculateMeleeRate() {
    f32 meleeAmt = IA::Instance() -> getUnitManager() -> getTroopAmount("StandardM") + IA::Instance() -> getUnitManager() -> getTroopAmount("AdvancedM");

    f32 armySize = IA::Instance() -> getArmySize();

    if (armySize == 0) {
        return 0;
    }
    return (meleeAmt / armySize);
}

/**
* Calculates the ratio between army and range soldiers
*/
f32 BehaviourTree::calculateRangeRate() {
    f32 rangeAmt = IA::Instance() -> getUnitManager() -> getTroopAmount("StandardR") + IA::Instance() -> getUnitManager() -> getTroopAmount("AdvancedR");
    f32 armySize = IA::Instance() -> getArmySize();
    if (armySize == 0) {
        return 0;
    }
    return (rangeAmt / armySize);
}

/**
* Calculates the ratio between army and siege soldiers
*/
f32 BehaviourTree::calculateSiegeRate() {
    f32 siegeAmt = IA::Instance() -> getUnitManager() -> getTroopAmount("Desintegrator") + IA::Instance() -> getUnitManager() -> getTroopAmount("Launcher");
    f32 armySize = IA::Instance() -> getArmySize();
    if (armySize == 0) {
        return 0;
    }
    return (siegeAmt / armySize);
}

bool BehaviourTree::evaluateWallNeed() {
    //ToDo: Analizar cuando la expansion de terreno edificable llega a donde hay que construir la muralla

    return IA::Instance() -> getCityLevel() >= wallMilestone && IA::Instance() -> getBuildingManager() -> getAmount("Wall") == 0;
}

bool BehaviourTree::readyToAttack() {
    return (IA::Instance() -> getArmyLevel() >= attackThreshold);
}

/**
 * GETTERS
 */
i32 BehaviourTree::getHospitalMilestone() {
    return hospitalMilestone;
}

i32 BehaviourTree::getMarketMilestone() {
    return marketMilestone;
}

i32 BehaviourTree::getQuarryMilestone() {
    return quarryMilestone;
}

i32 BehaviourTree::getMountedCreatureMilestone() {
    return mountedCreatureMilestone;
}

i32 BehaviourTree::getCreatureMilestone() {
    return creatureMilestone;
}

i32 BehaviourTree::getHappinessThreshold() {
    return happinessThreshold;
}

i32 BehaviourTree::getAttackThreshold() {
    return attackThreshold;
}

f32 BehaviourTree::getMeleeThreshold() {
    return meleeThreshold;
}

f32 BehaviourTree::getRangeThreshold() {
    return rangeThreshold;
}

f32 BehaviourTree::getCitizensThreshold() {
    return citizensThreshold;
}


bool BehaviourTree::getNeedSoldiers() {
    needSoldiers = calculateArmyCitizensRate() < armyThreshold;
    return needSoldiers;
}

bool BehaviourTree::getNeedBuildings() {
    return (needBarracks || needBarn || needWorkshop || needWall || needTower);
}

bool BehaviourTree::getNeedBarracks() {
    return needBarracks;
}

bool BehaviourTree::getNeedBarn() {
    return needBarn;
}

bool BehaviourTree::getNeedWorkshop() {
    return needWorkshop;
}

bool BehaviourTree::getNeedWall() {
    return needWall;
}

bool BehaviourTree::getNeedTower() {
    return needTower;
}

bool BehaviourTree::getUnderAttack() {
    return underAttack;
}

bool BehaviourTree::getShortOnCrystal() {
    shortOnCrystal = requireCrystal || ((IA::Instance() -> getCityLevel() >= quarryMilestone) && (calculateCrystalProductionRate() < crystalThreshold));
    return shortOnCrystal;
}

bool BehaviourTree::getShortOnMetal() {
    shortOnMetal = calculateMetalProductionRate() < metalThreshold;
    return shortOnMetal;
}

//Goal oriented
bool BehaviourTree::getRequireBarrack() {
    return requireBarrack;
}

bool BehaviourTree::getRequireBarn() {
    return requireBarn;
}

bool BehaviourTree::getRequireWorkshop() {
    return requireWorkshop;
}

void BehaviourTree::setRequireBarrack(bool requirementStatus) {
    requireBarrack = requirementStatus;
}

void BehaviourTree::setRequireBarn(bool requirementStatus) {
    requireBarn = requirementStatus;
}

void BehaviourTree::setRequireWorkshop(bool requirementStatus) {
    requireWorkshop = requirementStatus;
}

void BehaviourTree::setRequireCrystal(bool requirementStatus) {
    requireCrystal = requirementStatus;
}

bool BehaviourTree::getRequireCrystal() {
    return requireCrystal;
}

void BehaviourTree::setRequireCitizens(bool requirementStatus) {
    requireCitizens = requirementStatus;
}

bool BehaviourTree::getRequireCitizens() {
    return requireCitizens;
}

i32 BehaviourTree::getBarracks() {
    return barracks;
}

i32 BehaviourTree::getBarns() {
    return barns;
}

i32 BehaviourTree::getWorkshops() {
    return workshops;
}

void BehaviourTree::addBarrack() {
    barracks ++;
}

void BehaviourTree::addBarn() {
    barns++;
}

void BehaviourTree::addWorkshop() {
    workshops++;
}

// Down here so it doesnt clutter the top
void BehaviourTree::init(i32 behaviour) {
    // Set the variables' values according to the behaviour choosen by the AI
    switch (behaviour) {
        case Enumeration::IABehaviour::VeryHappy:
            // Happiness thresholds
            happinessThreshold = 50;
            attackThreshold = 10;
            // Service milestones
            marketMilestone = 150;
            hospitalMilestone = 450;
            // Resource milestones
            quarryMilestone = 120;
            // Unit milestones
            mountedCreatureMilestone = 80;
            creatureMilestone = 100;
            // Military buildings milestones
            wallMilestone = 150;
            towerMilestone = 200;
            barnMilestone = 200;
            workshopMilestone = 300;
            // Resource generation thresholds
            metalThreshold = 0.2;
            crystalThreshold = 0.2;
            citizensThreshold = 0.3;
            // Army thresholds
            armyThreshold = 0.3;
            meleeThreshold = 0.5;
            rangeThreshold = 0.45;
            siegeThreshold = 0.05;
        break;
        case Enumeration::IABehaviour::Happy: 
            // Happiness thresholds
            happinessThreshold = 25;
            attackThreshold = 10;
            // Service milestones
            marketMilestone = 150;
            hospitalMilestone = 450;
            // Resource milestones
            quarryMilestone = 300;
            // Unit milestones
            mountedCreatureMilestone = 80;
            creatureMilestone = 100;
            // Military buildings milestones
            wallMilestone = 70;
            towerMilestone = 90;
            barnMilestone = 60;
            workshopMilestone = 65;
            // Resource generation thresholds
            metalThreshold = 0.2;
            crystalThreshold = 0.2;
            citizensThreshold = 0.3;
            // Army thresholds
            armyThreshold = 0.2;
            meleeThreshold = 0.5;
            rangeThreshold = 0.45;
            siegeThreshold = 0.05;
        break;
        case Enumeration::IABehaviour::Neutral:
            // Happiness thresholds
            happinessThreshold = 0;
            attackThreshold = 100;
            // Service milestones
            marketMilestone = 150;
            hospitalMilestone = 450;
            // Resource milestones
            quarryMilestone = 300;
            // Unit milestones
            mountedCreatureMilestone = 80;
            creatureMilestone = 100;
            // Military buildings milestones
            wallMilestone = 70;
            towerMilestone = 90;
            barnMilestone = 60;
            workshopMilestone = 65;
            // Resource generation thresholds
            metalThreshold = 0.25;
            crystalThreshold = 0.2;
            citizensThreshold = 0.3;
            // Army thresholds
            armyThreshold = 0.25;
            meleeThreshold = 0.5;
            rangeThreshold = 0.45;
            siegeThreshold = 0.05;
        break;
        case Enumeration::IABehaviour::Unhappy: 
            // Happiness thresholds
            happinessThreshold = -25;
            attackThreshold = 100;
            // Service milestones
            marketMilestone = 150;
            hospitalMilestone = 450;
            // Resource milestones
            quarryMilestone = 300;
            // Unit milestones
            mountedCreatureMilestone = 90;
            creatureMilestone = 130;
            // Military buildings milestones
            wallMilestone = 70;
            towerMilestone = 90;
            barnMilestone = 60;
            workshopMilestone = 65;
            // Resource generation thresholds
            metalThreshold = 0.2;
            crystalThreshold = 0.2;
            citizensThreshold = 0.3;
            // Army thresholds
            armyThreshold = 0.3;
            meleeThreshold = 0.5;
            rangeThreshold = 0.45;
            siegeThreshold = 0.05;
        break;
        case Enumeration::IABehaviour::VeryUnhappy: 
            // Happiness thresholds
            happinessThreshold = -50;
            attackThreshold = 100;
            // Service milestones
            marketMilestone = 150;
            hospitalMilestone = 450;
            // Resource milestones
            quarryMilestone = 350;
            // Unit milestones
            mountedCreatureMilestone = 100;
            creatureMilestone = 150;
            // Military buildings milestones
            wallMilestone = 70;
            towerMilestone = 90;
            barnMilestone = 80;
            workshopMilestone = 110;
            // Resource generation thresholds
            metalThreshold = 0.2;
            crystalThreshold = 0.2;
            citizensThreshold = 0.3;
            // Army thresholds
            armyThreshold = 0.4;
            meleeThreshold = 0.6;
            rangeThreshold = 0.4;
            siegeThreshold = 0.05;
        break;
    }
}