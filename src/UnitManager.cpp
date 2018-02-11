#include "UnitManager.h"
#include "Game.h"
#include "IA.h"
#include "Human.h"
//Constructor
UnitManager::UnitManager(Enumeration::Team t, Enumeration::BreedType b) {
    gridAlignment = 20;
    selectedTroop = 0; 
    nextTroopId = 1;

    //Addes by Julian
    team = t;
    breed = b;

    unitLayer = new SceneNode();

    inQueueTroops = new std::map<i32, Unit*>();
    inHallTroops = new std::map<i32, Unit*>();
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
    for (std::map<i32, Unit*>::iterator it = inQueueTroops -> begin(); it != inQueueTroops -> end(); ++it){
        delete it->second;
    }
    inQueueTroops -> clear();
    delete inQueueTroops;

    for (std::map<i32, Unit*>::iterator it = inHallTroops -> begin(); it != inHallTroops -> end(); ++it){
        delete it->second;
    }
    inHallTroops -> clear();
    delete inHallTroops;

    for (std::map<i32, Unit*>::iterator it = inMapTroops -> begin(); it != inMapTroops -> end(); ++it) {
		delete it -> second;
    }
    inMapTroops -> clear();
    delete inMapTroops;

    delete unitLayer;
    if (selectedTroop != NULL) delete selectedTroop;
}

//Create a new troops
//In order to add a new unit, you must specify which one
bool UnitManager::createTroop(Enumeration::UnitType type) {
    if (checkCanPay(type)) {
        Unit *newUnit = new Unit(unitLayer, nextTroopId, team, breed, type);
        if (newUnit == NULL) {
            return false;
        }
        newUnit -> setID(nextTroopId);
        // Distinto tamaño para distintas unidades?
        newUnit -> getModel() -> setScale(Vector3<f32>(25,25,25));
        newUnit -> getModel() -> setActive(false);
        newUnit -> setRecruitedCallback([&] (Unit* u){
            std::cout << "Se ha terminado de reclutar la unidad " << u->getID() << std::endl;
            //Delete in Queue
            inQueueTroops->erase(inQueueTroops->find(u->getID()));

            //Add in Hall
            inHallTroops->insert(std::pair<i32, Unit*>(u->getID(), u));

            //Añadir al HUD
            if (team == Enumeration::Team::Human){
                Game::Instance()->getGameState()->getHud()->removeTroopFromQueue(u->getID());
                Game::Instance()->getGameState()->getHud()->addTroopToHall(u->getID(), u->getType());

                //Mostrar texto de reclutamiento
                Game::Instance() -> getEventManager() -> triggerEvent(Enumeration::EventType::showRecruitedText);  
            }
        });
        newUnit -> setRetractedCallback([&] (Unit *u){
            std::cout << "Se ha terminado de guardar la unidad " << u->getID() << std::endl;
            //Add in Hall
            inHallTroops->insert(std::pair<i32, Unit*>(u->getID(), u));
            //Delete in Map
            u -> getModel() -> setActive(false);
            inMapTroops->erase(inMapTroops->find(u->getID()));


            //Añadir al HUD
            if (team == Enumeration::Team::Human){
                Game::Instance()->getGameState()->getHud()->addTroopToHall(u->getID(), u->getType());
            }
        });

        std::cout << "Se ha empezado a reclutar la unidad " << newUnit->getID() << std::endl;
        inQueueTroops -> insert(std::pair<i32, Unit*>(newUnit->getID(), newUnit));
        if (team == Enumeration::Team::Human){
            Game::Instance()->getGameState()->getHud()->addTroopToQueue(newUnit->getID(), newUnit->getType());
        }

        troopsAmount[type]++;
        nextTroopId++;
        return true;
    }
    return false;
}

//Update all troops
void UnitManager::updateUnitManager() {
    // Retractear una sola unidad
    if (selectedTroop != NULL) {
        if (Game::Instance() -> getKeyboard() -> keyPressed(82)) { //82 = R, R de retracted
            if (team == Enumeration::Team::Human){
                selectedTroop -> setTroopDestination(Human::Instance()->getHallPosition());
            }
            selectedTroop -> switchState(Enumeration::UnitState::Retract);
        }
    }
    int i = 0;
    for (std::map<i32,Unit*>::iterator it = inQueueTroops -> begin(); it != inQueueTroops -> end() && i < inQueueTroops->size(); ++it) {
        if (it -> second != NULL) {
            it -> second -> update();
        }
        i++;
    }
    i = 0;
    for (std::map<i32,Unit*>::iterator it = inHallTroops -> begin(); it != inHallTroops -> end() && i < inHallTroops->size(); ++it) {
        if (it -> second != NULL) {
            it -> second -> update();
        }
        i++;
    }
    i = 0;
    for (std::map<i32,Unit*>::iterator it = inMapTroops -> begin(); it != inMapTroops -> end() && i < inMapTroops->size(); ++it) {
        if (it -> second != NULL) {
            it -> second -> update();
        }
        i++;
    }
}

