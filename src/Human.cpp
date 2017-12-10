#include "Human.h"

Human::Human() : Player() {
    happiness = 0;
    cityLevel = 1;
    
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
}

Human::~Human() {

}

Human* Human::instance = 0;

Human* Human::getInstance() {
    if (instance == 0) {
        instance = new Human();
    }
    return instance;
}

