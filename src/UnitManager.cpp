#include "UnitManager.h"
#include "IA.h"
#include "Human.h"
#include "Game.h"
#include "SoundEngine/SoundSystem.h"
#include "PathPlanner/PathManager.h"
//Constructor
UnitManager::UnitManager(Enumeration::Team t, Enumeration::BreedType b) {
    gridAlignment = 20;
    selectedTroop = 0; 

    //Addes by Julian
    team = t;
    breed = b;

    unitLayer = new SceneNode();

    inQueueTroops = new std::vector<Unit*>(); //ToDo: por aqui me quedo (falta esto y HUD)
    inHallTroops = new std::vector<Unit*>();
    inMapTroops = new std::map<int, Unit*>();

    isDeployingTroop = false;
    currentDeployingTroop = -1;

    selectedTroop = NULL;

	for (int i = 0; i < Enumeration::UnitType::TroopsSize; i++){
		troopsAmount[i] = 0;
	}
}

//Destroyer
UnitManager::~UnitManager() {
    delete selectedTroop;

    for (int i = 0; i < inQueueTroops -> size(); i++) {
        inQueueTroops -> erase(inQueueTroops -> begin() + i);
    }
    inQueueTroops -> clear();
    delete inQueueTroops;

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

    delete unitLayer;
}

//Create a new troops
//In order to add a new unit, you must specify which one
bool UnitManager::createTroop(Enumeration::UnitType unitData) {
    if (checkCanPay(unitData)) {
        Unit *newUnit = new Unit(unitLayer, std::rand(), L"media/buildingModels/dummy.obj", team, breed, unitData, Vector3<float>());
        newUnit -> getModel() -> setActive(false);
        newUnit -> getModel() -> setScale(Vector3<float>(100, 100, 100));
        newUnit -> setRecruitedCallback([&] (Unit* u){
            std::cout << "Si" << std::endl;
            //Delete in Queue
            ptrdiff_t pos = distance(inQueueTroops->begin(), find(inQueueTroops->begin(), inQueueTroops->end(), u));
            inQueueTroops->erase(inQueueTroops->begin()+pos);

            //Add in Hall
            inHallTroops->push_back(u);
            
            //ToDo: modificar el HUD
        });
        newUnit -> setRetractedCallback([&] (Unit *u){
            //Delete in Map
            inMapTroops->erase(u->getID());

            //Add in Hall
            inHallTroops->push_back(u);

            //ToDo: modificar el HUD
        });

        inQueueTroops -> push_back(newUnit);

        troopsAmount[unitData]++;
        return true;
    }
    return false;
}

//Update all troops
void UnitManager::updateUnitManager() {
    for (int i=0; i < inQueueTroops->size(); i++){
        inQueueTroops->at(i)->update();
    }
    /*for (int i=0; i < inHallTroops->size(); i++){
        inHallTroops->at(i);
    }*/
    for (std::map<int,Unit*>::iterator it = inMapTroops -> begin(); it != inMapTroops -> end(); ++it) {
        it -> second -> update();
    }
}

void UnitManager::testRaycastCollisions() {
	if (!isDeployingTroop) {
		currentCollision = unitLayer -> getNodeCollision(Game::Instance() -> getMouse());
	}
} 

void UnitManager::startDeployingTroop(int index) {
    if (!isDeployingTroop) {
        isDeployingTroop = true;
        currentDeployingTroop = index;
        selectedTroop = inHallTroops -> at(currentDeployingTroop);
    }
} 

