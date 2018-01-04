#include "Battle.h"
#include "IA.h"
#include "Human.h"
#include "Game.h"

#define BATTLERADIUS 60

Battle::Battle(float _x, float _y) {
    position = new Vector2<float>(_x, _y);
    humanTroops = new std::vector<Unit*>;
    iaTroops = new std::vector<Unit*>;
    humanBuildings = new std::vector<Building*>;
    iaBuildings = new std::vector<Building*>;

    unitFetchTimer = 1;
    buildingFetchTimer = 1;

    fetchUnits();
    fetchBuildings();
}

Battle::~Battle() {
    delete humanTroops;
    delete iaTroops;
    delete humanBuildings;
    delete iaBuildings;
    delete position;
}

std::vector<Unit*>* Battle::getHumanTroops() {
    return humanTroops;
}

std::vector<Unit*>* Battle::getIaTroops() {
    return iaTroops;
}

void Battle::update() {
    float dt = Game::Instance() ->getWindow() -> getDeltaTime();
    if (unitFetchTimer <= 0) {
        fetchUnits();
        unitFetchTimer = 1;
    } else {
        unitFetchTimer -= dt;
    }
    if (buildingFetchTimer <= 0) {
        fetchBuildings();
        buildingFetchTimer = 1;
    } else {
        buildingFetchTimer -= dt;
    }
    //Determine if there is only a team involved
    bool noIAPresence = (iaTroops -> size() == 0) && (iaBuildings -> size() == 0);
    bool noHumanPresence = (humanTroops -> size() == 0) && (humanBuildings -> size() == 0);
    if (noIAPresence || noHumanPresence) {
        //Battle is over
        this -> ~Battle();
    }
    determinateWinningSide();
}

/**
 * Fetches all units that are in the battle
 */
void Battle::fetchUnits() {
    //Empty the vector
    humanTroops ->clear();
    iaTroops -> clear();

    //Fetch the units vector from each player
    std::vector<Unit*> *humanArmy = new std::vector<Unit*>();/*Human::getInstance() -> getTroops();*/
    std::vector<Unit*> *iaArmy = new std::vector<Unit*>();/*IA::getInstance() -> getTroops();*/

    // Check every unit in the human army, if any is in range of the battle, add it to the vector
    for (int i = 0; i < humanArmy -> size(); i++) {
        if (determineWithinRange(humanArmy->at(i) -> getPosition())) {
            humanTroops -> push_back(humanArmy->at(i));
            //humanTroops -> at(i) -> assignBattle(this);
        }
    }

    // Check every unit in the IA army, if any is in range of the battle, add it to the vector
    for (int i = 0; i < iaArmy -> size(); i++) {
        if (determineWithinRange(iaArmy->at(i) -> getPosition())) {
            iaTroops -> push_back(iaArmy->at(i));
            //iaTroops -> at(i) -> assignBattle(this);
        }
    }
}

/**
 * Fetches all buildings that are in the battle
 */
void Battle::fetchBuildings() {
    //Empty the vector
    humanBuildings ->clear();
    iaBuildings -> clear();

    //Fetch the buildings vector from each player
    std::map<int, Building*> *humanCity = Human::getInstance() -> getBuildingManager() -> getBuildings();
    std::map<int, Building*> *iaCity = IA::getInstance() -> getBuildingManager() -> getBuildings();

    // Check every unit in the human army, if any is in range of the battle, add it to the vector
    for (int i = 0; i < humanCity -> size(); i++) {
        if (determineWithinRange(humanCity->at(i) -> getPosition())) {
            humanBuildings -> push_back(humanCity->at(i));
            //humanBuildings -> at(i) -> assignBattle(this);
        }
    }

    // Check every unit in the IA army, if any is in range of the battle, add it to the vector
    for (int i = 0; i < iaCity -> size(); i++) {
        if (determineWithinRange(iaCity->at(i) -> getPosition())) {
            iaBuildings -> push_back(iaCity->at(i));
            //iaBuildings -> at(i) -> assignBattle(this);
        }
    }
}

