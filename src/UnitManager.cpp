#include "UnitManager.h"
#include "Game.h"
#include <WorldEngine/WorldGeometry.h>
#include <WorldEngine/Cell.h>

#include "Human.h"
#include "IA.h"
#include "Map.h"
#include "Hud.h"
#include "IOEngine/IO.h"
#include <OBDEngine/ResourceManager/ResourceJSON.h>
#include "EntityData.h"

//ToDo: revisar esta clase

//Constructor
UnitManager::UnitManager(Enumeration::Team t, std::string b) {
    IO::Instance() -> getResourceManager()->loadResource("media/gameConfig/UnitData/"+b+"Units.json");
    ResourceJSON *r = (ResourceJSON*)IO::Instance() -> getResourceManager() -> getResource("media/gameConfig/UnitData/"+b+"Units.json");
    json j = *r -> getJSON();

    baseUnits = new std::map<std::string, UnitData>();
    inQueueTroopsByBuilding = new std::map<std::string, i32>();

    for (auto& element : j["Units"]){
        UnitData tmp;
            tmp.type = element["unitName"].get<std::string>();
            tmp.buildingType = element["buildingType"].get<std::string>();
            tmp.troopModel = element["troopPath"]["modelPath"].get<std::string>();
            tmp.troopTexture = element["troopPath"]["texturePath"].get<std::string>();
            tmp.flagModel = element["flagPath"]["modelPath"].get<std::string>();
            tmp.flagTexture = element["flagPath"]["texturePath"].get<std::string>();
            tmp.metalCost = element["metalCost"].get<i32>();
            tmp.crystalCost = element["crystalCost"].get<i32>();
            tmp.maxHP = element["maxHP"].get<i32>();
            tmp.viewRadius = element["viewRadius"].get<i32>();
            tmp.attackRange = element["attackRange"].get<i32>();
            tmp.attackDamage = element["attackDamage"].get<i32>();
            tmp.attackSpeed = element["attackSpeed"].get<i32>();
            tmp.happinessVariation = element["happiness"].get<i32>();
            tmp.citizensVariation = element["citizens"].get<i32>();
            tmp.recruitingTime = element["recruitingTime"].get<i32>();
            tmp.armyLevel = element["armyLevel"].get<i32>();
            tmp.moveSpeed = element["moveSpeed"].get<i32>();
            tmp.troops = element["troops"].get<i32>();
            tmp.cellsX = element["cellsX"].get<i32>();
            tmp.cellsY = element["cellsY"].get<i32>();
            tmp.bbOffset = element["bbOffset"].get<f32>();
            tmp.attackEvent = element["attackEvent"].get<std::string>();
            tmp.moveEvent = element["moveEvent"].get<std::string>();
            tmp.selectEvent = element["selectEvent"].get<std::string>();
        baseUnits->insert(std::pair<std::string, UnitData>(tmp.type, tmp));
		inQueueTroopsByBuilding->insert(std::pair<std::string, i32>(tmp.buildingType, 0));
    }
    
    selectedTroop = 0; 
    nextTroopId = 1;
    totalUnitFighters = 0;
    team = t;

    unitLayer = new SceneNode();

    inQueueTroops = new std::map<i32, Unit*>();
    inHallTroops = new std::map<i32, Unit*>();
    inMapTroops = new std::map<i32, Unit*>();

	currentCollisionID = -1;

    deployingTroop = false;
    currentDeployingTroop = -1;

    selectedTroop = nullptr;
}

