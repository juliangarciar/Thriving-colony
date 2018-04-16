#include "BuildingManager.h"
#include "Game.h"
#include <WorldEngine/WorldGeometry.h>
#include <GraphicEngine/Window.h>
#include <OBDEngine/ResourceManager/ResourceJSON.h>

BuildingManager::BuildingManager(Enumeration::Team t, std::string b) {
	team = t;

	nextBuildingId = 0;
    gridAlignment = -100;
    buildingMode = false;

	buildingLayer = new SceneNode();
	currentCollision = nullptr;
	inMapBuildings = new std::map<i32, Building*>();
	tempBuilding = nullptr;

    IO::Instance() -> getResourceManager()->loadResource("media/map/"+b+".json");
    ResourceJSON *r = (ResourceJSON*)IO::Instance() -> getResourceManager() -> getResource("media/map/"+b+".json");
    json j = *r -> getJSON();

    for (auto& element : j["buildings"]){
		BuildingData d;
		//ToDo: rellenar buildingData
		buildings.insert(std::pair<std::string, BuildingData>(element["type"].get<std::string>(), d));
	}
}

BuildingManager::~BuildingManager() {
	delete tempBuilding;
	delete buildingLayer;
	for (std::map<i32,Building*>::iterator it = inMapBuildings -> begin(); it != inMapBuildings -> end(); ++it) {
		delete it -> second;
    }
	inMapBuildings -> clear();
	delete inMapBuildings;
}

void BuildingManager::testRaycastCollisions() {
	if (!buildingMode) {
		currentCollision = buildingLayer -> getNodeCollision(IO::Instance() -> getMouse());
	}
}

bool BuildingManager::setBuildingMode(std::string type) {
	if (buildings.find(type) != buildings.end() && checkCanPay(type)) {
		if (!buildingMode) {
			buildingMode = true;
			tempBuilding = new Building(buildingLayer, 0, team, buildings[type]);
			recalculateHitbox();
			return true;
		}
	}
	return false;
}

/* ToDo: optimize, to much shit inside */
void BuildingManager::drawBuilding() {
    if (buildingMode && tempBuilding != nullptr) {
		//Get position where the cursor is pointing to the terrain
        Vector2<f32> collisionPoint = Map::Instance() -> getTerrain() -> getPointCollision(IO::Instance() -> getMouse()).toVector2();
		// Change 2nd parameter
		bool collision = false;
		Vector2<f32> dummy = WorldGeometry::Instance()->correctBuildingPosition(collisionPoint, tempBuilding);

		tempBuilding -> setPosition(dummy);

		if(team == Enumeration::Team::Human){
			Vector2<f32> tmp = Human::Instance()->getHallPosition();
			f32 distance = std::sqrt(std::pow(tmp.x - dummy.x, 2) + std::pow(tmp.y - dummy.y, 2));
			if(Human::Instance()->getBuildingRadious() < distance){
				collision = true;
			}
			else{
				collision = WorldGeometry::Instance()->checkBuildingSpace(tempBuilding);
			}
		}

		//Pressing the right mouse button cancels the building
		if (IO::Instance() -> getMouse() -> rightMouseDown()){
			buildingMode = false;
			delete tempBuilding;		
			tempBuilding = nullptr;
			return;
		}
		
		if (collision) {
			//ToDo: material no se puede construir aqui
		} else {
			//ToDo: volver al material original
			//If there is no collision and the player press left button of the mouse, build the building
			if (IO::Instance() -> getMouse() -> leftMouseDown()) {
				buildingMode = false;
				buildBuilding(dummy);
			}
		}
    }
}

void BuildingManager::createBuilding(Vector2<f32> pos, std::string type, i32 buildTime){
	if (buildings.find(type) != buildings.end()){
		BuildingData b = buildings[type];
		if (buildTime >= 0) b.buildTime = buildTime;
		tempBuilding = new Building(buildingLayer, 0, team, b);
		buildBuilding(pos);
	}
}