void UnitManager::testRaycastCollisions() {
	if (!deployingTroop) {
		currentCollision = unitLayer -> getNodeCollision(Game::Instance() -> getMouse());
	}
} 

void UnitManager::startDeployingTroop(i32 troopID) {
    if (!deployingTroop) {
        deployingTroop = true;
        currentDeployingTroop = troopID;
    }
}

void UnitManager::startDeployingAllTroops() {
    if (!deployingTroop) {
        deployingTroop = true;
        currentDeployingTroop = 0;
    }
} 

void UnitManager::deploySelectedTroop(Vector3<f32> p) {
    if (deployingTroop && currentDeployingTroop >= 0) { 
        Unit *temp = inHallTroops -> find(currentDeployingTroop) -> second;

        //Delete in hall
        inHallTroops->erase(temp->getID());

        //Insert in map
        inMapTroops -> insert(std::pair<i32, Unit*>(temp -> getModel() -> getID(), temp));

        temp -> switchState(Enumeration::UnitState::AttackMove); // ToDo: why attack move?
        if (team == Enumeration::Team::IA){
            temp -> setTroopPosition(IA::Instance()->getHallPosition());
        } else {
            temp -> setTroopPosition(Human::Instance()->getHallPosition());
        }
        temp -> setPathToTarget(p);
        temp -> getModel() -> setActive(true);

        if (team == Enumeration::Team::Human){
            Game::Instance()->getGameState()->getHud()->removeTroopFromHall(temp->getID());
        }
        std::cout << "Se ha terminado de deployear la unidad " << temp->getID() << std::endl;

        currentDeployingTroop = -1;
        deployingTroop = false;
    }
}

void UnitManager::deployAllTroops(Vector3<f32> p){
    for (std::map<i32,Unit*>::iterator it = inHallTroops -> begin(); it != inHallTroops -> end(); ++it) {
        Unit *temp = it -> second;

        //Insert in map
        inMapTroops -> insert(std::pair<i32, Unit*>(temp -> getModel() -> getID(), temp));

        temp -> switchState(Enumeration::UnitState::AttackMove); // ToDo: why attack move?
        if (team == Enumeration::Team::IA){
            temp -> setTroopPosition(IA::Instance()->getHallPosition());
        } else {
            temp -> setTroopPosition(Human::Instance()->getHallPosition());
        }
        temp -> setPathToTarget(p);
        temp -> getModel() -> setActive(true);
        
        if (team == Enumeration::Team::Human){
            Game::Instance()->getGameState()->getHud()->removeTroopFromHall(temp->getID());
        }
        std::cout << "Se ha terminado de deployear la unidad " << temp->getID() << std::endl;
    }
    
    //Delete in hall
    inHallTroops->clear();
    
    currentDeployingTroop = -1;
    deployingTroop = false;
}

void UnitManager::retractAllTroops() {
    for (std::map<i32,Unit*>::iterator it = inMapTroops -> begin(); it != inMapTroops -> end(); ++it) {
        Unit *temp = it -> second;
        if (team == Enumeration::Team::IA){
            temp -> setTroopDestination(IA::Instance()->getHallPosition());
        } else {
            temp -> setTroopDestination(Human::Instance()->getHallPosition());
        }
        temp -> switchState(Enumeration::UnitState::Retract);
    }
}

//Select a troop
void UnitManager::selectTroop(i32 troopID) {
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
    if (deployingTroop){
        return currentDeployingTroop;
    } else {
        return -1;
    }
}

std::map<i32, Unit*> *UnitManager::getInQueueTroops() {
    return inQueueTroops;
}

std::map<i32, Unit*> *UnitManager::getInHallTroops() {
    return inHallTroops;
}

std::map<i32, Unit*> *UnitManager::getInMapTroops() {
    return inMapTroops;
}

Unit* UnitManager::getSelectedTroop() {
    return selectedTroop;
}

i32 UnitManager::getTroopAmount(Enumeration::UnitType t){
    return troopsAmount[(i32)t];
}

bool UnitManager::areTroopsDeployed(){
    return (inHallTroops->size() == 0);
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
        //VERSION DEFINITIVA, LO DE DEBAJO ES DE JULIAN DE DEBUGERUNIS
        //Unit *newUnit = new Unit(unitLayer, std::rand(), L"media/buildingModels/dummy.obj", team, breed, unitData, Vector3<f32>());
        //newUnit -> getModel() -> setScale(Vector3<f32>(128, 128, 128));
*/
