#include "IA.h"
#include "Game.h"
#include "Human.h"

IA::IA() : Player() {
    tree = new BehaviourTree();
    nodeRootIA = new RootNode();

    buildings = new BuildingManager();
    units = new UnitManager(Enumeration::Team::IA, Enumeration::RaceType::Kaonov);
}

IA::~IA() {
    delete tree;
    delete nodeRootIA;
}

IA* IA::instance = 0;

bool IA::deployedTroops = false;
bool IA::closedDoors = false;

IA* IA::getInstance() {
    if (instance == 0) {
        instance = new IA();
    }
    return instance;
}

BehaviourTree* IA::getTree() {
    return tree;
}

void IA::update() {
    if (updateTimer <= 0) {
        gainResources();
        buildings -> updateBuildingManager();
        units -> updateUnitManager();
        nodeRootIA -> question();
        if (units -> getInMapTroops() -> empty()) {
            deployedTroops = false;
        }
        if (units -> getInHallTroops() -> empty()) {
            deployedTroops = true;
        }
        updateTimer = 1;
    } else {
        updateTimer -= Game::Instance() ->getWindow() -> getDeltaTime();
    }
}

/*
* Return a position of the map where there is nothing built
* Goes over the vector of buildings looking up, right, down and left of every building built
* until find the first empty position
*/
Vector3<float> IA::determinatePositionBuilding() {
    Vector3<float> v;
    bool found = false;
    bool occupied = false;
    std::map<int, Building*> *b = buildings -> getBuildings();

    // If it is the first building start always on the same position
    if (b -> size() == 0) {
        /**
         * These coordinates determine the position of the main building
         * the y component of it is determined based on the map
         */
        float startingX = 2000;
        float startingZ = 2000;
        v.set(startingX, 0, startingZ);
        v.y = Game::Instance() -> getGameState() ->getMap() -> getY(v.x, v.z);
    } else {

        //When there are some buildings
        Vector3<float> *v2 = 0;
        Vector3<float> *v3 = 0;
        for (std::map<int,Building*>::iterator it = b->begin(); it != b->end() && found == false; ++it){
            v2 = it -> second -> getPosition();
            occupied = false;
            v = Vector3<float>(v2 -> x, v2 -> y, v2 -> z + 200);
            for (std::map<int,Building*>::iterator it2 = b->begin(); it2 != b->end() && occupied == false; ++it2){
                v3 = it2 -> second -> getPosition();
                if (v3 -> x == v.x && v3 -> z == v.z) {
                    occupied = true;
                }
            }
            if (occupied == false ) {
                found = true;
            } else {
                v = Vector3<float>(v2 -> x + 200, v2 -> y, v2 -> z);
                occupied = false;
                for (std::map<int,Building*>::iterator it2 = b->begin(); it2 != b -> end() && occupied == false; ++it2){
                    v3 = it2 -> second -> getPosition();
                    if (v3 -> x == v.x && v3 -> z == v.z) {
                        occupied = true;
                    }
                }
                if (occupied == false ) {
                    found = true;
                } else {
                    v = Vector3<float>(v2 -> x, v2 -> y, v2 -> z - 200);
                    occupied = false;
                    for (std::map<int,Building*>::iterator it2 = b->begin(); it2 != b->end() && occupied == false; ++it2){
                        v3 = it2 -> second -> getPosition();
                        if (v3 -> x == v.x && v3 -> z == v.z) {
                            occupied = true;
                        }
                    }
                    if (occupied == false ) {
                        found = true;
                    } else {
                        v = Vector3<float>(v2 -> x - 200, v2 -> y, v2 -> z);
                        occupied = false;
                        for (std::map<int,Building*>::iterator it2 = b->begin(); it2 != b->end() && occupied == false; ++it2){
                            v3 = it2 -> second -> getPosition();
                            if (v3 -> x == v.x && v3 -> z == v.z) {
                                occupied = true;
                            }
                        }
                        if (occupied == false ) {
                            found = true;
                        }
                    }
                }
            }
        }
        v.y = Game::Instance() -> getGameState() ->getMap() -> getY(v.x, v.z);
    }
    return v;
}

void IA::deployTroops() {
    Vector3<float> v = *(IA::getInstance() -> getBuildingManager() -> getBuildings() -> begin() -> second -> getPosition());
    v.x = v.x + 100;
    v.y = Game::Instance() -> getGameState() -> getMap() -> getY(v.x, v.z);
    IA::getInstance() -> getUnitManager() -> deployAllTroops(v);
    deployedTroops = true;
}

void IA::closeDoors() {
    // ToDo: hacer de verdad
    closedDoors = true;
}

void IA::openDoors() {
    // ToDo: hacer de verdad
    closedDoors = false;
}

/*
* Troops come back to their building (barn, barrack or workshop)
*/
void IA::retractTroops() {
    Vector3<float> v = *(IA::getInstance() -> getBuildingManager() -> getBuildings() -> begin() -> second -> getPosition());
    IA::getInstance() -> getUnitManager() -> retractAllTroops(v);
}

bool IA::getUnderAttack() {
    if(underAttack == false){
        Vector3<float> *pos = buildings -> getBuildings() -> begin() -> second -> getPosition();
        int requesterRange = 1000;
        
        float xaux = 0;
        float yaux = 0;
        float dist = 0;

        // Get units in the map of the opposing team
        std::map<int, Unit*> *inMapTroops = Human::getInstance() -> getUnitManager() -> getInMapTroops();
        // Iterate through the map
        for (std::map<int,Unit*>::iterator it = inMapTroops->begin(); it != inMapTroops->end() && underAttack == false; ++it){
            if (it -> second != NULL) {
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
bool IA::getDeployedTroops() {
    return deployedTroops;
}

bool IA::getClosedDoors() {
    return closedDoors;
}