#include "UnitManager.h"
#include "Game.h"
#include "IA.h"
#include "Human.h"
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
    inMapTroops = new std::map<i32, Unit*>();

    deployingTroop = false;
    currentDeployingTroop = -1;

    selectedTroop = NULL;

	for (i32 i = 0; i < Enumeration::UnitType::TroopsSize; i++){
		troopsAmount[i] = 0;
	}
}

//Destroyer
UnitManager::~UnitManager() {
    delete selectedTroop;

    for (i32 i = 0; i < inQueueTroops -> size(); i++) {
        inQueueTroops -> erase(inQueueTroops -> begin() + i);
    }
    inQueueTroops -> clear();
    delete inQueueTroops;

    for (i32 i = 0; i < inHallTroops -> size(); i++) {
        inHallTroops -> erase(inHallTroops -> begin() + i);
    }
    inHallTroops -> clear();
    delete inHallTroops;

    for (std::map<i32,Unit*>::iterator it = inMapTroops -> begin(); it != inMapTroops -> end(); ++it) {
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
        Unit *newUnit = setNewUnitModel(unitData);
        if (newUnit == NULL) {
            return false;
        }
        // Distinto tamaño para distintas unidades?
        newUnit -> getModel() -> setScale(Vector3<float>(25,25,25)); //VERSION DEFINITIVA, LO DE DEBAJO ES DE JULIAN DE DEBUGERUNIS
        //Unit *newUnit = new Unit(unitLayer, std::rand(), L"media/buildingModels/dummy.obj", team, breed, unitData, Vector3<float>());
        newUnit -> getModel() -> setActive(false);
        //newUnit -> getModel() -> setScale(Vector3<f32>(128, 128, 128));
        newUnit -> setRecruitedCallback([&] (Unit* u){
            std::cout << "Se ha terminado de reclutar la unidad " << u->getID() << std::endl;
            //Delete in Queue
            ptrdiff_t pos = distance(inQueueTroops->begin(), find(inQueueTroops->begin(), inQueueTroops->end(), u));
            inQueueTroops->erase(inQueueTroops->begin()+pos);

            //Add in Hall
            inHallTroops->push_back(u);
            
            //ToDo: modificar el HUD
        });
        newUnit -> setRetractedCallback([&] (Unit *u){
            std::cout << "Se ha terminado de guardar la unidad " << u->getID() << std::endl;
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
    for (i32 i=0; i < inQueueTroops->size(); i++){
        inQueueTroops->at(i)->update();
    }
    /*for (i32 i=0; i < inHallTroops->size(); i++){
        inHallTroops->at(i);
    }*/
    for (std::map<i32,Unit*>::iterator it = inMapTroops -> begin(); it != inMapTroops -> end(); ++it) {
        it -> second -> update();
    }
}

void UnitManager::testRaycastCollisions() {
	if (!deployingTroop) {
		currentCollision = unitLayer -> getNodeCollision(Game::Instance() -> getMouse());
	}
} 

void UnitManager::startDeployingTroop(i32 index) {
    if (!deployingTroop) {
        deployingTroop = true;
        currentDeployingTroop = index;
        selectedTroop = inHallTroops -> at(currentDeployingTroop);
    }
} 

void UnitManager::deployTroop(Vector3<f32> p) { 
    Game *g = Game::Instance();
    if (deployingTroop && currentDeployingTroop >= 0) { 
        Unit *temp = inHallTroops -> at(currentDeployingTroop);

        //Delete in Queue
        ptrdiff_t pos = distance(inHallTroops->begin(), find(inHallTroops->begin(), inHallTroops->end(), temp));
        inHallTroops->erase(inHallTroops->begin()+pos);

        //Insert in map
        inMapTroops -> insert(std::pair<i32, Unit*>(temp -> getModel() -> getID(), temp));

        temp -> setTroopPosition(p); //ToDo: select where deploy
        temp -> switchState(Enumeration::UnitState::AttackMove); // ToDo: why attack move?
        temp -> setPathToTarget(g -> getGameState() -> getTerrain() -> getPointCollision(g -> getMouse()));
        temp -> getModel() -> setActive(true);
        
        g -> getMouse() -> changeIcon(CURSOR_NORMAL);

        currentDeployingTroop = -1;
        selectedTroop = NULL;
        deployingTroop = false;
    }
}

void UnitManager::retractAllTroops(Vector3<f32> vectorData) {
    for (std::map<i32,Unit*>::iterator it = inMapTroops -> begin(); it != inMapTroops -> end(); ++it) {
        Unit *u = it -> second;
        u -> switchState(Enumeration::UnitState::Retract);
        u -> setTroopDestination(vectorData);
    }
}

//Select a troop
void UnitManager::selectTroop(i32 troopID) { 
    Game *g = Game::Instance();
    std::map<i32,Unit*>::iterator it = inMapTroops -> find(troopID);
    if (it != inMapTroops -> end()) {
        selectedTroop = it -> second;
        //SELECT VOICE
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

void UnitManager::startBattle(i32 enemyID) {
    //ToDo: crear batalla
}

// Checks if the player, either the human or the AI can afford to build a specific building 
// ToDo: ESTE METODO Y EL DE DEBAJO ESTAN REPETIDO AQUI Y EN BUILDING MANAGER IGUAL
// DEBERIAN HEREDAR DE UNA CLASE MANAGER QUE TUVIESE AQUELLAS COSAS QUE FUESEN IGUALES
bool UnitManager::isSolvent(i32 metalCost, i32 crystalCost) {
    i32 metalAmt = 0;
    i32 crystalAmt = 0;
    i32 citizensAmt = 0;
    if (team == Enumeration::Team::Human) {
        metalAmt = Human::Instance() -> getMetalAmount();
        crystalAmt = Human::Instance() -> getCrystalAmount();
        citizensAmt = Human::Instance() -> getCitizens();
    } else {
        metalAmt = IA::Instance() -> getMetalAmount();
        crystalAmt = IA::Instance() -> getCrystalAmount();
        citizensAmt = IA::Instance() -> getCitizens();
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

bool UnitManager::isDeployingTroop(){
    return deployingTroop;
}

void UnitManager::deleteUnit(i32 id) {
    delete inMapTroops -> find(id) -> second;
    inMapTroops -> erase(id);
}

i32 UnitManager::getCollisionID() {
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

i32 UnitManager::getDeployingTroopID(){
    if (isDeployingTroop){
        return currentDeployingTroop;
    } else {
        return -1;
    }
}

std::map<i32, Unit*> * UnitManager::getInMapTroops() {
    return inMapTroops;
}

std::vector<Unit*> * UnitManager::getInHallTroops() {
    return inHallTroops;
}

Unit* UnitManager::getSelectedTroop() {
    return selectedTroop;
}

i32 UnitManager::getTroopAmount(Enumeration::UnitType t){
    return troopsAmount[(i32)t];
}

Unit* UnitManager::setNewUnitModel(Enumeration::UnitType unitType) {
    // Hacer que sean razas diferentes?
    switch (unitType) {
        case Enumeration::UnitType::StandardM:
            return new Unit(unitLayer, std::rand(), L"media/unitModels/Soldado_Melee_Drorania.obj", team, breed, unitType, Vector3<float>());
        break;

        case Enumeration::UnitType::StandardR:
            return new Unit(unitLayer, std::rand(), L"media/unitModels/Soldado_Rango_Drorania.obj", team, breed, unitType, Vector3<float>());
        break;

        case Enumeration::UnitType::AdvancedM:
            return new Unit(unitLayer, std::rand(), L"media/unitModels/criatura_drorania.obj", team, breed, unitType, Vector3<float>());
        break;

        case Enumeration::UnitType::AdvancedR:
            return new Unit(unitLayer, std::rand(), L"media/unitModels/criatura_drorania.obj", team, breed, unitType, Vector3<float>());
        break;

        case Enumeration::UnitType::Idol:
            return new Unit(unitLayer, std::rand(), L"media/unitModels/Ente_Drorania.obj", team, breed, unitType, Vector3<float>());
        break;

        case Enumeration::UnitType::Launcher:
            return new Unit(unitLayer, std::rand(), L"media/unitModels/canon_drorania.obj", team, breed, unitType, Vector3<float>());
        break;

        case Enumeration::UnitType::Desintegrator:
            return new Unit(unitLayer, std::rand(), L"media/unitModels/desintegrador_de_Drorania.obj", team, breed, unitType, Vector3<float>());
        break;
        default:
            return NULL;
        break;
    }
}

void UnitManager::enterMainBuilding(Enumeration::UnitType) {
    //ToDo: Crear una tropa nueva, que sea gratis y meterla en el inhalltroops
    std::cout << "entro" << std::endl;
}

//Returns the amount of troops
i32 UnitManager::getTotalTroopAmount() {
    return inQueueTroops -> size() + inHallTroops -> size() + inMapTroops -> size();
} 

/*
void UnitManager::deployTroopAtPosition(i32 index, Vector3<f32> vectorData) {
    Unit *u = inHallTroops -> at(index);
    u -> setPosition(vectorData);
    inMapTroops -> insert(std::pair<i32, Unit*>(u -> getModel() -> getID(), u));
    inHallTroops -> erase(inHallTroops -> begin() + index);

    //temp -> setPosition(Vector3<f32>(8000, 0, 8000));
    //temp -> setTroopDestination(terrain -> getPointCollision(g -> getMouse()));
    //u -> setTroopPosition(Vector3<f32>(Enumeration::HumanCityHall::human_x, terrain -> getY(Enumeration::HumanCityHall::human_x, Enumeration::HumanCityHall::human_z), Enumeration::HumanCityHall::human_z)); //ToDo

    //selectedTroop -> setTroopDestination(g -> getGameState() -> getTerrain() -> getPointCollision(g -> getMouse()));
    //Game::Instance() -> getSoundSystem() -> playVoice(selectedTroop -> getMoveEvent());
    //selectedTroop -> setTroopDestination(g -> getGameState() -> getTerrain() -> getPointCollision(g -> getMouse()));
}
*/