/*
* Determinate the winning side of a battle. A battle is considered losing when
* an army is outnumbered 7 to 3.
*/
void Battle::determinateWinningSide() {
    int totalUnits = iaTroops -> size() + humanTroops -> size();
    float iaPercentatge = iaTroops -> size() / totalUnits;

    if (iaPercentatge <= 0.3f) {
        // The IA is losing
        Game::Instance() -> getEvents() -> triggerEvent(Enumeration::EventType::RetractTroopsIA);
    } else if (iaPercentatge >= 0.7f) {
        //The player is losing
        //ToDo?: trigger algo?
    }
}

/**
 * Determines and returns wether or not the unit whose position is passed as argument
 * is within the range of the battle.
 */
bool Battle::determineWithinRange(Vector3<float>* unit) {
    float xComponent = unit -> x - position -> x;
    float yComponent = unit -> y - position -> y;
    float distance = sqrtf(pow(xComponent, 2) - pow(yComponent, 2));
    return (distance <= BATTLERADIUS);
}

/**
 * Receives the position of a unit and its team, and return the closest
 * unit pertaining to the enemy team.
 */
Entity* Battle::getClosestTarget(Vector3<float>* pos, Enumeration::Team team) {
    Entity* target = NULL;
    float minDistance = FLT_MAX; // Maximum value of float
    
    float xaux = 0;
    float yaux = 0;
    float dist = 0;

    // Look units as targets

    if (team == Enumeration::Team::Human) {
        // The unit requesting a target is human's
        for (int i = 0; i < iaTroops -> size(); i++) {
            if (iaTroops ->at(i) != NULL) {
                // Calculate distance between troop requesting target and posible targets
                xaux = iaTroops ->at(i) ->getPosition() -> x - position -> x;
                yaux = iaTroops ->at(i) ->getPosition() -> y - position -> y;
                dist = sqrtf(pow(xaux, 2) - pow(yaux, 2));

                if (dist < minDistance) {
                    minDistance = dist;
                    target = iaTroops -> at(i);
                }
            }
        }
    } else {
        // The unit requesting a target is bot's
        for (int i = 0; i < humanTroops -> size(); i++) {
            if (humanTroops ->at(i) != NULL) {
                // Calculate distance between troop requesting target and posible targets
                xaux = humanTroops ->at(i) ->getPosition() -> x - position -> x;
                yaux = humanTroops ->at(i) ->getPosition() -> y - position -> y;
                dist = sqrtf(pow(xaux, 2) - pow(yaux, 2));

                if (dist < minDistance) {
                    minDistance = dist;
                    target = humanTroops -> at(i);
                }
            }
        }
    }

    // If there are no units to attack, look for buildings as targets

    if (target == NULL) {
        if (team == Enumeration::Team::Human) {
            // The unit requesting a target is human's
            for (int i = 0; i < iaBuildings -> size(); i++) {
                if (iaBuildings ->at(i) != NULL) {
                    // Calculate distance between troop requesting target and posible targets
                    xaux = iaBuildings ->at(i) ->getPosition() -> x - position -> x;
                    yaux = iaBuildings ->at(i) ->getPosition() -> y - position -> y;
                    dist = sqrtf(pow(xaux, 2) - pow(yaux, 2));

                    if (dist < minDistance) {
                        minDistance = dist;
                        target = iaBuildings -> at(i);
                    }
                }
            }
        } else {
            // The unit requesting a target is bot's
            for (int i = 0; i < humanBuildings -> size(); i++) {
                if (humanBuildings ->at(i) != NULL) {
                    // Calculate distance between troop requesting target and posible targets
                    xaux = humanBuildings ->at(i) ->getPosition() -> x - position -> x;
                    yaux = humanBuildings ->at(i) ->getPosition() -> y - position -> y;
                    dist = sqrtf(pow(xaux, 2) - pow(yaux, 2));

                    if (dist < minDistance) {
                        minDistance = dist;
                        target = humanBuildings -> at(i);
                    }
                }
            }
        }
    }

    // If there are still no targets, this battle is probably over and this should have destroyed itself?

    if (target == NULL) {

    }
    return target;
}