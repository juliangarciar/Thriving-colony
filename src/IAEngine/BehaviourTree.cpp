#include "BehaviourTree.h"
#include "../IA.h"

BehaviourTree::BehaviourTree() {
    requireBarrack = false;
    requireBarn = false;
    requireWorkshop = false;

    requireCitizens = false;

    underAttack = false;
    requireCrystal = false;
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
    shortOnCrystal = requireCrystal || ((IA::getInstance() -> getCityLevel() >= quarryMilestone) && (calculateCrystalProductionRate() < crystalThreshold));
    return (shortOnMetal || shortOnCrystal);
}

/**
* Calculates the ratio between metal production and city level
*/
float BehaviourTree::calculateMetalProductionRate() {
    float cityLvl = IA::getInstance()->getCityLevel();
    float metalPr = IA::getInstance()->getMetalProduction();
    return (metalPr / cityLvl);
}

/**
* Calculates the ratio between crystal production and city level
*/
float BehaviourTree::calculateCrystalProductionRate() {
    float cityLvl = IA::getInstance()->getCityLevel();
    float crystalPr = IA::getInstance()->getCrystalProduction();
    return (crystalPr / cityLvl);
}

/**
* Calculates the ratio between citizens and city level
*/
float BehaviourTree::calculateCitizensRate() {
    float cityLvl = IA::getInstance() -> getCityLevel();
    float citizens = IA::getInstance() -> getCitizens();
    return (citizens / cityLvl);
}

/**
* Calculates the ratio between citizens and army
*/
float BehaviourTree::calculateArmyCitizensRate() {
    float armySize = IA::getInstance() -> getUnitManager() -> getTotalTroops();
    // Numbers of soldiers / Number of total cicitzens (citizens + soldiers)
    float totalCitizens = IA::getInstance() -> getCitizens() + armySize;
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
    needBarracks = !(IA::getInstance()->getBarrackBuilt()) && requireBarrack;
    needBarn = !(IA::getInstance()->getBarnBuilt()) && (requireBarn || IA::getInstance()->getCityLevel() >= barnMilestone);
    needWorkshop = !(IA::getInstance()->getWorkshopBuilt()) && (requireWorkshop || IA::getInstance()->getCityLevel() >= workshopMilestone);
    
    needWall = evaluateWallNeed();
    needTower = IA::getInstance()->getWallBuilt() && IA::getInstance()->getCityLevel() >= towerMilestone;

    return (needSoldiers || needBarracks || needBarn || needWorkshop || needWall || needTower);
}

/**
* Calculates the ratio between army and melee soldiers
*/
float BehaviourTree::calculateMeleeRate() {
    float meleeAmt = IA::getInstance()->getMeleeAmount();

    float armySize = IA::getInstance()->getArmySize();

    if (armySize == 0) {
        return 0;
    }
    return (meleeAmt / armySize);
}

/**
* Calculates the ratio between army and range soldiers
*/
float BehaviourTree::calculateRangeRate() {
    float rangeAmt = IA::getInstance()->getRangeAmount();
    float armySize = IA::getInstance()->getArmySize();
    if (armySize == 0) {
        return 0;
    }
    return (rangeAmt / armySize);
}

/**
* Calculates the ratio between army and siege soldiers
*/
float BehaviourTree::calculateSiegeRate() {
    float siegeAmt = IA::getInstance()->getSiegeAmount();
    float armySize = IA::getInstance()->getArmySize();
    if (armySize == 0) {
        return 0;
    }
    return (siegeAmt / armySize);
}

bool BehaviourTree::evaluateWallNeed() {
    //ToDo: Analizar cuando la expansion de terreno edificable llega a donde hay que construir la muralla

    return IA::getInstance()->getCityLevel() >= wallMilestone && IA::getInstance()->getWallBuilt() != true;
}

bool BehaviourTree::readyToAttack() {
    return false;
}

/**
 * GETTERS
 */
int BehaviourTree::getHospitalMilestone() {
    return hospitalMilestone;
}

int BehaviourTree::getMarketMilestone() {
    return marketMilestone;
}

int BehaviourTree::getQuarryMilestone() {
    return quarryMilestone;
}

int BehaviourTree::getMountedCreatureMilestone() {
    return mountedCreatureMilestone;
}

int BehaviourTree::getCreatureMilestone() {
    return creatureMilestone;
}

int BehaviourTree::getHappinessThreshold() {
    return happinessThreshold;
}

float BehaviourTree::getMeleeThreshold() {
    return meleeThreshold;
}

float BehaviourTree::getRangeThreshold() {
    return rangeThreshold;
}

float BehaviourTree::getCitizensThreshold() {
    return citizensThreshold;
}


bool BehaviourTree::getNeedSoldiers() {
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
    return shortOnCrystal;
}

bool BehaviourTree::getShortOnMetal() {
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
/**
 * DEBUG
 */
void BehaviourTree::debugMessage() {
    std::cout << std::endl;
    std::cout << "////////////////////////////////////////////////////////" << std::endl;
    std::cout << "La FELICIDAD de mi ciudad es de " << IA::getInstance()->getHappiness() << std::endl;
    std::cout << "El NIVEL de mi ciudad es de " << IA::getInstance()->getCityLevel() << std::endl;
    std::cout << "La cantidad de CIUDADANOS de mi ciudad es de " << IA::getInstance()->getCitizens() << std::endl;

    std::cout << "La generacion de RECURSOS de mi ciudad es: " << std::endl;
    std::cout << IA::getInstance() -> getSiderurgyAmount() << " siderurgias que generan " << IA::getInstance() -> getMetalProduction() << "metal."<< std::endl;
    std::cout << IA::getInstance() -> getQuarryAmount() << " canteras que generan " << IA::getInstance() -> getCrystalProduction() << "cristal." << std::endl;

    std::cout << "Mi EJERCITO es de " << IA::getInstance()->getArmySize() << " unidades, de las cuales tengo: " << std::endl;
    std::cout << IA::getInstance() -> getMeleeAmount() << " melees" << std::endl;
    std::cout << IA::getInstance() -> getRangeAmount() << " rangos" << std::endl;
    std::cout << IA::getInstance() -> getSiegeAmount() << " asedios" << std::endl;
    std::cout << "Tengo tambien: " << std::endl;
    std::cout << IA::getInstance() -> getMeleeAmount() << " murallas" << std::endl;
    std::cout << IA::getInstance() -> getRangeAmount() << " torres" << std::endl;
    std::cout << "////////////////////////////////////////////////////////" << std::endl;
}

// Down here so it doesnt clutter the top
void BehaviourTree::init(int behaviour) {
    // Set the variables' values according to the behaviour choosen by the AI
    switch (behaviour) {
        case Enumeration::IABehaviour::VeryHappy:
            // Happiness thresholds
            happinessThreshold = 50;
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
        case Enumeration::IABehaviour::Happy: 
            // Happiness thresholds
            happinessThreshold = 25;
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