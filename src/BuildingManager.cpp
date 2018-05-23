#include "BuildingManager.h"
#include "Game.h"
#include <WorldEngine/WorldGeometry.h>
#include <GraphicEngine/Window.h>
#include <OBDEngine/ResourceManager/ResourceJSON.h>

BuildingManager::BuildingManager(Enumeration::Team t, std::string b) {
	team = t;

	nextBuildingId = 1;
    buildingMode = false;

	buildingLayer = new SceneNode();
	currentCollisionID = -1;
	inMapBuildings = new std::map<i32, Building*>();
	tempBuilding = nullptr;

    ResourceJSON *r = (ResourceJSON*)IO::Instance() -> getResourceManager() -> getResource("media/gameConfig/BuildingData/"+b+"Buildings.json", true);
    json j = *r -> getJSON();

    for (auto& element : j["Buildings"]) {
		BuildingData tmp;
			tmp.type = element["buildingName"].get<std::string>();
			tmp.modelPath = element["modelPath"].get<std::string>();
			tmp.metalCost = element["metalCost"].get<i32>();
			tmp.crystalCost = element["crystalCost"].get<i32>();
			tmp.maxHP = element["maxHP"].get<i32>();
			tmp.viewRadius = element["viewRadius"].get<i32>();
			tmp.attackRange = element["attackRange"].get<i32>();
			tmp.attackDamage = element["attackDamage"].get<i32>();
			tmp.attackSpeed = element["attackSpeed"].get<i32>();
			tmp.happinessVariation = element["happinessVariation"].get<i32>();
			tmp.citizensVariation = element["citizensVariation"].get<i32>();
			tmp.bbOffset = element["bbOffset"].get<f32>();
			tmp.buildingTime = element["buildingTime"].get<f32>();
			tmp.cityLevel = element["cityLevel"].get<i32>();
			tmp.cellsX = element["cellsX"].get<i32>();
			tmp.cellsY = element["cellsY"].get<i32>();
			Window::Instance() -> getEngineResourceManager() -> loadResource(element["modelPath"].get<std::string>());
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
		currentCollisionID = buildingLayer -> getNodeCollision(IO::Instance() -> getMouse() -> getPosition());
	}
}

bool BuildingManager::setBuildingMode(std::string type) {
	std::map<std::string, BuildingData>::iterator it = baseBuildings.find(type);
	if (it != baseBuildings.end() && checkCanPay(type)) {
		if (!buildingMode) {
			buildingMode = true;
			tempBuilding = new Building(buildingLayer, nextBuildingId++, team, it -> second, this);
			return true;
		}
	}
	return false;
}

/* ToDo: optimize, to much shit inside */
void BuildingManager::drawBuilding() {
    if (buildingMode && tempBuilding != nullptr) {
		//Get position where the cursor is pointing to the terrain
        Vector2<f32> collisionPoint = Map::Instance() -> getTerrain() -> getPointCollision(IO::Instance() -> getMouse() -> getPosition()).toVector2();
		// Change 2nd parameter
		bool canBuild = true;
		Vector2<f32> dummy = WorldGeometry::Instance()->correctBuildingPosition(collisionPoint, tempBuilding->getHitbox());

		tempBuilding -> setPosition(dummy);

		if (team == Enumeration::Team::Human) {
			Vector3<f32> tmp = Human::Instance()->hallPosition;
			f32 distance = std::sqrt(std::pow(tmp.x - dummy.x, 2) + std::pow(tmp.z - dummy.y, 2));
			if (Human::Instance()->buildableRange < distance) {
				canBuild = false;
			}
			else {
				canBuild = WorldGeometry::Instance()->checkHitBoxCollision(tempBuilding->getHitbox(), true);
			}
		}

		//Pressing the right mouse button cancels the building
		if (IO::Instance() -> getMouse() -> rightMouseDown()) {
			buildingMode = false;
			delete tempBuilding;	
			/* ToDo: comprobar que esto esta bien comentado, sin comentar da error */	
			tempBuilding = nullptr;
			return;
		}

		if (IO::Instance() -> getKeyboard() -> keyPressed(82)) { //ToDo: fachada
			f32 rot = tempBuilding -> getModel() -> getRotation() . y;
			rot += 90;
			if (rot > 360) rot = 0;
			tempBuilding -> getModel() -> setRotation(Vector3<f32>(0, rot, 0));
		}
		
		if (!canBuild) {
			tempBuilding->setCantBuildColor();
		} else {
			tempBuilding->setBaseColor();
			//If there is no collision and the player press left button of the mouse, build the building
			if (IO::Instance() -> getMouse() -> leftMouseDown()) {
				buildingMode = false;
				buildBuilding(dummy);
			}
		}
    }
}

