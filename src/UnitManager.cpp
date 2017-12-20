#include "UnitManager.h"

//Constructor
UnitManager::UnitManager(Enumeration::Team teamData){
    //selectedTroop = NULL;
    this->teamManager = teamData;
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
//Create a new troops
//In order to add a new unit, you must specify which one
// ie: 
//Enumeration::UnitType unitData; 
//unitData.unitClass = Enumeration::UnitType::Class::Ranged; 
//unitData.unitSubClass = Enumeration::UnitType::SubClass::Idol;
void UnitManager::createTroop(Vector3<float> *vectorData, Enumeration::UnitType unitData){
    if(unitData.unitClass == Enumeration::UnitType::Ranged){
        Ranged *rangedUnit = new Ranged(unitData.unitSubClass, vectorData, this->teamManager);
        this->totalTroops.push_back(rangedUnit);
    }
    else if (unitData.unitClass == Enumeration::UnitType::Melee)
    {
        Melee *meleeUnit = new Melee(unitData.unitSubClass, vectorData, this->teamManager);
        this->totalTroops.push_back(meleeUnit);
    }
}
//Select a troop
void UnitManager::selectTroop(Unit *troopData){
    this->selectedTroop = troopData;
}
//Pass the order to the selected unit
void UnitManager::newOrder(){

}

//////PARTECITA DE RAFA


/**
 * Checks if the player, either the human or the AI can afford to build a specific building 
 */
// TODO ESTE METODO ESTA EXATCAMENTE IGUAL EN EL BUILDING MANAGER (IGUAL DEBERIAN HEREDAR DE UNA CLASE
// MANAGER QUE TENGA COMO COSAS COMPARTIDAS? QUIEN SABE
bool BuildingManager::isSolvent(int metalCost, int crystalCost, Enumeration::Team team) {
	int metalAmt = 0;
	int crystalAmt = 0;
	if (team == Enumeration::Team::Human) {
		metalAmt = Human::getInstance() -> getMetalAmount();
		crystalAmt = Human::getInstance() -> getCrystalAmount();
	} else {
		metalAmt = IA::getInstance() -> getMetalAmount();
		crystalAmt = IA::getInstance() -> getCrystalAmount();
		////std::cout << metalAmt << "/" << metalCost << std::endl;
	}
	bool canPayMetal = metalAmt >= metalCost;
	bool canPayCrystal = crystalAmt >= crystalCost;
    
    return (canPayMetal && canPayCrystal);
}

//TODO CAMBIAR PERO PARA TROPAS Y NO EDIFICIOS

/**
 * This method is responsible for managing calls to isSolvent() for the human, registering the type
 * of the desired building and sending the aforementhioned method the prices. It has its own method
 * to avoid cluttering the setBuildingMode() method, as it used to be there in the first place.
 */
bool BuildingManager::checkCanPay(Enumeration::BuildingType type) {
	//ESto esta aqui para no hacer clutter arriba
	bool canPay = false;

	//CHECK IF YOU CAN PAY THE BUILDING
	switch(type){
        case Enumeration::BuildingType::School:
			canPay = isSolvent(Enumeration::BuildingCost::SchoolMetalCost, Enumeration::BuildingCost::SchoolCrystalCost, Enumeration::Team::Human);
        break;
        case Enumeration::BuildingType::Market:
			canPay = isSolvent(Enumeration::BuildingCost::MarketMetalCost, Enumeration::BuildingCost::MarketCrystalCost, Enumeration::Team::Human);
        break;
        case Enumeration::BuildingType::Hospital:
			canPay = isSolvent(Enumeration::BuildingCost::HospitalMetalCost, Enumeration::BuildingCost::HospitalCrystalCost, Enumeration::Team::Human);
        break;
        case Enumeration::BuildingType::Siderurgy:
			canPay = isSolvent(Enumeration::BuildingCost::SiderurgyMetalCost, Enumeration::BuildingCost::SiderurgyCrystalCost, Enumeration::Team::Human);
        break;
        case Enumeration::BuildingType::Quarry:
			canPay = isSolvent(Enumeration::BuildingCost::QuarryMetalCost, Enumeration::BuildingCost::QuarryCrystalCost, Enumeration::Team::Human);
        break;
        case Enumeration::BuildingType::House:
			canPay = isSolvent(Enumeration::BuildingCost::HomeMetalCost, Enumeration::BuildingCost::HomeCrystalCost, Enumeration::Team::Human);
        break;
        case Enumeration::BuildingType::Barrack:
			canPay = isSolvent(Enumeration::BuildingCost::BarrackMetalCost, Enumeration::BuildingCost::BarrackCrystalCost, Enumeration::Team::Human);
        break;
        case Enumeration::BuildingType::Barn:
			canPay = isSolvent(Enumeration::BuildingCost::BarnMetalCost, Enumeration::BuildingCost::BarnCrystalCost, Enumeration::Team::Human);
        break;
        case Enumeration::BuildingType::Workshop:
			canPay = isSolvent(Enumeration::BuildingCost::WorkshopMetalCost, Enumeration::BuildingCost::WorkshopCrystalCost, Enumeration::Team::Human);
        break;
        case Enumeration::BuildingType::Wall:
			canPay = isSolvent(Enumeration::BuildingCost::WallMetalCost, Enumeration::BuildingCost::WallCrystalCost, Enumeration::Team::Human);
        break;
        case Enumeration::BuildingType::Tower:
			canPay = isSolvent(Enumeration::BuildingCost::TowerMetalCost, Enumeration::BuildingCost::TowerCrystalCost, Enumeration::Team::Human);
        break;
	}
	return canPay;
}