#include "BehaviourTree.h"
#include "../IA.h"
#include <iostream>

BehaviourTree::BehaviourTree(/*IA* iaPnt*/) {
    //ia=iaPnt;
}

BehaviourTree::~BehaviourTree() {

}

/**
 * Behaviour methods
 */

void BehaviourTree::makeChoice() {
    debugMessage();
    //First branch: Attacking the enemy
    if (readyToAttack()) {
        std::cout << "Voy a atacar" << std::endl;
        //To Do: Attack the enemy
    } else  {
        //Second branch: Being attacked
        if (underAttack){
            std::cout << "Me atacan" << std::endl;
            //To Do:
        } else {
            //Third branch: Peaceful, develop the city
            std::cout << "Voy a desarrollar la ciudad" << std::endl;
            developCity();
        }
    }
}

void BehaviourTree::serviceBranch() {
    IA::getInstance()->increaseHappiness(5);
    std::cout << "Construyo un edificio de servicios. Tengo " << IA::getInstance()->getHappiness() << " felicidad";
    //ToDo: Elegir el servicio a construir
}

void BehaviourTree::resourcesBranch(){
    //First subbranch: Quarry
    if (shortOnCrystal && IA::getInstance()->getCityLevel() >= quarryMilestone) {

    IA::getInstance()->increaseQuarryAmount();
    std::cout << "Construyo una cantera. Ahora genero " << IA::getInstance()->getCrystalProduction() << " cristal por segundo";
        //To do: Construir Cantera
    } else {
        //Second subbranch: Siderurgy
        if (shortOnMetal) {            
            IA::getInstance()->increaseSiderurgyAmount();
            std::cout << "Construyo una siderurgia. Ahora genero " << IA::getInstance()->getMetalProduction() << " metal por segundo";
        }
        
    }
}

void BehaviourTree::unitsBranch() {
    
    //First subsubbranch: Melee
    if (calculateMeleeRate() < meleeThreshold) {
        std::cout << "Voy a hacer melees" << std::endl;

        IA::getInstance() -> increaseMeleeAmount();
        //First subsubsubbranch: Creature
        if (IA::getInstance()->getCityLevel() >= creatureMilestone) {
            //To do: generar criatura
        } else {
            //First subsubsubbranch: With creature
            if (IA::getInstance()->getCityLevel() >= mountedCreatureMilestone) {
                //To do: generar melees en criatura
            } else {
                //Second subsubsubbranch: Without creature
                //To do: generar melees
            }
        }
    } else {
        //Second subsubbranch: Range
        if (calculateRangeRate() < rangeThreshold) {
            std::cout << "Voy a hacer rangos" << std::endl;
            IA::getInstance() -> increaseRangeAmount();
            //First subsubsubbranch: With creature
            if (IA::getInstance()->getCityLevel() >= mountedCreatureMilestone) {
                //To do: generar rango en criatura
            } else {
                //Second subsubsubbranch: Without creature
                //To do: generar rango
            }
        } else {
            //Third subsubbranch: Siege
            //if (calculateSiegeRate() < siegeThreshold) {

            std::cout << "Voy a hacer asedio" << std::endl;
            IA::getInstance() -> increaseSiegeAmount();
            //First subsubsubbranch: Ram
            if (IA::getInstance()->getRamAmount() <= IA::getInstance()->getCatapultAmount()) {
                //To do: generar ariete
            } else {
                //Second subsubsubbranch: Catapult
                //To do: generar catapulta
            }
        }
    }
}


void BehaviourTree::buildingsBranch(){
    //First subsubbranch: Barrack
    if (needBarracks){
        IA::getInstance()->buildBarrack();
        std::cout << "Construyo una barraca.";
        //To do: construir barraca
    } else {
        //Second subsubbranch: Barn
        if (needBarn) {
            IA::getInstance()->buildBarn();
            std::cout << "Construyo un establo";
            //To do: construir establo
        } else {
            //Third subsubbranch: Workshop
            IA::getInstance()->buildWorkshop();
            std::cout << "Construyo un taller" << std::endl;
            if (needWorkshop) {
                //To do: construir taller
            } else {
                //Fourth subsubranch: Wall
                if (needWall) {
                    std::cout << "Construyo una muralla" << std::endl;
                    IA::getInstance() -> increaseWallAmount();
                    //To do: construir muralla
                } else {
                    //Fifth subsubbranch: Tower
                    if (needTower) {
                        std::cout << "Construyo una torre" << std::endl;
                        IA::getInstance() -> increaseTowerAmount();
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
        std::cout << "Voy a hacer unidades" << std::endl;
        unitsBranch();
    } else {
        //Second subbranch: Buildings
        std::cout << "Voy a hacer edificios" << std::endl;
        if (IA::getInstance()->getBarrackBuilt() != true || (IA::getInstance()->getCityLevel() >= barnMilestone && IA::getInstance()->getBarnBuilt() != true) || (IA::getInstance()->getCityLevel() >= workshopMilestone && IA::getInstance()->getWorkshopBuilt() != true) || (IA::getInstance()->getCityLevel() >= wallMilestone && IA::getInstance()->getWallBuilt() != true) || IA::getInstance()->getCityLevel() >= towerMilestone) {
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
    std::cout << crystalPr / cityLvl << std::endl;
    return (crystalPr / cityLvl);
}

/**
* Calculates the ratio between citizens and city level
*/
float BehaviourTree::calculateCitizensRate() {
    float cityLvl = IA::getInstance()->getCityLevel();
    float citizens = IA::getInstance()->getCitizens();
    return (citizens / cityLvl);
}

/**
* Calculates the ratio between citizens and army
*/
float BehaviourTree::calculateArmyCitizensRate() {
    float armySize = IA::getInstance()->getArmySize();
    // Numbers of soldiers / Number of total cicitzens (citizens + soldiers)
    float totalCitizens = IA::getInstance()->getCitizens() + armySize;
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

void BehaviourTree::developCity() {

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