//Destroyer
UnitManager::~UnitManager() {
    for (std::map<i32, Unit*>::iterator it = inQueueTroops -> begin(); it != inQueueTroops -> end(); ++it){
        delete it -> second;
    }
    inQueueTroops -> clear();
    delete inQueueTroops;

    for (std::map<i32, Unit*>::iterator it = inHallTroops -> begin(); it != inHallTroops -> end(); ++it){
        delete it -> second;
    }
    inHallTroops -> clear();
    delete inHallTroops;

    for (std::map<i32, Unit*>::iterator it = inMapTroops -> begin(); it != inMapTroops -> end(); ++it) {
		delete it -> second;
    }
    inMapTroops -> clear();
    delete inMapTroops;

    delete unitLayer;
}
//Create a new troops
//In order to add a new unit, you must specify which one
bool UnitManager::createTroop(std::string type) {
	//ToDo: This method is just so fucking weird, I just can't get it
    std::map<std::string, UnitData>::iterator it = baseUnits->find(type);
    if (it != baseUnits->end()){
		//Check if there are space in the queue
        if (team == Enumeration::Team::Human){
			if (inQueueTroopsByBuilding->at(it->second.buildingType) >= Human::Instance()->getBuildingManager()->getAmount(it->second.buildingType)) return false;
		} else {
			if (inQueueTroopsByBuilding->at(it->second.buildingType) >= IA::Instance()->getBuildingManager()->getAmount(it->second.buildingType)) return false;
		}
		//Check if can pay it
        if (checkCanPay(type)) {
            Unit *newUnit = new Unit(unitLayer, nextTroopId, team, it->second, this);
            if (newUnit == nullptr) {
                return false;
            }
            newUnit -> getModel() -> setActive(false);
			adjustUnitFighter(it->second.troops);
            newUnit -> setRecruitedCallback([&] (Unit* u){
                //Delete in Queue
                inQueueTroops->erase(inQueueTroops->find(u->getID()));

				//Remove from queue size
				inQueueTroopsByBuilding->at(u->getBuildingName())--;

                //Add in Hall
                inHallTroops->insert(std::pair<i32, Unit*>(u->getID(), u));

                //Añadir al HUD
                if (team == Enumeration::Team::Human){
                    Hud::Instance()->removeTroopFromQueue(u->getID());
                    Hud::Instance()->addTroopToHall(u->getID(), u->getType());

                    //Mostrar texto de reclutamiento
                    IO::Instance() -> getEventManager() -> triggerEvent(Enumeration::EventType::showRecruitedText);  
                }
            });
            newUnit -> setRetractedCallback([&] (Unit *u){
                //Add in Hall
                inHallTroops->insert(std::pair<i32, Unit*>(u->getID(), u));
                //Delete in Map
                u -> getModel() -> setActive(false);
                inMapTroops->erase(inMapTroops->find(u->getID()));


                //Añadir al HUD
                if (team == Enumeration::Team::Human){
                    Hud::Instance()->addTroopToHall(u->getID(), u->getType());
                }
            });

			//Tax player
			newUnit->preTaxPlayer();

			//Add to queues
            inQueueTroops -> insert(std::pair<i32, Unit*>(newUnit->getID(), newUnit));
			inQueueTroopsByBuilding->at(it->second.buildingType)++;
            if (team == Enumeration::Team::Human){
                Hud::Instance()->addTroopToQueue(newUnit->getID(), newUnit->getType());
            }

            troopsAmount[type]++;
            nextTroopId++;
            return true;
        }
    } else {
        std::cout << "No existe ese tipo de tropa" << std::endl;
        exit(0);
    }
    return false;
}

//Update all troops
void UnitManager::updateUnitManager() {
    // Retractear una sola unidad
    if (selectedTroop != nullptr) {
        if (IO::Instance() -> getKeyboard() -> keyPressed(82)) { //ToDo: fachada -- 82 = R, R de retracted
            if (team == Enumeration::Team::Human){
				Vector3<f32> p = Human::Instance()->hallPosition;
                selectedTroop -> setUnitDestination(Vector2<f32>(p.x, p.z));
            }
            selectedTroop -> switchState(Enumeration::UnitState::Retract);
        }
    }
    i32 i = 0;
    for (std::map<i32,Unit*>::iterator it = inQueueTroops -> begin(); it != inQueueTroops -> end() && i < inQueueTroops->size(); ++it) {
        if (it -> second != nullptr) {
            it -> second -> update();
        }
        i++;
    }
    i = 0;
    for (std::map<i32,Unit*>::iterator it = inHallTroops -> begin(); it != inHallTroops -> end() && i < inHallTroops->size(); ++it) {
        if (it -> second != nullptr) {
            it -> second -> update();
        }
        i++;
    }
    i = 0;
    for (std::map<i32,Unit*>::iterator it = inMapTroops -> begin(); it != inMapTroops -> end() && i < inMapTroops->size(); ++it) {
        if (it -> second != nullptr) {
            it -> second -> update();
        }
        i++;
    }
}

