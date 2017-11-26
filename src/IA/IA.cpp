#include "IA.h"

IA::IA() {
    happiness = 0;
    cityLevel = 1;
    
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

}

IA::~IA() {

}