#include "UnitManager.h"
#include "IA.h"
#include "Human.h"

//Constructor
UnitManager::UnitManager(Enumeration::Team teamData){
    selectedTroop = 0;
    this->teamManager = teamData;
    inHallTroops = new std::vector<Unit*>();
    inMapTroops = new std::vector<Unit*>();
    totalTroops = new std::vector<Unit*>();
}
//Destroyer
UnitManager::~UnitManager(){
    delete selectedTroop;

    inHallTroops->clear();
    delete inHallTroops;

    inMapTroops->clear();
    delete inMapTroops;

    totalTroops->clear();
    delete totalTroops;
}
//Returns all troops the player has
std::vector<Unit*> *UnitManager::getTotalTroops(){
    totalTroops->clear();
    totalTroops->reserve( inHallTroops->size() + inMapTroops->size() ); // preallocate memory
    totalTroops->insert( totalTroops->end(), inHallTroops->begin(), inHallTroops->end() );
    totalTroops->insert( totalTroops->end(), inMapTroops->begin(), inMapTroops->end() );
    return totalTroops;
} 
//Update all troops
void UnitManager::updateUnitManager(){
    for (int i = 0; i < inMapTroops -> size(); i++){
        inMapTroops -> at(i) -> updateTroop();
    }
}
//Create a new troops
//In order to add a new unit, you must specify which one
// ie: 
//Enumeration::UnitType unitData; 
//unitData.unitClass = Enumeration::UnitType::Class::Ranged; 
//unitData.unitSubClass = Enumeration::UnitType::SubClass::Idol;
bool UnitManager::createTroop(Enumeration::UnitType unitData){
    if (checkCanPay(unitData.unitSubClass)) {
        if(unitData.unitClass == Enumeration::UnitType::Ranged){
            Ranged *rangedUnit = new Ranged(unitData.unitSubClass, new Vector3<float>(), this->teamManager);
            this->inHallTroops -> push_back(rangedUnit);
            return true;
        }
        else if (unitData.unitClass == Enumeration::UnitType::Melee)
        {
            Melee *meleeUnit = new Melee(unitData.unitSubClass, new Vector3<float>(), this->teamManager);
            this->inHallTroops -> push_back(meleeUnit);
            return true;
        }
    }
    return false;
}

void UnitManager::deployTroop(int index, Vector3<float> *vectorData){
    this->inHallTroops->at(index)->setPos(vectorData);
    this->inMapTroops->push_back(inHallTroops->at(index));
    this->inHallTroops->erase(inHallTroops->begin() + index);
    //ToDo: mostrar en el mapa
}

//Select a troop
void UnitManager::selectTroop(Unit *troopData){
    this->selectedTroop = troopData;
}
//Pass the order to the selected unit
void UnitManager::newOrder(){

}

//////PARTE DE LA ECONOMIA PARA

/**
 * Checks if the player, either the human or the AI can afford to build a specific building 
 */
 // ESTE METODO ESTA REPETIDO AQUI Y EN BUILDING MANAGER IGUAL DEBERIAN HEREDAR
 // DE UNA CLASE MANAGER QUE TUVIESE AQUELLAS COSAS QUE FUESEN IGUALES
bool UnitManager::isSolvent(int metalCost, int crystalCost, Enumeration::Team team) {
    int metalAmt = 0;
    int crystalAmt = 0;
    if (team == Enumeration::Team::Human) {
        metalAmt = Human::getInstance() -> getMetalAmount();
        crystalAmt = Human::getInstance() -> getCrystalAmount();
        std::cout << metalAmt << " - " << metalCost << std::endl;
        std::cout << crystalAmt << " - " << crystalCost << std::endl;
    } else {
        metalAmt = IA::getInstance() -> getMetalAmount();
        crystalAmt = IA::getInstance() -> getCrystalAmount();
    }
    bool canPayMetal = metalAmt >= metalCost;
    bool canPayCrystal = crystalAmt >= crystalCost;

    return (canPayMetal && canPayCrystal);
}

/**
 * This method is responsible for managing calls to isSolvent() for the human, registering the type
 * of the desired building and sending the aforementhioned method the prices. It has its own method
 * to avoid cluttering the setBuildingMode() method, as it used to be there in the first place.
 */
 
bool UnitManager::checkCanPay(Enumeration::UnitType::SubClass type) {
    //ESto esta aqui para no hacer clutter arriba
    bool canPay = false;
    //CHECK IF YOU CAN PAY THE BUILDING
    
    switch(type){
    case Enumeration::UnitType::SubClass::StandardM:
        canPay = isSolvent(Enumeration::UnitCost::MeleeFootmenMetalCost, Enumeration::UnitCost::MeleeFootmenCrystalCost, Enumeration::Team::Human);
    break;
    case Enumeration::UnitType::SubClass::AdvancedM:
        canPay = isSolvent(Enumeration::UnitCost::MountedMeleeMetalCost, Enumeration::UnitCost::MountedMeleeCrystalCost, Enumeration::Team::Human);
    break;
    case Enumeration::UnitType::SubClass::Idol:
        canPay = isSolvent(Enumeration::UnitCost::CreatureMetalCost, Enumeration::UnitCost::CreatureCrystalCost, Enumeration::Team::Human);
    break;
    case Enumeration::UnitType::SubClass::Launcher:
        canPay = isSolvent(Enumeration::UnitCost::CatapultMetalCost, Enumeration::UnitCost::CatapultCrystalCost, Enumeration::Team::Human);
    break;
    case Enumeration::UnitType::SubClass::Desintegrator:
        canPay = isSolvent(Enumeration::UnitCost::RamMetalCost, Enumeration::UnitCost::RamCrystalCost, Enumeration::Team::Human);
    break;
    case Enumeration::UnitType::SubClass::StandardR:
        canPay = isSolvent(Enumeration::UnitCost::RangedFootmenMetalCost, Enumeration::UnitCost::RangedFootmenCrystalCost, Enumeration::Team::Human);
    break;
    case Enumeration::UnitType::SubClass::AdvancedR:
        canPay = isSolvent(Enumeration::UnitCost::MountedRangedMetalCost, Enumeration::UnitCost::MountedRangedCrystalCost, Enumeration::Team::Human);
    break;
    }
    return canPay;
}
