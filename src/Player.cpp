#include "Player.h"
//#include "Game.h"
#include "GraphicEngine/Window.h"
#include "Tower.h"
#include "Game.h"

#define RESOURCEPRODUCTION 10

Player::Player() {
    updateTimer = 1;

    happiness = 0;
    cityLevel = 10;
    
    siderurgyAmount = 0;
    quarryAmount= 0;

    //ToDo: creo que se dijo que el player empezaba con 500 o con 700 
    //Hay que empezar con 500 mas de metal porque si no al construir la siderurgia inicial 
    //se queda a 0 porque se le cobra
    metalAmount = 1200;
    crystalAmount = 0;

    citizens = 0;

    armySize = 0;
    meleeAmount = 0;
    rangeAmount = 0;
    siegeAmount = 0;
    catapultAmount = 0;
    ramAmount = 0;

    wallBuilt = false;
    barrackBuilt = false;
    barnBuilt = false;
    workshopBuilt = false;

    underAttack = false;
}

Player::~Player() {
    delete units;
    delete buildings;
}

void Player::update() {

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

int Player::getMetalProduction() {
    return siderurgyAmount * RESOURCEPRODUCTION;
}

int Player::getCrystalProduction() {
    return quarryAmount * RESOURCEPRODUCTION;
}

int Player::getCitizens() {
    return citizens;
}

int Player::getArmySize() {
    return units -> getTotalTroops();
}

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

BuildingManager* Player::getBuildingManager() {
    return buildings;
}
UnitManager* Player::getUnitManager(){
    return units;
}
/*
* SETTERS
*/

void Player::setBarnBuilt(bool _barn) {
    barnBuilt = _barn;
}

void Player::setBarrackBuilt(bool _barrack) {
    barrackBuilt = _barrack;
}

void Player::setWorkshopBuilt(bool _workshop) {
    workshopBuilt = _workshop;
}

/**
 * CONTROL METHODS
 */
void Player::gainResources() {
    metalAmount += getMetalProduction();
    crystalAmount += getCrystalProduction();
}

void Player::spendResources(int metalCost, int crystalCost) {
    // Nunca acabaran siendo menor que 0
    metalAmount -= metalCost;
    crystalAmount -= crystalAmount;
}

void Player::increaseHappiness(int h) {
    //clamp mejor?
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

void Player::increaseSiderurgyAmount() {
    siderurgyAmount ++;
}

void Player::increaseQuarryAmount() {
    quarryAmount ++;
}

void Player::increaseCitizens() {
    citizens += 5;
}

void Player::increaseArmySize() {
    citizens -= 10;
    happiness -= 5;
    armySize ++;
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

void Player::increaseBuildableRange() {
    //ToDo: equilibrar la cantidad de aumento
    buildableRange *= 1.5;
}

void Player::increaseWallAmount() {
    wallAmount ++;
}

void Player::increaseTowerAmount() {
    towerAmount ++;
}

//Es necesario?
//por ahora si
bool Player::losingBattle() {
    //ToDo: calcular si estas perdiendo tu la  batalla
    return false;
}

//ToDo: las tropas no deberian ir en unit manager?
/*std::vector<Unit*>* Player::getTroops() {
    //ToDo: Devolver tropas
    //TODO al cuadrado: Decidir como va a ser lo de las tropas   
    // las tropas van en el unit manager oogili boogili
    //return troops;
    return units -> getTotalTroops();
}*/

int Player::getMetalAmount() {
    return metalAmount;
}

int Player::getCrystalAmount() {
    return crystalAmount;
}

void Player::receiveMetal() {
    metalAmount = metalAmount + 200;
}

void Player::receiveCrystal() {
    crystalAmount = crystalAmount + 200;
}

void Player::receiveCitizens() {
    citizens = citizens + 100;
}