void UnitManager::testRaycastCollisions() {
	if (!deployingTroop) {
		currentCollisionID = unitLayer -> getNodeCollision(IO::Instance() -> getMouse()->getPosition());
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
//ToDo: Check this method -> Optimize, also change deployAllTroops
void UnitManager::deploySelectedTroop(Vector2<f32> p) {
    if (deployingTroop && currentDeployingTroop >= 0) { 
        Unit *temp = inHallTroops -> find(currentDeployingTroop) -> second;
        //Delete in hall
        inHallTroops->erase(temp->getID());
        //Insert in map
        inMapTroops -> insert(std::pair<i32, Unit*>(temp -> getModel() -> getID(), temp));
        Cell* target;
        Vector3<f32> hallPosition(0, 0, 0);

        if (team == Enumeration::Team::IA){
            hallPosition = IA::Instance()->hallPosition;
			target = WorldGeometry::Instance()->positionToCell(hallPosition.toVector2());
        } else {
            hallPosition = Human::Instance()->hallPosition;
            target = WorldGeometry::Instance()->positionToCell(hallPosition.toVector2());
        }
        target = WorldGeometry::Instance()->getValidCell(hallPosition.toVector2(), p, temp->getHitbox());
        Vector2<f32> dummy = target->getPosition();
        temp -> setUnitPosition(dummy);
        temp -> setUnitCell(dummy);
        temp -> getModel() -> setActive(true);
        temp -> setPathToTarget(p);
        temp -> switchState(Enumeration::UnitState::Move);
        if (team == Enumeration::Team::Human){
            Hud::Instance()->removeTroopFromHall(temp->getID());
        }

        currentDeployingTroop = -1;
        deployingTroop = false;
    }
}

/* Probably add the new deploy system used above */
void UnitManager::deployAllTroops(Vector2<f32> p){
    for (std::map<i32,Unit*>::iterator it = inHallTroops -> begin(); it != inHallTroops -> end(); ++it) {
        Unit *temp = it -> second;

        //Insert in map
        inMapTroops -> insert(std::pair<i32, Unit*>(temp -> getModel() -> getID(), temp));

        Cell* target;
        Vector3<f32> hallPosition(0, 0, 0);
        if (team == Enumeration::Team::IA){
			hallPosition = IA::Instance()->hallPosition;
            target = WorldGeometry::Instance()->positionToCell(hallPosition.toVector2());
        } else {
			hallPosition = Human::Instance()->hallPosition;
            target = WorldGeometry::Instance()->positionToCell(hallPosition.toVector2());
        }
        //ToDo: Check this, can return a nullptr
        target = WorldGeometry::Instance()->getValidCell(hallPosition.toVector2(), p, temp->getHitbox());
        
        Vector2<f32> dummy;
        dummy = target->getPosition();
        temp -> setUnitPosition(dummy);
        temp -> setUnitCell(dummy);
        temp -> getModel() -> setActive(true);
        temp -> setPathToTarget(p);
        temp -> switchState(Enumeration::UnitState::Move); 
        if (team == Enumeration::Team::Human){
            Hud::Instance()->removeTroopFromHall(temp->getID());
        }
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
			Vector3<f32> p = IA::Instance()->hallPosition;
            temp -> setPathToTarget(Vector2<f32>(p.x, p.z));
        } else {
			Vector3<f32> p = Human::Instance()->hallPosition;
            temp -> setPathToTarget(Vector2<f32>(p.x, p.z));
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
    if (selectedTroop != nullptr){
        selectedTroop = nullptr;
        IO::Instance() -> getMouse() -> changeIcon(CURSOR_NORMAL);
    }
}

//Pass the order to the selected unit
void UnitManager::moveOrder() {
    if (selectedTroop != nullptr) {
        if (IO::Instance() -> getKeyboard() -> keyPressed(GLFW_KEY_A)) { //ToDo: fachada
            selectedTroop->switchState(Enumeration::UnitState::AttackMove);

            selectedTroop->setPathToTarget(Map::Instance() -> getTerrain() -> getPointCollision(IO::Instance() -> getMouse()->getPosition()).toVector2());
        } else {
            selectedTroop->switchState(Enumeration::UnitState::Move);

            selectedTroop->setPathToTarget(Map::Instance() -> getTerrain() -> getPointCollision(IO::Instance() -> getMouse()->getPosition()).toVector2());
        }
        //MOVEMENT VOICE
        //SoundSystem::Instance() -> playVoiceEvent(selectedTroop -> getMoveEvent());
    }
}

/**
 * This method is responsible for managing calls to isSolvent() for the human, registering the type
 * of the desired building and sending the aforementhioned method the prices. It has its own method
 * to avoid cluttering the setBuildingMode() method, as it used to be there in the first place.
 */
bool UnitManager::checkCanPay(std::string type) {
	std::map<std::string,UnitData>::iterator it = baseUnits->find(type);
	if (it != baseUnits->end()){
		if (team == Enumeration::Team::Human)
			return Human::Instance() -> isSolvent(it->second.metalCost, it->second.crystalCost, it->second.citizensVariation);
		else
			return IA::Instance() -> isSolvent(it->second.metalCost, it->second.crystalCost, it->second.citizensVariation);
	}
	return false;
}

bool UnitManager::isTroopSelected() {
    if (selectedTroop != nullptr) return true;
    else return false;
}

bool UnitManager::isDeployingTroop(){
    return deployingTroop;
}

void UnitManager::deleteUnit(i32 id) {
    std::map<i32, Unit*>::iterator it = inMapTroops->find(id);
    if (it != inMapTroops->end()){
        if (team == Enumeration::Team::Human) {
            Human::Instance() -> modifyArmyLevel(-it -> second -> getArmyLevel());
        } else {
            IA::Instance() -> modifyArmyLevel(-it -> second -> getArmyLevel());
        }
        if(selectedTroop == it->second){
            selectedTroop = nullptr;
        }
        delete it -> second;
        inMapTroops -> erase(id);
    }
}

i32 UnitManager::getCollisionID() {
	return currentCollisionID;
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

i32 UnitManager::getTroopAmount(std::string t){
    return troopsAmount[t];
}

bool UnitManager::areTroopsDeployed(){
    return (inHallTroops -> size() == 0);
}

bool UnitManager::areTroopsInMap(){
    return (inMapTroops -> size() != 0);
}

//Returns the amount of troops
i32 UnitManager::getTotalTroopAmount() {
    return inQueueTroops -> size() + inHallTroops -> size() + inMapTroops -> size();
} 

const UnitData& UnitManager::getUnitData(std::string type) const{
	std::map<std::string, UnitData>::const_iterator it = baseUnits->find(type);
	/*if (it != baseUnits->end()){
		//return &it->second;
	}*/ if (it == baseUnits->end()){
		std::cout << "El tipo de unidad " << type << " no es valido." << std::endl;
		exit(0);
		//return &it->second;
	}
    return it->second;
}

Unit* UnitManager::getUnit(i32 _id){
    std::map<i32, Unit*>::iterator it = inMapTroops->find(_id);
    if (it != inMapTroops->end()){
        return it->second;
    }
    else{
        return nullptr;
    }
}

void UnitManager::adjustUnitFighter(i32 qnty){
    totalUnitFighters += qnty;
}

i32 UnitManager::getUnitFighters(){
	return totalUnitFighters;
}