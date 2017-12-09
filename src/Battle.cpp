#include "Battle.h"
#include "IA.h"
#include "Human.h"
#include <vector>

#define BATTLERADIUS 60

Battle::Battle(int _x, int _y) {
    x = _x;
    y = _y;

    fetchUnits();
    humanTroops = new std::vector<Unit*>;
    iaTroops = new std::vector<Unit*>;
}

Battle::~Battle() {
    delete humanTroops;
    delete iaTroops;
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

    Unit** humanArmy = Human::getInstance() -> getTroops();
    Unit** iaArmy = IA::getInstance() -> getTroops();
    // Check every unit in the human army, if any is in range of the battle, add it to the vector
    for (int i = 0; i < Human::getInstance() -> getArmySize(); i++) {
        if (determineWithinRange(humanArmy[i].getPosition())) {
            humanTroops.push(humanArmy[i]);

        }
    }
    // Check every unit in the IA army, if any is in range of the battle, add it to the vector
    for (int i = 0; i < IA::getInstance() -> getArmySize(); i++) {
        if (determineWithinRange(iaArmy[i] -> getPosition())) {
            iaTroops.push(iaArmy[i]);
        }
    }
}

/*
* Determinate the winning side of a battle. A battle is considered losing when
* an army is outnumbered 7 to 3.
*/
void Battle::determinateWinningSide() {
    int totalUnits = iaTroops -> size + humanTroops -> size;
    float iaPercentatge = iAArmySize / totalUnits;

    if (iaPercentatge <= 0.3f) {
        // The IA is losing
        //ToDo: trigger retirada
    } else if (iaPercentatge >= 0.7f) {
        //The player is losing
        //ToDo?: trigger algo?
    }
}

/**
 * Determines and returns wether or not the unit whose position is passed as argument
 * is within the range of the battle.
 */
bool Battle::determineWithingRange(Vector3 unit) {
    float xComponent = unit->x - position ->x;
    float yComponent = unit->y - position ->y;
    float distance = sqrtf(xComponent² - yComponent²);
    return (distance <= BATTLERADIUS);
}