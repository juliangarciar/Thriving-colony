#include "Player.h"

Player::Player() {

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
    return metalProduction;
}

int Player::getCrystalProduction() {
    return crystalProduction;
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