void UnitManager::deployTroop() { 
    Game *g = Game::Instance();
    if (isDeployingTroop && currentDeployingTroop >= 0 && g -> getMouse() -> leftMouseDown()) { 
        Unit *temp = inHallTroops -> at(currentDeployingTroop);

        //Delete in Queue
        ptrdiff_t pos = distance(inHallTroops->begin(), find(inHallTroops->begin(), inHallTroops->end(), temp));
        inHallTroops->erase(inHallTroops->begin()+pos);

        //Insert in map
        inMapTroops -> insert(std::pair<int, Unit*>(temp -> getModel() -> getID(), temp));

        temp -> setTroopPosition(Vector3<float>(Enumeration::HumanCityHall::human_x+100, g -> getGameState() -> getTerrain() -> getY(Enumeration::HumanCityHall::human_x, Enumeration::HumanCityHall::human_z), Enumeration::HumanCityHall::human_z)); //ToDo
        
        // Why attack move
        temp -> switchState(Enumeration::UnitState::AttackMove);

        temp -> setPathToTarget(g -> getGameState() -> getTerrain() -> getPointCollision(g -> getMouse()));
        
        temp -> getModel() -> setActive(true);
        // ToDo: esto para que era?
        //temp -> setRetracted(false);
        
        g -> getMouse() -> changeIcon(CURSOR_NORMAL);

        currentDeployingTroop = -1;
        selectedTroop = NULL;
        isDeployingTroop = false;
    }
}

void UnitManager::deployAllTroops(Vector3<float> vectorData) {
    for (int i = inHallTroops -> size() - 1; i >= 0; i--) {
        Unit *u = inHallTroops -> at(i);
        inHallTroops -> erase(inHallTroops -> begin() + i);
        inMapTroops -> insert(std::pair<int, Unit*>(u -> getModel() -> getID(), u));

        u -> setTroopPosition(vectorData);
        u -> switchState(Enumeration::UnitState::AttackMove);
        u -> setTroopDestination(vectorData);
        u -> getModel() -> setActive(true);
        // ToDo: esto para que era?
        //temp -> setRetracted(false);
    }
}

void UnitManager::retractAllTroops(Vector3<float> vectorData) {
    for (std::map<int,Unit*>::iterator it = inMapTroops -> begin(); it != inMapTroops -> end(); ++it) {
        Unit *u = it -> second;
        u -> switchState(Enumeration::UnitState::Retract);
        u -> setTroopDestination(vectorData);
        // ToDo: esto para que era?
        //temp -> setRetracted(false);
    }
}

//Select a troop
void UnitManager::selectTroop(int troopID) { 
    Game *g = Game::Instance();
    std::map<int,Unit*>::iterator it = inMapTroops -> find(troopID);
    if (it != inMapTroops -> end()) {
        selectedTroop = it -> second;
        //SELECT VOICE
        g -> getMouse() -> changeIcon(CURSOR_CROSSHAIR);
        //SoundSystem::Instance() -> playVoiceEvent(selectedTroop -> getSelectEvent());
    }
}

//Select a troop
void UnitManager::unSelectTroop() { 
    Game *g = Game::Instance();
    if (selectedTroop != NULL){
        selectedTroop = NULL;
        g -> getMouse() -> changeIcon(CURSOR_NORMAL);
    }
}

//Pass the order to the selected unit
void UnitManager::moveOrder() {
    Game *g = Game::Instance();
    if (selectedTroop != NULL) {
        selectedTroop -> setTroopDestination(g -> getGameState() -> getTerrain() -> getPointCollision(g -> getMouse()));
        if (Game::Instance() -> getKeyboard() -> keyPressed(GLFW_KEY_A)) { //ToDo: fachada
        // ToDo by Julian -> change attack iddle to pathfinding mode
            selectedTroop -> switchState(Enumeration::UnitState::AttackMove);

            selectedTroop->setPathToTarget(g -> getGameState() -> getTerrain() -> getPointCollision(g -> getMouse()));
        } else {
            selectedTroop -> switchState(Enumeration::UnitState::Move);

            selectedTroop->setPathToTarget(g -> getGameState() -> getTerrain() -> getPointCollision(g -> getMouse()));
        }
        //MOVEMENT VOICE
        //SoundSystem::Instance() -> playVoiceEvent(selectedTroop -> getMoveEvent());
    }
}

void UnitManager::startBattle(int enemyID) {
    //ToDo: crear batalla
}