void BuildingManager::buildBuilding(Vector2<f32> pos) {
	if (tempBuilding != nullptr){
		//Establece la posicion inicial del edificio
		tempBuilding -> setPosition(pos);
		//Establece la ID inicial del edificio
		tempBuilding -> setID(nextBuildingId);
		//Establece un callback que se ejecutará al acabar de construir
		tempBuilding -> setFinishedCallback([&](Building *b){
			buildingAmounts[b -> getType()]++;
			
			if (team == Enumeration::Team::Human){
				if (buildingAmounts[b -> getType()] == 1 
					&& (b -> getType() == "Barrack" || b -> getType() == "Barn" || b -> getType() == "Workshop")) {
					Hud::Instance() -> enableTab(b -> getType());
				}
				IO::Instance() -> getEventManager() -> triggerEvent(Enumeration::EventType::showBuiltText);  
			}
		});

		//Insert building in a map
		inMapBuildings -> insert(std::pair<i32,Building*>(nextBuildingId, tempBuilding));
		
		//Start the construction of the building
		tempBuilding -> startBuilding();
		
		//
		WorldGeometry::Instance() -> build(tempBuilding);

		//
		tempBuilding = nullptr;
		nextBuildingId++;
	} else {
		std::cout << "Error, se ha intentado construir un edificio inexistente" << std::endl;
		exit(0);
	}
}

//Checks if the player, either the human or the AI can afford to build a specific building 
bool BuildingManager::isSolvent(i32 metalCost, i32 crystalCost) {
	i32 metalAmt = 0;
	i32 crystalAmt = 0;
	if (team == Enumeration::Team::Human) {
		metalAmt = Human::Instance() -> getMetalAmount();
		crystalAmt = Human::Instance() -> getCrystalAmount();
	} else {
		metalAmt = IA::Instance() -> getMetalAmount();
		crystalAmt = IA::Instance() -> getCrystalAmount();
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
bool BuildingManager::checkCanPay(std::string type) {
	if (buildings.find(type) != buildings.end()){
		return isSolvent(buildings[type].metalCost, buildings[type].crystalCost);
	}
	return false;
}

void BuildingManager::recalculateHitbox(){
	for (std::map<i32,Building*>::iterator it = inMapBuildings -> begin(); it != inMapBuildings -> end(); ++it) {
		it -> second -> refreshHitbox();
	}
}

void BuildingManager::updateBuildingManager() {
	for (std::map<i32,Building*>::iterator it = inMapBuildings -> begin(); it != inMapBuildings -> end(); ++it) {
		it -> second -> update();
	}
}

bool BuildingManager::checkFinished(i32 _id) {	
	return (inMapBuildings -> find(_id) -> second -> getFinished());	
}

i32 BuildingManager::getAmount(std::string type){
	if (buildings.find(type) != buildings.end()){
		return buildingAmounts[type];
	} 
	return 0;
}

i32 BuildingManager::getCollisionID() {
	if (currentCollision != nullptr && currentCollision -> getSceneNode() != nullptr) {
		return currentCollision -> getSceneNode() -> getID();
	}
	return -1;
}

std::string BuildingManager::getCollisionName() {
	if (currentCollision != nullptr && currentCollision -> getSceneNode() != nullptr) {
		return currentCollision -> getSceneNode() -> getName();
	}
	return nullptr;
}

std::map<i32, Building*>* BuildingManager::getBuildings() {
	return inMapBuildings;
}

SceneNode* BuildingManager::getBuildingLayer() {
	return buildingLayer;
}

void BuildingManager::deleteBuilding(i32 id) {
	if (inMapBuildings -> find(id) -> second -> getTeam() == Enumeration::Team::Human) {
		Human::Instance() -> decreaseHappiness(inMapBuildings -> find(id) -> second -> getHappinessVariation());
	} else {
		IA::Instance() -> decreaseHappiness(inMapBuildings -> find(id) -> second -> getHappinessVariation());
	}
	buildingAmounts[inMapBuildings -> find(id) -> second -> getType()]--;
	delete inMapBuildings -> find(id) -> second;
	inMapBuildings -> erase(id);
} 

Building *BuildingManager::getBuilding(i32 id){
  	std::map<i32,Building*>::iterator it;
	it = inMapBuildings->find(id);
  	if (it != inMapBuildings->end())
		return it->second;
	else 
		return nullptr;
}
