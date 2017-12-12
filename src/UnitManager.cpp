#include "UnitManager.h"

//Constructor
UnitManager::UnitManager(){
    //selectedTroop = NULL;

}
//Destroyer
UnitManager::~UnitManager(){
    delete selectedTroop;
    for (int i = 0; i < totalTroops.size(); i++){
        delete totalTroops[i];
    }
}
//Returns all troops the player has
std::vector < Unit* > UnitManager::getTotalTroops(){
    return this->totalTroops;
}
//Update all troops
void UnitManager::updateUnitManager(){
    for (int i = 0; i < totalTroops.size(); i++){
        totalTroops[i]->updateTroop();
    }
}
//Create a new troops (not defined yet)
void UnitManager::createTroop(){

}
//Select a troop
void UnitManager::selectTroop(Unit *troopData){
    this->selectedTroop = troopData;
}
//Pass the order to the selected unit
void UnitManager::newOrder(){

}