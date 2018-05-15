#include "BuildingManager.h"
#include "Game.h"
#include <WorldEngine/WorldGeometry.h>
#include <GraphicEngine/Window.h>
#include <OBDEngine/ResourceManager/ResourceJSON.h>

BuildingManager::BuildingManager(Enumeration::Team t, std::string b) {
	team = t;

	nextBuildingId = 0;
    buildingMode = false;

	buildingLayer = new SceneNode();
	currentCollision = nullptr;
	inMapBuildings = new std::map<i32, Building*>();
	tempBuilding = nullptr;

    IO::Instance() -> getResourceManager()->loadResource("media/gameConfig/BuildingData/"+b+"Buildings.json");
    ResourceJSON *r = (ResourceJSON*)IO::Instance() -> getResourceManager() -> getResource("media/gameConfig/BuildingData/"+b+"Buildings.json");
    json j = *r -> getJSON();

    for (auto& element : j["Buildings"]){
		BuildingData tmp;
			tmp.type = element["buildingName"].get<std::string>();
			tmp.modelPath = element["modelPath"].get<std::string>();
			tmp.texturePath = element["texturePath"].get<std::string>();
			tmp.metalCost = element["metalCost"].get<i32>();
			tmp.crystalCost = element["crystalCost"].get<i32>();
			tmp.maxHP = element["maxHP"].get<i32>();
			tmp.viewRadius = element["viewRadius"].get<i32>();
			tmp.attackRange = element["attackRange"].get<i32>();
			tmp.attackDamage = element["attackDamage"].get<i32>();
			tmp.attackSpeed = element["attackSpeed"].get<i32>();
			tmp.happinessVariation = element["happinessVariation"].get<i32>();
			tmp.citizensVariation = element["citizensVariation"].get<i32>();
			tmp.buildingTime = element["buildingTime"].get<f32>();
			tmp.cityLevel = element["cityLevel"].get<i32>();
			tmp.cellsX = element["cellsX"].get<i32>();
			tmp.cellsY = element["cellsY"].get<i32>();
		baseBuildings.insert(std::pair<std::string, BuildingData>(tmp.type, tmp));
	}
}

BuildingManager::~BuildingManager() {
	delete tempBuilding;
	for (std::map<i32,Building*>::iterator it = inMapBuildings -> begin(); it != inMapBuildings -> end(); ++it) {
		delete it -> second;
    }
	delete buildingLayer;
	inMapBuildings -> clear();
	delete inMapBuildings;
}

void BuildingManager::testRaycastCollisions() {
	if (!buildingMode) {
		currentCollision = buildingLayer -> getNodeCollision(IO::Instance() -> getMouse());
	}
}

bool BuildingManager::setBuildingMode(std::string type) {
	std::map<std::string, BuildingData>::iterator it = baseBuildings.find(type);
	if (it != baseBuildings.end() && checkCanPay(type)) {
		if (!buildingMode) {
			buildingMode = true;
			tempBuilding = new Building(buildingLayer, 0, team, it->second);
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
		bool canBuild = true;
		Vector2<f32> dummy = WorldGeometry::Instance()->correctBuildingPosition(collisionPoint, tempBuilding);

		tempBuilding -> setPosition(dummy);

		if(team == Enumeration::Team::Human){
			Vector3<f32> tmp = Human::Instance()->getHallPosition();
			f32 distance = std::sqrt(std::pow(tmp.x - dummy.x, 2) + std::pow(tmp.z - dummy.y, 2));
			if(Human::Instance()->getBuildingRadious() < distance){
				canBuild = false;
			}
			else{
				canBuild = WorldGeometry::Instance()->checkHitBoxCollision(tempBuilding->getHitbox(), true);
			}
		}

		//Pressing the right mouse button cancels the building
		if (IO::Instance() -> getMouse() -> rightMouseDown()){
			buildingMode = false;
			delete tempBuilding;		
			tempBuilding = nullptr;
			return;
		}
		
		if (!canBuild) {
			tempBuilding->setCantBuildMat();
		} else {
			tempBuilding->setCanBuildMat();
			//If there is no collision and the player press left button of the mouse, build the building
			if (IO::Instance() -> getMouse() -> leftMouseDown()) {
				buildingMode = false;
				buildBuilding(dummy);
			}
		}
    }
}

void BuildingManager::createBuilding(Vector2<f32> pos, std::string type, i32 buildTime){
	std::map<std::string, BuildingData>::iterator it = baseBuildings.find(type);
	if (it != baseBuildings.end()){
		BuildingData b = it->second;
		if (buildTime >= 0) b.buildingTime = buildTime;
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
		tempBuilding -> setBaseMaterial(); //ToDo: anadido por rafa
		
		//
		WorldGeometry::Instance() -> build(tempBuilding);

		//Finish everything
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
	std::map<std::string, BuildingData>::iterator it = baseBuildings.find(type);
	if (it != baseBuildings.end()){
		return isSolvent(it->second.metalCost, it->second.crystalCost);
	}
	return false;
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
	std::map<std::string, BuildingData>::iterator it = baseBuildings.find(type);
	if (it != baseBuildings.end()){
		return buildingAmounts[type];
	} 
	return 0;
}

i32 BuildingManager::getCollisionID() {
	if (currentCollision != nullptr) {
		return currentCollision -> getID();
	}
	return -1;
}

std::string BuildingManager::getCollisionName() {
	if (currentCollision != nullptr) {
		return currentCollision -> getName();
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

const BuildingData& BuildingManager::getBuildingData(std::string type) const{
	std::map<std::string, BuildingData>::const_iterator it = baseBuildings.find(type);
	/*if (it != baseBuildings.end()){
		//return &it->second;
	}*/ if (it == baseBuildings.end()) {
		std::cout << "El tipo de edificio " << type << " no es valido." << std::endl;
		exit(0);
		//return BuildingData();
	}
	return it->second;
}