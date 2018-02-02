#include "UnitManager.h"
#include "IA.h"
#include "Human.h"
#include "Game.h"
#include "SoundEngine/SoundSystem.h"

//Constructor
UnitManager::UnitManager(Enumeration::Team teamData, Enumeration::BreedType raceData) {
    gridAlignment = 20;
    selectedTroop = 0; 

    teamManager = teamData;

    inHallTroops = new std::vector<Unit*>();
    //inMapTroops = new std::vector<Unit*>();
    inMapTroops = new std::map<int, Unit*>();
    //totalTroops = new std::vector<Unit*>();

    isDeployingTroop = false;
    currentDeployingTroop = -1;

    unitLayer = new SceneNode();

    selectedTroop = NULL;

    //Addes by Julian
    this -> breedType = raceData;
}

//Destroyer
UnitManager::~UnitManager() {
    delete selectedTroop;

    for (int i = 0; i < inHallTroops -> size(); i++) {
        inHallTroops -> erase(inHallTroops -> begin() + i);
    }
    inHallTroops -> clear();
    delete inHallTroops;

    for (std::map<int,Unit*>::iterator it = inMapTroops -> begin(); it != inMapTroops -> end(); ++it) {
		delete it -> second;
    }
    inMapTroops -> clear();
    delete inMapTroops;

    //totalTroops -> clear();
    //delete totalTroops;

    delete unitLayer;
}
//Returns all troops the player has
int UnitManager::getTotalTroops() {
    return inHallTroops -> size() + inMapTroops -> size();
} 
//Update all troops
void UnitManager::updateUnitManager() {
    for (std::map<int,Unit*>::iterator it = inMapTroops -> begin(); it != inMapTroops -> end(); ++it) {
        it -> second -> updateTroop();
        if (it -> second -> getMoving() == false && it -> second -> getRetracted() == true) {
            it -> second -> getModel() -> setActive(false);
            inHallTroops -> push_back(it -> second);
            inMapTroops -> erase(it);
        }
    }
}

//Create a new troops
//In order to add a new unit, you must specify which one
// ie: 
//Enumeration::UnitType unitData; 
//unitData.unitClass = Enumeration::UnitType::Class::Ranged; 
//unitData.unitSubClass = Enumeration::UnitType::SubClass::Idol;
bool UnitManager::createTroop(Enumeration::UnitType unitData) {
    if (checkCanPay(unitData)) {
        Unit *newUnit = new Unit(std::rand(), unitLayer, L"media/buildingModels/escuela.obj", Vector3<float>(), this -> teamManager, unitData, this -> breedType);
        newUnit -> getModel() -> setActive(false);
        this -> inHallTroops -> push_back(newUnit);
        return true;
    }
    return false;
}

void UnitManager::testRaycastCollisions() {
	if (!isDeployingTroop) {
		currentCollision = unitLayer -> getNodeCollision(Game::Instance() -> getMouse());
	}
} 

int UnitManager::getCollisionID() {
	if (currentCollision != NULL) {
		return currentCollision -> getSceneNode() -> getID();
	}
	return -1;
}

std::string UnitManager::getCollisionName() {
	if (currentCollision != NULL) {
		return currentCollision -> getSceneNode() -> getName();
	}
	return NULL;
}

/*
void UnitManager::deployTroopAtPosition(int index, Vector3<float> vectorData) {
    Unit *u = this -> inHallTroops -> at(index);
    u -> setPosition(vectorData);
    this -> inMapTroops -> insert(std::pair<int, Unit*>(u -> getModel() -> getID(), u));
    this -> inHallTroops -> erase(inHallTroops -> begin() + index);
}
*/

void UnitManager::startDeployingTroop(int index) { 
    Game *g = Game::Instance();
    if (!isDeployingTroop) {
        isDeployingTroop = true;
        currentDeployingTroop = index;
        selectedTroop = inHallTroops -> at(currentDeployingTroop);
    }
} 

void UnitManager::deployTroop(Terrain *terrain) { 
    Game *g = Game::Instance();
    if (isDeployingTroop && currentDeployingTroop >= 0 && g -> getMouse() -> leftMouseDown()) { 
        Unit *temp = inHallTroops -> at(currentDeployingTroop);

        this -> inHallTroops -> erase(inHallTroops -> begin() + currentDeployingTroop);
        this -> inMapTroops -> insert(std::pair<int, Unit*>(temp -> getID(), temp));

        temp -> setTroopPosition(Vector3<float>(Enumeration::HumanCityHall::human_x, terrain -> getY(Enumeration::HumanCityHall::human_x, Enumeration::HumanCityHall::human_z), Enumeration::HumanCityHall::human_z)); //ToDo
        
        temp -> switchState(Enumeration::UnitState::AttackMove);

        temp -> setTroopDestination(terrain -> getPointCollision(g -> getMouse()));
        temp -> getModel() -> setActive(true);
        temp -> setRetracted(false);
        
        
        g -> getMouse() -> changeIcon(CURSOR_NORMAL);

        currentDeployingTroop = -1;
        selectedTroop = NULL;
        isDeployingTroop = false;
    }
}

