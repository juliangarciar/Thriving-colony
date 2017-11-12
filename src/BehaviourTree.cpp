#include "BehaviourTree.h"

BehaviourTree::BehaviourTree(){

}

BehaviourTree::~BehaviourTree(){

}

//=====
// Calculates the ratio between metal production and city level
//=====
float BehaviourTree::calculateMetalProductionRate(){
    int cityLvl = ia->getCityLevel();
    int metalPr = ia->getMetalProduction();
    return (metalPr / cityLvl);
}

//=====
// Calculates the ratio between crystal production and city level
//=====
float BehaviourTree::calculateCrystalProductionRate(){
    int cityLvl = ia->getCityLevel();
    int crystalPr = ia->getCrystalProduction();
    return (crystalPr / cityLvl);
}

//=====
// Calculates the ratio between citizens and city level
//=====
float BehaviourTree::calculateCitizensRate(){
    int cityLvl = ia->getCityLevel();
    int citizens = ia->getCitizens();
    return (citizens / cityLvl);
}

//=====
// Calculates the ratio between citizens and army
//=====
float BehaviourTree::calculateArmyCitizensRate(){
    int armySize = ia->getArmySize();
    // Numbers of soldiers / Number of total cicitzens (citizens + soldiers)
    int totalCitizens = ia->getCitizens() + armySize;
    return (armySize / totalCitizens);
}

//=====
// Calculates the ratio between army and melee soldiers
//=====
float BehaviourTree::calculateMeleeRate(){
    int meleeAmt = ia->getMeleeAmount();
    int armySize = ia->getArmySize();
    return (meleeAmt / armySize);
}