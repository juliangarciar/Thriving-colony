#include "Battle.h"
#include "IA.h"
#include "Human.h"
#include "Game.h"

#define BATTLERADIUS 60

Battle::Battle(float _x, float _y) {
    position = new Vector2<float>(_x, _y);

    fetchUnits();
    humanTroops = new std::vector<Unit*>;
    iaTroops = new std::vector<Unit*>;
}

Battle::~Battle() {
    delete humanTroops;
    delete iaTroops;
    delete position;
}

std::vector<Unit*> Battle::getHumanTroops() {
    return *humanTroops;
}

std::vector<Unit*> Battle::getIaTroops() {
    return *iaTroops;
}

void Battle::update() {
    //if Timer
        fetchUnits();
    // }
    determinateWinningSide();
}

/**
 * Fetches all units that are in the battle
 */
void Battle::fetchUnits() {
    //Empty the vector
    humanTroops ->clear();
    iaTroops -> clear();

    //Fetch the units array from each player
    //ToDo: metodo get troops de player que te devuelva todas las unidades
    //      porque ahora esta por partes(getmelees, getranged, getsiege)
    //      y dependiendo de como acabe siendo la ia habra que hacerlo de
    //      una forma u otra

    std::vector<Unit*> humanArmy = Human::getInstance() -> getTroops();
    std::vector<Unit*> iaArmy = IA::getInstance() -> getTroops();
    // Check every unit in the human army, if any is in range of the battle, add it to the vector
    for (int i = 0; i < humanArmy -> size; i++) {
        if (determineWithinRange(humanArmy->at(i) -> getPosition())) {
            humanTroops -> push_back(humanArmy->at(i));
        }
    }
    // Check every unit in the IA army, if any is in range of the battle, add it to the vector
    for (int i = 0; i < iaArmy -> size; i++) {
        if (determineWithinRange(iaArmy->at(i) -> getPosition())) {
            iaTroops -> push_back(iaArmy->at(i));
        }
    }
}

/*
* Determinate the winning side of a battle. A battle is considered losing when
* an army is outnumbered 7 to 3.
*/
void Battle::determinateWinningSide() {
    int totalUnits = iaTroops -> size + humanTroops -> size;
    float iaPercentatge = iaTroops -> size / totalUnits;

    if (iaPercentatge <= 0.3f) {
        // The IA is losing
        Game::Instance() -> getEvents() -> triggerEvent(Enumeration::EventType::RetractTroops);
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