#include "Player.h"
#include "Map.h"

Player::Player() {
    
}

Player::~Player() {

}

void Player::Init() {
    happiness = 0;
    citizens = 0;
    maxPeople = 0;

    metalAmount = 0;
    crystalAmount = 0;

    cityLevel = 10;
    armyLevel = 0;

    citizensByHappiness = 0;
    resistanceModifier = 0;
    damageModifier = 0;

	influenceRangeIncrements = 0;

    underAttack = false;

    resourceTimer = new Timer(1.00, true);

	resourceTimer -> setCallback([&](){
		metalAmount += getMetalProduction();
		crystalAmount += getCrystalProduction();
	});

	citizenTimer = new Timer(5.00, true);

	citizenTimer -> setCallback([&](){
   		citizens += (Map::Instance()->getCitizenIncrement() + citizensByHappiness);
		if (citizens + getArmySize() > maxPeople) {
			citizens = maxPeople - getArmySize();
		}
	});
}

void Player::Update() { //ToDo: config by JSON
	citizensByHappiness = floor(happiness / 25);
    if (citizensByHappiness < 0) {
        citizensByHappiness = 0;
    }
    resistanceModifier = floor(happiness * 10 / 100);
    if (resistanceModifier < 0) {
        resistanceModifier = 0;
    }
    damageModifier = -1 * floor(happiness * 15 / 100);
    if (damageModifier < 0) {
        damageModifier = 0;
    }
}

void Player::CleanUp(){
    delete resourceTimer;
	resourceTimer = nullptr;
    delete citizenTimer;
	citizenTimer = nullptr;
}

/**
 * CONTROL METHODS
 */
bool Player::isSolvent(i32 metalCost, i32 crystalCost, i32 citizenCost){
	return (metalCost <= metalAmount && crystalCost <= crystalAmount && citizenCost <= citizens);
}

void Player::spendResources(i32 metalCost, i32 crystalCost) {
    metalAmount -= metalCost;
    crystalAmount -= crystalAmount;
	if (metalAmount < 0) metalAmount = 0;
	if (crystalAmount < 0) crystalAmount = 0;
}

void Player::increaseBuildableRange() {
	if (influenceRangeIncrements < Map::Instance()->getInfluenceRangeIncrementLimit())
    	buildableRange += Map::Instance()->getInfluenceRangeIncrement();
	influenceRangeIncrements++;
}

/**
 * MODIFIYING METHODS
 */
void Player::modifyHappiness(i32 h) {
    happiness += h;
    if (happiness <= -100) {
        happiness = -100;
    }
    if (happiness >= 100) {
        happiness = 100;
    }
}

void Player::modifyCitizens(i32 c) {
    citizens += c;
    if (citizens < 0) {
        citizens = 0;
    }
}

void Player::modifyMaxPeople(i32 p) {
    maxPeople += p;
    if (maxPeople < 0) {
        maxPeople = 0;
    }
}

void Player::modifyCityLevel(i32 lvl) {
    cityLevel += lvl;
    if (cityLevel < 0) {
        cityLevel = 0;
    }
}

void Player::modifyArmyLevel(i32 lvl) {
    armyLevel += lvl;
    if (armyLevel < 0) {
        armyLevel = 0;
    }
}

//==========
// Getters
//==========
i32 Player::getArmySize() {
    return units -> getTotalTroopAmount();
}

i32 Player::getMetalProduction() {
    return buildings->getAmount("Siderurgy") * Map::Instance()->getMetalProductivity();
}

i32 Player::getCrystalProduction() {
    return buildings->getAmount("Quarry") * Map::Instance()->getCrystalProductivity();
}

i32 Player::getHappiness(){
	return happiness;
}

i32 Player::getCitizens() {
	return citizens;
}

i32 Player::getMaxPeople(){
	return maxPeople;
}

i32 Player::getCityLevel(){
	return cityLevel;
}

i32 Player::getArmyLevel(){
	return armyLevel;
}

i32 Player::getResistanceModifier() {
	return resistanceModifier;
}

i32 Player::getDamageModifier() {
	return damageModifier;
}

BuildingManager *Player::getBuildingManager(){
	return buildings;
}

UnitManager *Player::getUnitManager(){
	return units;
}