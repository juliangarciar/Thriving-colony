#include "IA.h"
#include "Game.h"

IA::IA() : Player() {
    tree = new BehaviourTree();

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
Vector3<float>* IA::determinatePositionBuilding() {
    Vector3<float> *v = 0;
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
        v = new Vector3<float>(startingX, 0, startingZ);
        v -> y = Game::Instance() -> getGameState() ->getMap() -> getY(v -> x, v -> z);
    } else {

        //When there are some buildings
        Vector3<float> *v2 = 0;
        Vector3<float> *v3 = 0;
        for (std::map<int,Building*>::iterator it = b->begin(); it != b->end(); ++it){
            v2 = it -> second -> getPosition();
            occupied = false;
            v = new Vector3<float>(v2 -> x, v2 -> y, v2 -> z + 100);
            for (int j = 0; j < b -> size() && occupied == false; j++) {
                v3 = it -> second -> getPosition();
                if (v3 -> x == v -> x && v3 -> z == v -> z) {
                    occupied = true;
                }
            }
            if (occupied == false ) {
                found = true;
            } else {
                v = new Vector3<float>(v2 -> x + 100, v2 -> y, v2 -> z);
                occupied = false;
                for (int j = 0; j < b -> size() && occupied == false; j++) {
                    v3 = it -> second -> getPosition();
                    if (v3 -> x == v -> x && v3 -> z == v -> z) {
                        occupied = true;
                    }
                }
                if (occupied == false ) {
                    found = true;
                } else {
                    v = new Vector3<float>(v2 -> x, v2 -> y, v2 -> z - 100);
                    occupied = false;
                    for (int j = 0; j < b -> size() && occupied == false; j++) {
                        v3 = it -> second -> getPosition();
                        if (v3 -> x == v -> x && v3 -> z == v -> z) {
                            occupied = true;
                        }
                    }
                    if (occupied == false ) {
                        found = true;
                    } else {
                        v = new Vector3<float>(v2 -> x - 100, v2 -> y, v2 -> z);
                        occupied = false;
                        for (int j = 0; j < b -> size() && occupied == false; j++) {
                            v3 = it -> second -> getPosition();
                            if (v3 -> x == v -> x && v3 -> z == v -> z) {
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
        v -> y = Game::Instance() -> getGameState() ->getMap() -> getY(v -> x, v -> z);
    }
    return v;
}