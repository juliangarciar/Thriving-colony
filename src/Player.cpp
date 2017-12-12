#include "Player.h"
#include "Game.h"
#include "Tower.h"

bool Player::deployedTroops = false;

#define RESOURCEPRODUCTION 10

Player::Player() {
    happiness = 0;
    cityLevel = 10;
    
    siderurgyAmount = 1;
    quarryAmount= 0;

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

    //ToDo: Dejar asi o solo un ejercito???
    //      Depende de como vaya a quedarse la IA de combate
    //melees = 0;
    //rangeds = 0;
    troops = 0;
    buildings = 0;

    Game::Instance() -> getEvents() -> addEvent(Enumeration::EventType::DeployTroops, deployTroops);
    Game::Instance() -> getEvents() -> addEvent(Enumeration::EventType::RetractTroops, retractTroops);
}

Player::~Player() {
    //delete melees;
    //delete rangeds;
    delete troops;
    delete buildings;
}

void Player::update() {
    //if (timer) {
        //gainResource();
    //}
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
    return troops->size();
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

bool Player::getClosedDoors() {
    return closedDoors;
}

// Return wether or not our troops are deployed
bool Player::getDeployedTroops() {
    return deployedTroops;
}

/**
 * CONTROL METHODS
 */

void Player::increaseHappiness(int h) {
    happiness += h;
}

void Player::increaseCityLevel(int lvl) {
    cityLevel += lvl;
}

void Player::increaseSiderurgyAmount() {
    increaseCityLevel(5);
    siderurgyAmount ++;
}

void Player::increaseQuarryAmount() {
    increaseCityLevel(5);
    quarryAmount ++;
}

void Player::increaseCitizens() {
    increaseCityLevel(3);
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
/*
void Player::buildBuilding(int hitPoints, Vector3<float>* pos, Enumeration::BuildingType _type, bool _team) {
    switch (_type) {
        case Enumeration::BuildingType::Barn:
            barnBuilt = true; 
        break;
        
        case Enumeration::BuildingType::Barrack:
            barrackBuilt= true;
        break;

        case Enumeration::BuildingType::Workshop:
            workshopBuilt = true;
        break;
    }
    buildings -> push_back(new Building(hitPoints, pos, _type, _team));
}

void Player::buildTower(int hitPoints, int attackSpeedPnt, int damagePnt, Vector3<float>* pos, bool _team) {
    buildings -> push_back(new Tower(hitPoints, attackSpeedPnt, damagePnt, pos, _team));
}
*/
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
bool Player::losingBattle() {
    //ToDo: calcular si estas perdiendo tu la  batalla
    return false;
}

void Player::closeDoors() {
    // ToDo: hacer de verdad
    closedDoors = true;
}

void Player::openDoors() {
    // ToDo: hacer de verdad
    closedDoors = false;
}

void Player::deployTroops() {
    // ToDo: hacer de verdad
    deployedTroops = true;
}

/*
* Troops come back to their building (barn, barrack or workshop)
*/
void Player::retractTroops() {
    // ToDo: hacer de verdad
    deployedTroops = false;
}

std::vector<Unit*>* Player::getTroops() {
    //ToDo: Devolver tropas
    //TODO al cuadrado: Decidir como va a ser lo de las tropas   
    return troops;
}