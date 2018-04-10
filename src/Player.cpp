#include "Player.h"

//ToDo: seria ideal que todo fuera parametrizable y todo estuviera en el mismo sitio

Player::Player() {
    
}

Player::~Player() {
    delete units;
    delete buildings;
}

void Player::Init() {
    testTimer = new Timer(1.00);
    happiness = 0;
    cityLevel = 10;
    armyLevel = 0;
    citizens = 20;

    metalAmount = 1200;
    crystalAmount = 0;

    underAttack = false;

    updateTimer = 1.00;
    updateFastTimer = 1.00;
    updateSlowTimer = 3.00;
}

/**
 * CONTROL METHODS
 */
void Player::gainResources() {
    metalAmount += getMetalProduction();
    crystalAmount += getCrystalProduction();
}

void Player::spendResources(i32 metalCost, i32 crystalCost) {
    // ToDo: Nunca acabaran siendo menor que 0
    metalAmount -= metalCost;
    crystalAmount -= crystalAmount;
}

void Player::increaseHappiness(i32 h) {
    // ToDo: clamp mejor?
    happiness += h;
    if (happiness <= -100) {
        happiness = -100;
    }
    if (happiness >= 100) {
        happiness = 100;
    }
}

void Player::increaseCityLevel(i32 lvl) {
    cityLevel += lvl;
}

void Player::increaseCitizens(i32 c) {
    citizens += c;
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
    // ToDo: no deberia ir en el battle manager? no se, es probable
    return false;
}

void Player::increaseArmyLevel(i32 alincrement) {
    armyLevel = armyLevel + alincrement;
}

void Player::decreaseArmyLevel(i32 aldecrement) {
    armyLevel = armyLevel - aldecrement;
}

void Player::setHallPosition(Vector2<f32> p){
    hallPosition = p;
}

void Player::setMetalAmount(i32 metal){
    metalAmount = metal;
}

void Player::setCrystalAmount(i32 crystal){
    crystalAmount = crystal;
}

void Player::setSiderurgyProductivity(i32 prod){
    siderurgyProductivity = prod;
}

void Player::setQuarryProductivity(i32 prod){
    quarryProductivity = prod;
}

void Player::setBuildingRadious(f32 radious){
    buildingRadious = radious;
}
//==========
// Getters
//==========
i32 Player::getHappiness() {
    return happiness;
}

i32 Player::getCityLevel() {
    return cityLevel;
}

i32 Player::getCitizens() {
    return citizens;
}

i32 Player::getArmySize() {
    return units -> getTotalTroopAmount();
}

i32 Player::getMetalAmount() {
    return metalAmount;
}

i32 Player::getCrystalAmount() {
    return crystalAmount;
}

i32 Player::getMetalProduction() {
    return buildings->getAmount(Enumeration::BuildingType::Siderurgy) * siderurgyProductivity;
}

i32 Player::getCrystalProduction() {
    return buildings->getAmount(Enumeration::BuildingType::Quarry) * quarryProductivity;
}

i32 Player::getArmyLevel() {
    return armyLevel;
}

f32 Player::getBuildingRadious(){
    return buildingRadious;
}

BuildingManager* Player::getBuildingManager() {
    return buildings;
}

UnitManager* Player::getUnitManager() {
    return units;
}

Vector2<f32> Player::getHallPosition() {
    return hallPosition;
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

void Player::decreaseHappiness(i32 h) {
    happiness = happiness - h;
}