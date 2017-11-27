#include "Player.h"

Player::Player() {
    happiness = 0;
    cityLevel = 10;
    
    siderurgyAmount = 1;
    metalProduction = 10;

    quarryAmount= 0;
    crystalProduction = 10;
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

    melees = 0;
    rangeds = 0;
    buildings = 0;
}

Player::~Player() {

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
    return siderurgyAmount * metalProduction;
}

int Player::getCrystalProduction() {
    return quarryAmount * crystalProduction;
}

int Player::getCitizens() {
    return citizens;
}

int Player::getArmySize() {
    return armySize;
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

void Player::buildBarrack() {
    barrackBuilt= true;
}

void Player::buildBarn() {
    barnBuilt = true;
}

void Player::buildWorkshop() {
    workshopBuilt = true;
}

int Player::getWallAmount() {
    return wallAmount;
}

int Player::getTowerAmount() {
    return towerAmount;
}

void Player::increaseWallAmount() {
    wallAmount ++;
}

void Player::increaseTowerAmount() {
    towerAmount ++;
}