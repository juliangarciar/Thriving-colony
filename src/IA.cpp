#include "IA.h"

IA::IA() : Player() {
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

IA* IA::instance = 0;

IA* IA::getInstance() {
    if (instance == 0) {
        instance = new IA();
    }
    return instance;
}

BehaviourTree* IA::getTree() {
    return tree;
}
