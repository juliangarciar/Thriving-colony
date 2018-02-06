#include "Human.h"
#include "Game.h"
#include "IA.h"

Human::Human() : Player() {
    init();
}

void Human::init() {
    updateTimer = 0;

    buildings = new BuildingManager(Enumeration::Team::Human, Enumeration::BreedType::Drorania);
    units = new UnitManager(Enumeration::Team::Human, Enumeration::BreedType::Drorania);
}

void Human::cleanUp() {
    delete buildings;
    delete units;
}

Human::~Human() {
    delete buildings;
    delete units;
}

Human* Human::instance = 0;

bool Human::deployedTroops = false;
bool Human::closedDoors = false;

Human* Human::getInstance() {
    if (instance == 0) {
        instance = new Human();
    }
    return instance;
}

void Human::update() {
    buildings -> updateBuildingManager();
    units -> updateUnitManager();
    if (updateTimer <= 0) {
        gainResources();
        if (units -> getInMapTroops() -> empty()) {
            deployedTroops = false;
        }
        if (units -> getInHallTroops() -> empty()) {
            deployedTroops = true;
        }
        updateTimer = 1;
    } else {
        updateTimer -= Game::Instance() -> getWindow() -> getDeltaTime();
    }
}

void Human::deployTroops() {
    Vector3<float> v = *(Human::getInstance() -> getBuildingManager() -> getBuildings() -> begin() -> second -> getPosition());
    v.x = v.x + 100;
    v.y = Game::Instance() -> getGameState() -> getTerrain() -> getY(v.x, v.z);
    Human::getInstance() -> getUnitManager() -> deployAllTroops(v);
    deployedTroops = true;
}

void Human::closeDoors() {
    // ToDo: hacer de verdad
    closedDoors = true;
}

void Human::openDoors() {
    // ToDo: hacer de verdad
    closedDoors = false;
}

/*
* Troops come back to their building (barn, barrack or workshop)
*/
void Human::retractTroops() {
    Vector3<float> v = *(Human::getInstance() -> getBuildingManager() -> getBuildings() -> begin() -> second -> getPosition());
    Human::getInstance() -> getUnitManager() -> retractAllTroops(v);
}

bool Human::getUnderAttack() {
    if(underAttack == false){
        Vector3<float> *pos = buildings -> getBuildings() -> begin() -> second -> getPosition();
        int requesterRange = 1000;
        
        float xaux = 0;
        float yaux = 0;
        float dist = 0;
        // Get units in the map of the opposing team
        std::map<int, Unit*> *inMapTroops = IA::getInstance() -> getUnitManager() -> getInMapTroops();
        // Iterate through the map
        for (std::map<int,Unit*>::iterator it = inMapTroops -> begin(); it != inMapTroops -> end() && underAttack == false; ++it){
            if (it  -> second != NULL) {
            // Calculate distance between troop requesting target and posible targets
                xaux = it -> second -> getPosition() -> x - pos -> x;
                yaux = it -> second -> getPosition() -> y - pos -> y;
                dist = sqrtf(pow(xaux, 2) - pow(yaux, 2));

                if (dist <= requesterRange) {
                    underAttack = true;
                }
            }
        }
    }
    return underAttack;
}

// Return wether or not our troops are deployed
bool Human::getDeployedTroops() {
    return deployedTroops;
}

bool Human::getClosedDoors() {
    return closedDoors;
}
/*
void Human::receiveMetal() {
    metalAmount = metalAmount + 200;
}

void Human::receiveCrystal() {
    crystalAmount = crystalAmount + 200;
}

void Human::receiveCitizens() {
    citizens = citizens + 100;
}
*/