void BuildingManager::createBuilding(Vector2<f32> pos, std::string type, i32 buildTime) {
	std::map<std::string, BuildingData>::iterator it = baseBuildings.find(type);
	if (it != baseBuildings.end()) {
		BuildingData b = it -> second;
		if (buildTime >= 0) b.buildingTime = buildTime;
		tempBuilding = new Building(buildingLayer, nextBuildingId++, team, b, this);
		
		buildBuilding(pos);
	}
}

void BuildingManager::buildBuilding(Vector2<f32> pos) {
	if (tempBuilding != nullptr) {
		//Establece la posicion inicial del edificio
		tempBuilding -> setPosition(pos);
		//Establece un callback que se ejecutará al acabar de construir
		tempBuilding -> setFinishedCallback([&](Building *b) {
			buildingAmounts[b -> getType()]++;
			
			if (team == Enumeration::Team::Human) {
				if (buildingAmounts[b -> getType()] == 1 
					&& (b -> getType() == "Barrack" || b -> getType() == "Barn" || b -> getType() == "Workshop")) {
					Hud::Instance() -> enableTab(b -> getType());
				}
				if (b -> getBuildingTime()) IO::Instance() -> getEventManager() -> triggerEvent("showBuiltText");  
			}
		});

		//Insert building in a map
		inMapBuildings -> insert(std::pair<i32,Building*>(tempBuilding->getID(), tempBuilding));
		
		//Start the construction of the building
		tempBuilding -> startBuilding();
		
		//Build
		WorldGeometry::Instance() -> build(tempBuilding);
		//Finish everything
		tempBuilding = nullptr;
	} else {
		std::cerr << "Error: se ha intentado construir un edificio inexistente" << std::endl;
		exit(0);
	}
}

/**
 * This method is responsible for managing calls to isSolvent() for the human, registering the type
 * of the desired building and sending the aforementhioned method the prices. It has its own method
 * to avoid cluttering the setBuildingMode() method, as it used to be there in the first place.
 */
bool BuildingManager::checkCanPay(std::string type) {
	std::map<std::string, BuildingData>::iterator it = baseBuildings.find(type);
	if (it != baseBuildings.end()) {
		if (team == Enumeration::Team::Human)
			return Human::Instance() -> isSolvent(it->second.metalCost, it->second.crystalCost, 0);
		else
			return IA::Instance() -> isSolvent(it->second.metalCost, it->second.crystalCost, 0);
	}
	return false;
}

bool BuildingManager::checkFinished(i32 _id) {	
	return (inMapBuildings -> find(_id) -> second -> getFinished());	
}

i32 BuildingManager::getAmount(std::string type) {
	std::map<std::string, BuildingData>::iterator it = baseBuildings.find(type);
	if (it != baseBuildings.end()) {
		return buildingAmounts[type];
	} 
	return 0;
}

i32 BuildingManager::getCollisionID() {
	return currentCollisionID;
}

std::map<i32, Building*>* BuildingManager::getBuildings() {
	return inMapBuildings;
}

SceneNode* BuildingManager::getBuildingLayer() {
	return buildingLayer;
}

void BuildingManager::deleteBuilding(i32 id) {
    std::map<i32, Building*>::iterator it = inMapBuildings->find(id);
    if (it != inMapBuildings->end()) {
		if (it -> second -> getTeam() == Enumeration::Team::Human) {
			Human::Instance() -> modifyHappiness(-it -> second -> getHappinessVariation());
			if (it -> second -> getType() == "House") {
				Human::Instance() -> modifyMaxPeople(-it -> second -> getCitizensVariation());
			}
		} else {
			IA::Instance() -> modifyHappiness(-it -> second -> getHappinessVariation());
			if (it -> second -> getType() == "House") {
				IA::Instance() -> modifyMaxPeople(-it -> second -> getCitizensVariation());
			}
		}
		buildingAmounts[it -> second -> getType()]--;
		delete it -> second;
		inMapBuildings -> erase(id);
	}
} 

Building *BuildingManager::getBuilding(i32 id) {
  	std::map<i32,Building*>::iterator it;
	it = inMapBuildings->find(id);
  	if (it != inMapBuildings->end())
		return it->second;
	else 
		return nullptr;
}

const BuildingData& BuildingManager::getBuildingData(std::string type) const{
	std::map<std::string, BuildingData>::const_iterator it = baseBuildings.find(type);
	if (it == baseBuildings.end()) {
		std::cerr << "Error: el tipo de edificio " << type << " no es valido." << std::endl;
		exit(0);
	}
	return it->second;
}