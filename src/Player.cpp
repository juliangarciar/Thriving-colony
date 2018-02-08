#include "Player.h"
#include "Game.h"

//ToDo: seria ideal que todo fuera parametrizable y todo estuviera en el mismo sitio

Player::Player() {
    happiness = 0;
    cityLevel = 10;
    citizens = 20;

    metalAmount = 1200;
    crystalAmount = 0;

    underAttack = false;

    updateTimer = 1.00;
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
    return false;
}

void Player::setHallPosition(Vector3<f32> p){
    hallPosition = p;
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
    return buildings->getAmount(Enumeration::BuildingType::Siderurgy) * RESOURCEPRODUCTION;
}

i32 Player::getCrystalProduction() {
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

void Player::decreaseHappiness(i32 h) {
    happiness = happiness - h;
}

Vector3<f32> Player::getHallPosition() {
    return hallPosition;
}

/*



        i32 getMeleeAmount();
        i32 getRangeAmount();
        i32 getSiegeAmount();
        i32 getRamAmount();
        i32 getCatapultAmount();

        bool getWallBuilt();
        bool getBarrackBuilt();
        bool getBarnBuilt();
        bool getWorkshopBuilt();

        i32 getSiderurgyAmount();
        i32 getQuarryAmount();

        i32 getWallAmount();
        i32 getTowerAmount();

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

i32 Player::getMeleeAmount() {
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

i32 Player::getRangeAmount() {
    return rangeAmount;
}

i32 Player::getSiegeAmount() {
    return siegeAmount;
}

i32 Player::getRamAmount() {
    return ramAmount;
}

i32 Player::getCatapultAmount() {
    return catapultAmount;
}

i32 Player::getSiderurgyAmount() {
    return siderurgyAmount;
}

i32 Player::getQuarryAmount() {
    return quarryAmount;
}

i32 Player::getWallAmount() {
    return wallAmount;
}

i32 Player::getTowerAmount() {
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
