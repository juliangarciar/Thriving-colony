#include "Player.h"
#include "Game.h"
#include <GraphicEngine/Window.h>

//ToDo: seria ideal que todo fuera parametrizable y todo estuviera en el mismo sitio

Player::Player() {
    happiness = 0;
    cityLevel = 10;
    citizens = 20;

    metalAmount = 1200;
    crystalAmount = 0;

    underAttack = false;
}

Player::~Player() {
    delete units;
    delete buildings;
}

/**
 * CONTROL METHODS
 */
void Player::gainResources() {
    metalAmount += getMetalProduction();
    crystalAmount += getCrystalProduction();
}

void Player::spendResources(int metalCost, int crystalCost) {
    // ToDo: Nunca acabaran siendo menor que 0
    metalAmount -= metalCost;
    crystalAmount -= crystalAmount;
}

void Player::increaseHappiness(int h) {
    // ToDo: clamp mejor?
    happiness += h;
    if (happiness <= -100) {
        happiness = -100;
    }
    if (happiness >= 100) {
        happiness = 100;
    }
}

void Player::increaseCityLevel(int lvl) {
    cityLevel += lvl;
}

void Player::increaseCitizens() {
    citizens += 5;
}

void Player::increaseArmySize() {
    citizens -= 10;
    happiness -= 5;
}

void Player::increaseBuildableRange() {
    // ToDo: equilibrar la cantidad de aumento
    buildableRange *= 1.5;
}

bool Player::losingBattle() {
    // ToDo: Es necesario? por ahora si
    // ToDo: calcular si estas perdiendo tu la  batalla
    return false;
}

//==========
// Getters
//==========
int Player::getHappiness() {
    return happiness;
}

int Player::getCityLevel() {
    return cityLevel;
}

int Player::getCitizens() {
    return citizens;
}

int Player::getArmySize() {
    return units -> getTotalTroops();
}

int Player::getMetalAmount() {
    return metalAmount;
}

int Player::getCrystalAmount() {
    return crystalAmount;
}

int Player::getMetalProduction() {
    return buildings->getAmount(Enumeration::BuildingType::Siderurgy) * RESOURCEPRODUCTION;
}

int Player::getCrystalProduction() {
    return buildings->getAmount(Enumeration::BuildingType::Quarry) * RESOURCEPRODUCTION;
}

BuildingManager* Player::getBuildingManager() {
    return buildings;
}
UnitManager* Player::getUnitManager() {
    return units;
}

// Tricks
void Player::receiveMetal() {
    metalAmount = metalAmount + 200;
}

void Player::receiveCrystal() {
    crystalAmount = crystalAmount + 200;
}

void Player::receiveCitizens() {
    citizens = citizens + 100;
}

/*



        int getMeleeAmount();
        int getRangeAmount();
        int getSiegeAmount();
        int getRamAmount();
        int getCatapultAmount();

        bool getWallBuilt();
        bool getBarrackBuilt();
        bool getBarnBuilt();
        bool getWorkshopBuilt();

        int getSiderurgyAmount();
        int getQuarryAmount();

        int getWallAmount();
        int getTowerAmount();

        bool getUnderAttack();

        void setBarnBuilt(bool);
        void setBarrackBuilt(bool);
        void setWorkshopBuilt(bool);

        //ToDo: Mejor un array con los indices del Enum
        void increaseSiderurgyAmount();
        void increaseQuarryAmount();

        //ToDo: Mejor un array con los indices del Enum
        void increaseMeleeAmount();
        void increaseRangeAmount();
        void increaseSiegeAmount();
        
        void increaseWallAmount();
        void increaseTowerAmount();

        void deployTroops();
        void retractTroops();
        void closeDoors();
        void openDoors();

        void increaseRamAmount();
        void increaseCatapultAmount();

    meleeAmount = 0;
    rangeAmount = 0;
    siegeAmount = 0;
    catapultAmount = 0;
    ramAmount = 0;

    wallBuilt = false;
    barrackBuilt = false;
    barnBuilt = false;
    workshopBuilt = false;
    
    siderurgyAmount = 0;
    quarryAmount= 0;

int Player::getMeleeAmount() {
    return meleeAmount;
}

bool Player::getWallBuilt() {
    return wallBuilt;
}

bool Player::getBarrackBuilt() {
    return barrackBuilt;
}

bool Player::getBarnBuilt() {
    return barnBuilt;
}

bool Player::getWorkshopBuilt() {
    return workshopBuilt;
}

int Player::getRangeAmount() {
    return rangeAmount;
}

int Player::getSiegeAmount() {
    return siegeAmount;
}

int Player::getRamAmount() {
    return ramAmount;
}

int Player::getCatapultAmount() {
    return catapultAmount;
}

int Player::getSiderurgyAmount() {
    return siderurgyAmount;
}

int Player::getQuarryAmount() {
    return quarryAmount;
}

int Player::getWallAmount() {
    return wallAmount;
}

int Player::getTowerAmount() {
    return towerAmount;
}

void Player::setBarnBuilt(bool _barn) {
    barnBuilt = _barn;
}

void Player::setBarrackBuilt(bool _barrack) {
    barrackBuilt = _barrack;
}

void Player::setWorkshopBuilt(bool _workshop) {
    workshopBuilt = _workshop;
}

void Player::increaseSiderurgyAmount() {
    siderurgyAmount ++;
}

void Player::increaseQuarryAmount() {
    quarryAmount ++;
}

void Player::increaseMeleeAmount() {
    meleeAmount ++;
    increaseArmySize();
}

void Player::increaseRangeAmount() {
    rangeAmount ++;
    increaseArmySize();
}

void Player::increaseSiegeAmount() {
    siegeAmount ++;
    increaseArmySize();
}

void Player::increaseCatapultAmount() {
    catapultAmount ++;
    increaseArmySize();
}

void Player::increaseRamAmount() {
    ramAmount ++;
    increaseArmySize();
}

void Player::increaseWallAmount() {
    wallAmount ++;
}

void Player::increaseTowerAmount() {
    towerAmount ++;
}

*/