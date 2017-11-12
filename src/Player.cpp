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