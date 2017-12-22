#include "UnitManager.h"
#include "IA.h"
#include "Human.h"
#include "Game.h"

//Constructor
UnitManager::UnitManager(Enumeration::Team teamData){
    gridAlignment = 20;
    selectedTroop = 0; 

    teamManager = teamData;

    inHallTroops = new std::vector<Unit*>();
    //inMapTroops = new std::vector<Unit*>();
    inMapTroops = new std::map<int, Unit*>();
    totalTroops = new std::vector<Unit*>();

    isDeployingTroop = false;
    currentDeployingTroop = -1;

    unitLayer = new SceneNode();

    selectedTroop = NULL;
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

    delete unitLayer;
}
//Returns all troops the player has
int UnitManager::getTotalTroops(){
    return inHallTroops->size() + inMapTroops->size();
} 
//Update all troops
void UnitManager::updateUnitManager(){
    for (std::map<int,Unit*>::iterator it = inMapTroops->begin(); it != inMapTroops->end(); ++it){
        it -> second-> updateTroop();
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
            Ranged *rangedUnit = new Ranged(std::rand(), unitLayer, unitData.unitSubClass, Vector3<float>(), this->teamManager);
            rangedUnit->getModel()->setActive(false);
            this->inHallTroops -> push_back(rangedUnit);
            return true;
        }
        else if (unitData.unitClass == Enumeration::UnitType::Melee)
        {
            Melee *meleeUnit = new Melee(std::rand(), unitLayer, unitData.unitSubClass, Vector3<float>(), this->teamManager);
            meleeUnit->getModel()->setActive(false);
            this->inHallTroops -> push_back(meleeUnit);
            return true;
        }
    }
    return false;
}

void UnitManager::testRaycastCollisions(){
	if (!isDeployingTroop) {
		currentCollision = unitLayer -> getNodeCollision(Game::Instance() -> getCursor());
	}
} 

int UnitManager::getCollisionID(){
	if (currentCollision != NULL){
		return currentCollision->getSceneNode()->getID();
	}
	return -1;
}

std::string UnitManager::getCollisionName(){
	if (currentCollision != NULL){
		return currentCollision->getSceneNode()->getName();
	}
	return NULL;
}

void UnitManager::deployTroopAtPosition(int index, Vector3<float> vectorData){
    Unit *u = this->inHallTroops->at(index);
    u->setPosition(vectorData);
    this->inMapTroops->insert(std::pair<int, Unit*>(u->getModel()->getID(), u));
    this->inHallTroops->erase(inHallTroops->begin() + index);
}

void UnitManager::startDeployingTroop(int index){ 
    Game *g = Game::Instance();
    if (!isDeployingTroop){
        isDeployingTroop = true;
        currentDeployingTroop = index;
        selectedTroop = inHallTroops->at(currentDeployingTroop);
        g->getCursor()->getCursor()->setActiveIcon(gui::ECURSOR_ICON::ECI_CROSS); //ToDo: fachada
    }
} 

void UnitManager::deployTroop(Terrain *terrain){ 
    Game *g = Game::Instance();
    if (isDeployingTroop && currentDeployingTroop >= 0 && g->getIO() -> leftMouseDown()){ 
        Unit *temp = inHallTroops->at(currentDeployingTroop);

        this->inHallTroops->erase(inHallTroops->begin() + currentDeployingTroop);
         this->inMapTroops->insert(std::pair<int, Unit*>(temp->getModel()->getID(), temp));

        //g -> getSoundSystem() -> playVoice(troopData->getMoveEvent());
        temp->setTroopPosition(Vector3<float>(HUMAN_CITY_HALL_X, terrain->getY(HUMAN_CITY_HALL_X, HUMAN_CITY_HALL_Z), HUMAN_CITY_HALL_Z)); //ToDo
        temp->setTroopDestination(terrain -> getPointCollision(g -> getCursor()));
        temp->getModel()->setActive(true);
        
        g->getCursor()->getCursor()->setActiveIcon(gui::ECURSOR_ICON::ECI_NORMAL); //ToDo: fachada

        currentDeployingTroop = -1;
        selectedTroop = NULL;
        isDeployingTroop = false;
    }
}

//Select a troop
void UnitManager::selectTroop(int troopID){ 
    Game *g = Game::Instance();
    std::map<int,Unit*>::iterator it = inMapTroops->find(troopID);
    if (it != inMapTroops->end()) {
        this->selectedTroop = it->second;
        Game::Instance()->getSoundSystem()->playVoice(troopData->getSelectEvent());
        g->getCursor()->getCursor()->setActiveIcon(gui::ECURSOR_ICON::ECI_CROSS); //ToDo: fachada
    }
}

//Select a troop
void UnitManager::unSelectTroop(){ 
    Game *g = Game::Instance();
    if (this->selectedTroop != NULL){
        this->selectedTroop = NULL;
        g->getCursor()->getCursor()->setActiveIcon(gui::ECURSOR_ICON::ECI_NORMAL); //ToDo: fachada
    }
}


//Pass the order to the selected unit
void UnitManager::newOrder(Terrain *terrain){
    Game *g = Game::Instance();
    if (this->selectedTroop != NULL){
        this->selectedTroop->setTroopDestination(terrain -> getPointCollision(g -> getCursor()));
    }
}

//////PARTE DE LA ECONOMIA PARA RAFA

/**
 * Checks if the player, either the human or the AI can afford to build a specific building 
 */
 // ESTE METODO ESTA REPETIDO AQUI Y EN BUILDING MANAGER IGUAL DEBERIAN HEREDAR
 // DE UNA CLASE MANAGER QUE TUVIESE AQUELLAS COSAS QUE FUESEN IGUALES
bool UnitManager::isSolvent(int metalCost, int crystalCost, Enumeration::Team team) {
    int metalAmt = 0;
    int crystalAmt = 0;
    int citizensAmt = 0;
    if (team == Enumeration::Team::Human) {
        metalAmt = Human::getInstance() -> getMetalAmount();
        crystalAmt = Human::getInstance() -> getCrystalAmount();
        citizensAmt = Human::getInstance() -> getCitizens();
        //std::cout << metalAmt << " - " << metalCost << std::endl;
        //std::cout << crystalAmt << " - " << crystalCost << std::endl;
    } else {
        metalAmt = IA::getInstance() -> getMetalAmount();
        crystalAmt = IA::getInstance() -> getCrystalAmount();
        citizensAmt = IA::getInstance() -> getCitizens();
    }
    bool canPayMetal = metalAmt >= metalCost;
    bool canPayCrystal = crystalAmt >= crystalCost;
    bool hasCitizens = citizensAmt >= 10;

    return (canPayMetal && canPayCrystal && hasCitizens);
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

bool UnitManager::isTroopSelected(){
    if (selectedTroop != NULL) return true;
    else return false;
}