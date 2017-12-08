#include "Battle.h"

Battle::Battle() {

}

Battle::~Battle() {

}

Unit **Battle::getHumanTroops() {
    return humanTroops;
}

Unit **Battle::getIaTroops() {
    return iaTroops;
}

/*
* Determinate the side that has more probabilities to win the battle
*/
void Battle::determinateWinnerSide() {
    
}