// Checks if the player, either the human or the AI can afford to build a specific building 
// ToDo: ESTE METODO Y EL DE DEBAJO ESTAN REPETIDO AQUI Y EN BUILDING MANAGER IGUAL
// DEBERIAN HEREDAR DE UNA CLASE MANAGER QUE TUVIESE AQUELLAS COSAS QUE FUESEN IGUALES
bool UnitManager::isSolvent(int metalCost, int crystalCost) {
    int metalAmt = 0;
    int crystalAmt = 0;
    int citizensAmt = 0;
    if (team == Enumeration::Team::Human) {
        metalAmt = Human::getInstance() -> getMetalAmount();
        crystalAmt = Human::getInstance() -> getCrystalAmount();
        citizensAmt = Human::getInstance() -> getCitizens();
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
            canPay = isSolvent(Enumeration::UnitCost::MeleeFootmenMetalCost, Enumeration::UnitCost::MeleeFootmenCrystalCost);
        break;
        case Enumeration::UnitType::AdvancedM:
            canPay = isSolvent(Enumeration::UnitCost::MountedMeleeMetalCost, Enumeration::UnitCost::MountedMeleeCrystalCost);
        break;
        case Enumeration::UnitType::Idol:
            canPay = isSolvent(Enumeration::UnitCost::CreatureMetalCost, Enumeration::UnitCost::CreatureCrystalCost);
        break;
        case Enumeration::UnitType::Launcher:
            canPay = isSolvent(Enumeration::UnitCost::CatapultMetalCost, Enumeration::UnitCost::CatapultCrystalCost);
        break;
        case Enumeration::UnitType::Desintegrator:
            canPay = isSolvent(Enumeration::UnitCost::RamMetalCost, Enumeration::UnitCost::RamCrystalCost);
        break;
        case Enumeration::UnitType::StandardR:
            canPay = isSolvent(Enumeration::UnitCost::RangedFootmenMetalCost, Enumeration::UnitCost::RangedFootmenCrystalCost);
        break;
        case Enumeration::UnitType::AdvancedR:
            canPay = isSolvent(Enumeration::UnitCost::MountedRangedMetalCost, Enumeration::UnitCost::MountedRangedCrystalCost);
        break;
        default: break;
    }
    return canPay;
}

bool UnitManager::isTroopSelected() {
    if (selectedTroop != NULL) return true;
    else return false;
}

void UnitManager::deleteUnit(int id) {
    delete inMapTroops -> find(id) -> second;
    inMapTroops -> erase(id);
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

std::map<int, Unit*> * UnitManager::getInMapTroops() {
    return inMapTroops;
}

std::vector<Unit*> * UnitManager::getInHallTroops() {
    return inHallTroops;
}

Unit* UnitManager::getSelectedTroop() {
    return selectedTroop;
}

int UnitManager::getTroopAmount(Enumeration::UnitType t){
    return troopsAmount[(int)t];
}

//Returns all troops the player has
int UnitManager::getTotalTroops() {
    return inHallTroops -> size() + inMapTroops -> size();
} 

/*
void UnitManager::deployTroopAtPosition(int index, Vector3<float> vectorData) {
    Unit *u = inHallTroops -> at(index);
    u -> setPosition(vectorData);
    inMapTroops -> insert(std::pair<int, Unit*>(u -> getModel() -> getID(), u));
    inHallTroops -> erase(inHallTroops -> begin() + index);

    //temp -> setPosition(Vector3<float>(8000, 0, 8000));
    //temp -> setTroopDestination(terrain -> getPointCollision(g -> getMouse()));
    //u -> setTroopPosition(Vector3<float>(Enumeration::HumanCityHall::human_x, terrain -> getY(Enumeration::HumanCityHall::human_x, Enumeration::HumanCityHall::human_z), Enumeration::HumanCityHall::human_z)); //ToDo

    //selectedTroop -> setTroopDestination(g -> getGameState() -> getTerrain() -> getPointCollision(g -> getMouse()));
    //Game::Instance() -> getSoundSystem() -> playVoice(selectedTroop -> getMoveEvent());
    //selectedTroop -> setTroopDestination(g -> getGameState() -> getTerrain() -> getPointCollision(g -> getMouse()));
}
*/