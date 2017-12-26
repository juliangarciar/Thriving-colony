#include "Human.h"
#include "Game.h"

Human::Human() : Player() {
    happiness = 0;
    cityLevel = 1;
    
    siderurgyAmount = 1;
    quarryAmount= 0;
    
    citizens = 500; //ToDo: bajar a 10 o asi

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

    
    units = new UnitManager(Enumeration::Team::Human, Enumeration::RaceType::Drorania);
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

void Human::update() {
    if (updateTimer <= 0) {
        //std::cout << "PRobando" << std::endl;
        gainResources();
        updateTimer = 1;
    } else {
        updateTimer -= Window::Instance() -> getDeltaTime();
    }
}

