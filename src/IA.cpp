#include "IA.h"

IA::IA() : Player() {
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

    tree = new BehaviourTree();
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

Vector3<float>* IA::determinatePositionBuilding() {
    bool found = false;
    bool occupied = false;
    std::vector<Building*> *b = buildings -> getBuildings();
    if (b -> size() == 0) {
        std::cout<<"llega1"<<std::endl;
        Vector3<float> *v = new Vector3<float>(1600, 300, 1500);
        return v;
    } else {
        std::cout<<"llega1"<<std::endl;
        Vector3<float> *v = 0;
        Vector3<float> *v2 = 0;
        Vector3<float> *v3 = 0;
        for (int i = 0; i < b -> size() || found == false; i++) {
            v2 = b -> at(i) -> getPosition();
            occupied = false;
            v = new Vector3<float>(v2 -> x, v2 -> y + 100, v2 -> z);
            for (int j = 0; j < b -> size() || occupied == false; j++) {
                v3 = b -> at(j) -> getPosition();
                if (v3 -> x == v -> x && v3 -> y == v -> y) {
                    occupied = true;
                }
            }
            if (occupied == false ) {
                found = true;
            } else {
                v = new Vector3<float>(v2 -> x + 100, v2 -> y, v2 -> z);
                occupied = false;
                for (int j = 0; j < b -> size() || occupied == false; j++) {
                    v3 = b -> at(j) -> getPosition();
                    if (v3 -> x == v -> x && v3 -> y == v -> y) {
                        occupied = true;
                    }
                }
                if (occupied == false ) {
                    found = true;
                } else {
                    v = new Vector3<float>(v2 -> x, v2 -> y - 100, v2 -> z);
                    occupied = false;
                    for (int j = 0; j < b -> size() || occupied == false; j++) {
                        v3 = b -> at(j) -> getPosition();
                        if (v3 -> x == v -> x && v3 -> y == v -> y) {
                            occupied = true;
                        }
                    }
                    if (occupied == false ) {
                        found = true;
                    } else {
                        v = new Vector3<float>(v2 -> x - 100, v2 -> y, v2 -> z);
                        occupied = false;
                        for (int j = 0; j < b -> size() || occupied == false; j++) {
                            v3 = b -> at(j) -> getPosition();
                            if (v3 -> x == v -> x && v3 -> y == v -> y) {
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
    return v;
    }
}