#include "BehaviourTree.h"
#include <iostream>

BehaviourTree::BehaviourTree(IA *iaPnt) {
    ia=iaPnt;
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
    ia->increaseHappiness(5);
    std::cout << "Construyo un edificio de servicios. Tengo " << ia->getHappiness() << " felicidad";
    //ToDo: Elegir el servicio a construir
}

void BehaviourTree::resourcesBranch(){
    //First subbranch: Quarry
    if (shortOnCrystal && ia->getCityLevel() >= quarryMilestone) {

    ia->increaseQuarryAmount();
    std::cout << "Construyo una cantera. Ahora genero " << ia->getCrystalProduction() << " cristal por segundo";
        //To do: Construir Cantera
    } else {
        //Second subbranch: Siderurgy
        if (shortOnMetal) {            
            ia->increaseSiderurgyAmount();
            std::cout << "Construyo una siderurgia. Ahora genero " << ia->getMetalProduction() << " metal por segundo";
        }
        
    }
}

void BehaviourTree::unitsBranch() {
    
    //First subsubbranch: Melee
    if (calculateMeleeRate() < meleeThreshold) {
        std::cout << "Voy a hacer melees" << std::endl;

        ia -> increaseMeleeAmount();
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
            std::cout << "Voy a hacer rangos" << std::endl;
            ia -> increaseRangeAmount();
            //First subsubsubbranch: With creature
            if (ia->getCityLevel() >= mountedCreatureMilestone) {
                //To do: generar rango en criatura
            } else {
                //Second subsubsubbranch: Without creature
                //To do: generar rango
            }
        } else {
            //Third subsubbranch: Siege
            //if (calculateSiegeRate() < siegeThreshold) {

            std::cout << "Voy a hacer asedio" << std::endl;
            ia -> increaseSiegeAmount();
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


void BehaviourTree::buildingsBranch(){
    //First subsubbranch: Barrack
    if (needBarracks){
        ia->buildBarrack();
        std::cout << "Construyo una barraca.";
        //To do: construir barraca
    } else {
        //Second subsubbranch: Barn
        if (needBarn) {
            ia->buildBarn();
            std::cout << "Construyo un establo";
            //To do: construir establo
        } else {
            //Third subsubbranch: Workshop
            ia->buildWorkshop();
            std::cout << "Construyo un taller" << std::endl;
            if (needWorkshop) {
                //To do: construir taller
            } else {
                //Fourth subsubranch: Wall
                if (needWall) {
                    std::cout << "Construyo una muralla" << std::endl;
                    ia -> increaseWallAmount();
                    //To do: construir muralla
                } else {
                    //Fifth subsubbranch: Tower
                    if (needTower) {
                        std::cout << "Construyo una torre" << std::endl;
                        ia -> increaseTowerAmount();
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
    ///TODO: Se queda en el cristal siempre
    shortOnMetal = calculateMetalProductionRate() < metalThreshold;
    shortOnCrystal = (ia -> getCityLevel() >= quarryMilestone) && (calculateCrystalProductionRate() < crystalThreshold);
    return (shortOnMetal || shortOnCrystal);
}

/**
* Calculates the ratio between metal production and city level
*/
float BehaviourTree::calculateMetalProductionRate() {
    float cityLvl = ia->getCityLevel();
    float metalPr = ia->getMetalProduction();
    return (metalPr / cityLvl);
}

/**
* Calculates the ratio between crystal production and city level
*/
float BehaviourTree::calculateCrystalProductionRate() {
    float cityLvl = ia->getCityLevel();
    float crystalPr = ia->getCrystalProduction();
    std::cout << crystalPr / cityLvl << std::endl;
    return (crystalPr / cityLvl);
}

/**
* Calculates the ratio between citizens and city level
*/
float BehaviourTree::calculateCitizensRate() {
    float cityLvl = ia->getCityLevel();
    float citizens = ia->getCitizens();
    return (citizens / cityLvl);
}

/**
* Calculates the ratio between citizens and army
*/
float BehaviourTree::calculateArmyCitizensRate() {
    float armySize = ia->getArmySize();
    // Numbers of soldiers / Number of total cicitzens (citizens + soldiers)
    float totalCitizens = ia->getCitizens() + armySize;
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
    float meleeAmt = ia->getMeleeAmount();

    float armySize = ia->getArmySize();

    if (armySize == 0) {
        return 0;
    }
    return (meleeAmt / armySize);
}

/**
* Calculates the ratio between army and range soldiers
*/
float BehaviourTree::calculateRangeRate() {
    float rangeAmt = ia->getRangeAmount();
    float armySize = ia->getArmySize();
    if (armySize == 0) {
        return 0;
    }
    return (rangeAmt / armySize);
}

/**
* Calculates the ratio between army and siege soldiers
*/
float BehaviourTree::calculateSiegeRate() {
    float siegeAmt = ia->getSiegeAmount();
    float armySize = ia->getArmySize();
    if (armySize == 0) {
        return 0;
    }
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
    std::cout << "La FELICIDAD de mi ciudad es de " << ia->getHappiness() << std::endl;
    std::cout << "El NIVEL de mi ciudad es de " << ia->getCityLevel() << std::endl;
    std::cout << "La cantidad de CIUDADANOS de mi ciudad es de " << ia->getCitizens() << std::endl;

    std::cout << "La generacion de RECURSOS de mi ciudad es: " << std::endl;
    std::cout << ia -> getSiderurgyAmount() << " siderurgias que generan " << ia -> getMetalProduction() << "metal."<< std::endl;
    std::cout << ia -> getQuarryAmount() << " canteras que generan " << ia -> getCrystalProduction() << "cristal." << std::endl;

    std::cout << "Mi EJERCITO es de " << ia->getArmySize() << " unidades, de las cuales tengo: " << std::endl;
    std::cout << ia -> getMeleeAmount() << " melees" << std::endl;
    std::cout << ia -> getRangeAmount() << " rangos" << std::endl;
    std::cout << ia -> getSiegeAmount() << " asedios" << std::endl;
    std::cout << "Tengo tambien: " << std::endl;
    std::cout << ia -> getMeleeAmount() << " murallas" << std::endl;
    std::cout << ia -> getRangeAmount() << " torres" << std::endl;
    std::cout << "////////////////////////////////////////////////////////" << std::endl;
}