void UnitManager::deployAllTroops(Vector3<float> vectorData) {
    for (int i = inHallTroops -> size() - 1; i >= 0; i--) {
        Unit *u = inHallTroops -> at(i);
        this -> inHallTroops -> erase(inHallTroops -> begin() + i);
        this -> inMapTroops -> insert(std::pair<int, Unit*>(u -> getID(), u));

        u -> setTroopPosition(vectorData);
        u -> switchState(Enumeration::UnitState::AttackMove);
        u -> setTroopDestination(vectorData);
        u -> getModel() -> setActive(true);
        u -> setRetracted(false);
    }
}

void UnitManager::retractAllTroops(Vector3<float> vectorData) {
    for (std::map<int,Unit*>::iterator it = inMapTroops -> begin(); it != inMapTroops -> end(); ++it) {
        Unit *u = it -> second;
        u -> switchState(Enumeration::UnitState::Move);
        u -> setTroopDestination(vectorData);
        u -> setRetracted(true);
    }
}

//Select a troop
void UnitManager::selectTroop(int troopID) { 
    Game *g = Game::Instance();
    std::map<int,Unit*>::iterator it = inMapTroops -> find(troopID);
    if (it != inMapTroops -> end()) {
        this -> selectedTroop = it -> second;
        //SELECT VOICE
        SoundSystem::Instance() -> playVoiceEvent(selectedTroop -> getSelectEvent());
        g -> getMouse() -> changeIcon(CURSOR_CROSSHAIR);
    }
}

//Select a troop
void UnitManager::unSelectTroop() { 
    Game *g = Game::Instance();
    if (this -> selectedTroop != NULL){
        this -> selectedTroop = NULL;
        g -> getMouse() -> changeIcon(CURSOR_NORMAL);
    }
}


//Pass the order to the selected unit
void UnitManager::moveOrder(Terrain *terrain) {
    Game *g = Game::Instance();
    if (this -> selectedTroop != NULL) {
        this -> selectedTroop -> setTroopDestination(terrain -> getPointCollision(g -> getMouse()));
        if (Game::Instance() -> getKeyboard() -> keyPressed(GLFW_KEY_A)) { //ToDo: arreglar
            this -> selectedTroop -> switchState(Enumeration::UnitState::AttackMove);

            this -> selectedTroop -> setTroopDestination(terrain -> getPointCollision(g -> getMouse()));
        } else {
            this -> selectedTroop -> switchState(Enumeration::UnitState::Move);

            this -> selectedTroop -> setTroopDestination(terrain -> getPointCollision(g -> getMouse()));
        }
        //MOVEMENT VOICE
        SoundSystem::Instance() -> playVoiceEvent(selectedTroop -> getMoveEvent());
        //this -> selectedTroop -> setTroopDestination(terrain -> getPointCollision(g -> getMouse()));
        //Game::Instance() -> getSoundSystem() -> playVoice(this -> selectedTroop -> getMoveEvent());
    }
}

void UnitManager::startBattle(int enemyID) {
    //ToDo: crear batalla
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
 
bool UnitManager::checkCanPay(Enumeration::UnitType type) {
    //ESto esta aqui para no hacer clutter arriba
    bool canPay = false;
    //CHECK IF YOU CAN PAY THE BUILDING
    switch (type) {
    case Enumeration::UnitType::StandardM:
        canPay = isSolvent(Enumeration::UnitCost::MeleeFootmenMetalCost, Enumeration::UnitCost::MeleeFootmenCrystalCost, Enumeration::Team::Human);
    break;
    case Enumeration::UnitType::AdvancedM:
        canPay = isSolvent(Enumeration::UnitCost::MountedMeleeMetalCost, Enumeration::UnitCost::MountedMeleeCrystalCost, Enumeration::Team::Human);
    break;
    case Enumeration::UnitType::Idol:
        canPay = isSolvent(Enumeration::UnitCost::CreatureMetalCost, Enumeration::UnitCost::CreatureCrystalCost, Enumeration::Team::Human);
    break;
    case Enumeration::UnitType::Launcher:
        canPay = isSolvent(Enumeration::UnitCost::CatapultMetalCost, Enumeration::UnitCost::CatapultCrystalCost, Enumeration::Team::Human);
    break;
    case Enumeration::UnitType::Desintegrator:
        canPay = isSolvent(Enumeration::UnitCost::RamMetalCost, Enumeration::UnitCost::RamCrystalCost, Enumeration::Team::Human);
    break;
    case Enumeration::UnitType::StandardR:
        canPay = isSolvent(Enumeration::UnitCost::RangedFootmenMetalCost, Enumeration::UnitCost::RangedFootmenCrystalCost, Enumeration::Team::Human);
    break;
    case Enumeration::UnitType::AdvancedR:
        canPay = isSolvent(Enumeration::UnitCost::MountedRangedMetalCost, Enumeration::UnitCost::MountedRangedCrystalCost, Enumeration::Team::Human);
    break;
    }
    return canPay;
}

bool UnitManager::isTroopSelected() {
    if (selectedTroop != NULL) return true;
    else return false;
}

std::map<int, Unit*> * UnitManager::getInMapTroops() {
    return inMapTroops;
}

std::vector<Unit*> * UnitManager::getInHallTroops() {
    return inHallTroops;
}

Unit* UnitManager::getSelectedTroop() {
    return selectedTroop;
}

void UnitManager::deleteUnit(int id) {
    delete inMapTroops -> find(id) -> second;
    inMapTroops -> erase(id);
}