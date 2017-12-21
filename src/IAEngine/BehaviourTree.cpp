#include "BehaviourTree.h"
#include "../IA.h"

BehaviourTree::BehaviourTree() {
    happinessThreshold = 50;

    marketMilestone = 150;
    hospitalMilestone = 450;

    quarryMilestone = 300;
    mountedCreatureMilestone = 80;
    wallMilestone = 70;
    towerMilestone = 90;
    barnMilestone = 60;
    workshopMilestone = 65;
    creatureMilestone = 100;

    metalThreshold = 0.2;
    crystalThreshold = 0.2;
    citizensThreshold = 0.3;
    armyThreshold = 0.2;
    meleeThreshold = 0.5;
    rangeThreshold = 0.45;
    siegeThreshold = 0.05;

    underAttack = false;
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
    ///TODO: Se queda en el cristal siempre
    shortOnMetal = calculateMetalProductionRate() < metalThreshold;
    shortOnCrystal = (IA::getInstance() -> getCityLevel() >= quarryMilestone) && (calculateCrystalProductionRate() < crystalThreshold);
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
    float armySize = IA::getInstance() -> getUnitManager() -> getTotalTroops() -> size();
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
    needBarracks = !(IA::getInstance()->getBarrackBuilt()) && requireBarracks;
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