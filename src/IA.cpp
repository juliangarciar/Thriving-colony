#include "IA.h"
#include "Game.h"

IA::IA() : Player() {
    tree = new BehaviourTree();
    nodeRootIA = new RootNode();

    units = new UnitManager(Enumeration::Team::IA);
}

IA::~IA() {
    delete tree;
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

void IA::update() {
    if (updateTimer <= 0) {
        gainResources();
        nodeRootIA -> question();
        updateTimer = 1;
    } else {
        updateTimer -= Window::Instance() -> getDeltaTime();
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
    // ToDo: como el primer edificio va a ser el centro de mandos que ya va a estar
    // construido, esto no haria falta. La ciudad empieza tambien con una cantera.
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
            v = Vector3<float>(v2 -> x, v2 -> y, v2 -> z + 100);
            for (std::map<int,Building*>::iterator it2 = b->begin(); it2 != b->end() && occupied == false; ++it2){
                v3 = it2 -> second -> getPosition();
                if (v3 -> x == v.x && v3 -> z == v.z) {
                    occupied = true;
                }
            }
            if (occupied == false ) {
                found = true;
            } else {
                v = Vector3<float>(v2 -> x + 100, v2 -> y, v2 -> z);
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
                    v = Vector3<float>(v2 -> x, v2 -> y, v2 -> z - 100);
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
                        v = Vector3<float>(v2 -> x - 100, v2 -> y, v2 -> z);
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