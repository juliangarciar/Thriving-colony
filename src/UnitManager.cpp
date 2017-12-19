#include "UnitManager.h"

//Constructor
UnitManager::UnitManager(Enumeration::Team teamData){
    selectedTroop = 0;
    this->teamManager = teamData;
    totalTroops = new std::vector<Unit*>();
}
//Destroyer
UnitManager::~UnitManager(){
    delete selectedTroop;
    for (int i = 0; i < totalTroops -> size(); i++){
        delete totalTroops -> at(i);
    }
}
//Returns all troops the player has
std::vector<Unit*> *UnitManager::getTotalTroops(){
    return this -> totalTroops;
}
//Update all troops
void UnitManager::updateUnitManager(){
    for (int i = 0; i < totalTroops -> size(); i++){
        totalTroops -> at(i) -> updateTroop();
    }
}
//Create a new troops
//In order to add a new unit, you must specify which one
// ie: 
//Enumeration::UnitType unitData; 
//unitData.unitClass = Enumeration::UnitType::Class::Ranged; 
//unitData.unitSubClass = Enumeration::UnitType::SubClass::Idol;
void UnitManager::createTroop(Vector3<float> *vectorData, Enumeration::UnitType unitData){
    if(unitData.unitClass == Enumeration::UnitType::Ranged){
        Ranged *rangedUnit = new Ranged(unitData.unitSubClass, vectorData, this->teamManager);
        this->totalTroops -> push_back(rangedUnit);
    }
    else if (unitData.unitClass == Enumeration::UnitType::Melee)
    {
        Melee *meleeUnit = new Melee(unitData.unitSubClass, vectorData, this->teamManager);
        this->totalTroops -> push_back(meleeUnit);
    }
}
//Select a troop
void UnitManager::selectTroop(Unit *troopData){
    this->selectedTroop = troopData;
}
//Pass the order to the selected unit
void UnitManager::newOrder(){

}