#include "BuildingManager.h"
#include "Game.h"
#include "Human.h"
#include "IA.h"
#include "Tower.h"

using namespace irr;

BuildingManager::BuildingManager(){
    buildingMode = false;
    gridAlignment = 50;
	buildingLayer = new SceneNode();
	buildings = new std::map<int, Building*>();
	tempBuilding = NULL;
	id = 0;
	currentCollision = NULL;
}

BuildingManager::~BuildingManager(){
	delete tempBuilding;
	delete buildingLayer;
	delete buildings;
}

void BuildingManager::testRaycastCollisions(){
	if (!buildingMode) {
		currentCollision = buildingLayer -> getNodeCollision(Game::Instance() -> getCursor());
	}
}

int BuildingManager::getCollisionID(){
	if (currentCollision != NULL && currentCollision->getSceneNode() != NULL){
		return currentCollision->getSceneNode()->getID();
	}
	return -1;
}

std::string BuildingManager::getCollisionName(){
	if (currentCollision != NULL && currentCollision->getSceneNode() != NULL){
		return currentCollision->getSceneNode()->getName();
	}
	return NULL;
}

void BuildingManager::setBuildingMode(Enumeration::BuildingType type){
	if (checkCanPay(type)) {
		if (!buildingMode){
			buildingMode = true;
			setTempBuildingModel(Vector3<float>(0, 0, 0),type, Enumeration::Team::Human);
		}
	}
}

void BuildingManager::drawBuilding(Terrain *terrain){
    Game *g = Game::Instance();
    if (buildingMode && tempBuilding != NULL){
        // Aqui tenemos que hacer que cuando se haya apretado el boton de nueva ventana,
        // tambien se cree una caja en las coordenadas actuales del cursor del raton.
		/*
		* Get position where the cursor is pointing to the terrain
		*/
        Vector3<float> xyzPointCollision = terrain -> getPointCollision(g -> getCursor());

		Vector3<float> f = Box3D<float>(tempBuilding->getModel()->getModel()->getTransformedBoundingBox()).getSize();

        float x = roundf(xyzPointCollision.x / gridAlignment) * gridAlignment;
        float y = (roundf(xyzPointCollision.y / gridAlignment) * gridAlignment) + (f.y/2);
        float z = roundf(xyzPointCollision.z / gridAlignment) * gridAlignment;

		tempBuilding -> setPosition (Vector3<float>(x, y, z));

			
		//Pressing the right mouse button cancels the building
		if (g->getIO() -> rightMouseDown()){
			buildingMode = false;

			delete tempBuilding;		

			tempBuilding = NULL;

			return;
		}

		/* 
		* Look if there is any other building built there
		*/
		bool collision = false;
		for (std::map<int,Building*>::iterator it = buildings->begin(); it != buildings->end() && !collision; ++it){
			collision = it -> second -> getHitbox() -> intersects(*tempBuilding->getHitbox());
		}
		if (collision){
			g -> getWindow() -> getSceneManager() -> getMeshManipulator() -> setVertexColors(
				tempBuilding -> getModel() -> getModel() -> getMesh(), video::SColor(255,0,0,255)
			); //ToDo: esto es fachada
		} else {
			g -> getWindow() -> getSceneManager() -> getMeshManipulator() -> setVertexColors(
				tempBuilding -> getModel() -> getModel() -> getMesh(), tempBuilding -> getColor()
			); //ToDo: esto es fachada

			/*
			* If there is no collision and the player press left button of the mouse,
			* build the building
			*/
			if (g->getIO() -> leftMouseDown()){
				buildingMode = false;
				buildBuilding(Vector3<float>(x, y, z), (Enumeration::BuildingType)tempBuilding->getType(), Enumeration::Team::Human);
			}
		}
    }
}

void BuildingManager::buildBuilding(Vector3<float> pos, Enumeration::BuildingType _type, Enumeration::Team _team) {
	if (_team == Enumeration::Team::IA){
		setTempBuildingModel(pos, _type, _team);
		/*
		if(_type == Enumeration::BuildingType::Tower) {
			buildings->insert(std::pair<int,Building*>(id, new Tower(0, buildingLayer, pos, _team)));
		} else {
			buildings->insert(std::pair<int,Building*>(id, new Building(0, buildingLayer, _type, pos, _team)));
		}*/
		buildings->insert(std::pair<int,Building*>(id, tempBuilding));
		tempBuilding = NULL;
		id++;
	} else {
		if (tempBuilding == NULL){
			//tempBuilding = new Building(id, buildingLayer, _type, pos, _team);
			//Poner modelo
			
			setTempBuildingModel(pos,_type,_team);
			tempBuilding ->setPosition(pos);
			tempBuilding ->setHitbox();

		
		}
		tempBuilding->getModel()->setID(id);
		buildings->insert(std::pair<int,Building*>(id, tempBuilding));

		Game::Instance()->getGameState()->getHud()->addTab(id, tempBuilding->getType());
		// Tax the player when placing the building
		tempBuilding -> taxPlayer(Enumeration::Team::Human);
		id++;
		tempBuilding = NULL;
	}
	
}

void BuildingManager::setTempBuildingModel(Vector3<float> pos, Enumeration::BuildingType _type, Enumeration::Team _team) {
	if(_type == Enumeration::BuildingType::Tower){
		tempBuilding = new Tower(0, buildingLayer, Vector3<float>(0, 0, 0), Enumeration::Team::Human);
	} else if (_type == Enumeration::BuildingType::House){
		tempBuilding = new Building(0, buildingLayer, L"media/buildingModels/vivienda.obj", _type, pos, _team);
		tempBuilding->getModel()->getModel()->setScale(core::vector3df(25,25,25)); //ToDo: fachada
	} else if (_type == Enumeration::BuildingType::Barrack){
		tempBuilding = new Building(0, buildingLayer, L"media/buildingModels/barraca.obj", _type, pos, _team);
		tempBuilding->getModel()->getModel()->setScale(core::vector3df(25,25,25)); //ToDo: fachada
	} else if (_type == Enumeration::BuildingType::Siderurgy){
		tempBuilding = new Building(0, buildingLayer, L"media/buildingModels/siderurgia.obj", _type, pos, _team);
		tempBuilding->getModel()->getModel()->setScale(core::vector3df(25,25,25)); //ToDo: fachada
	} else if (_type == Enumeration::BuildingType::School){
		tempBuilding = new Building(0, buildingLayer, L"media/buildingModels/escuela.obj", _type, pos, _team);
		tempBuilding->getModel()->getModel()->setScale(core::vector3df(25,25,25)); //ToDo: fachada
	} else if (_type == Enumeration::BuildingType::Market){
		tempBuilding = new Building(0, buildingLayer, L"media/buildingModels/mercado.obj", _type, pos, _team);
		tempBuilding->getModel()->getModel()->setScale(core::vector3df(25,25,25)); //ToDo: fachada
	} else
		tempBuilding = new Building(0, buildingLayer, _type, pos, _team);
}

std::map<int, Building*>* BuildingManager::getBuildings() {
	return buildings;
}

/**
 * Checks if the player, either the human or the AI can afford to build a specific building 
 */
bool BuildingManager::isSolvent(int metalCost, int crystalCost, Enumeration::Team team) {
	int metalAmt = 0;
	int crystalAmt = 0;
	if (team == Enumeration::Team::Human) {
		metalAmt = Human::getInstance() -> getMetalAmount();
		crystalAmt = Human::getInstance() -> getCrystalAmount();
	} else {
		metalAmt = IA::getInstance() -> getMetalAmount();
		crystalAmt = IA::getInstance() -> getCrystalAmount();
		//std::cout << metalAmt << "/" << metalCost << std::endl;
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
bool BuildingManager::checkCanPay(Enumeration::BuildingType type) {
	//Esto esta aqui para no hacer clutter arriba
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

void BuildingManager::updateBuildingManager() {
	for (std::map<int,Building*>::iterator it = buildings->begin(); it != buildings->end(); ++it){
		//Esto es una guarrada y es una mierda, pero si no no va
		it -> second -> setHitbox();
		//it -> second ->updateHitbox();
		it -> second -> update();
	}
}

bool BuildingManager::checkFinished(int _id) {
	// Si no no coge bien los ids
	int targetId = _id -1;
	if (targetId < 0) {
		// corregir para que el id del edificio principal no sea -1
		targetId = 0;
	} 

	//Esto siempre devuelve true
	for (std::map<int,Building*>::iterator it = buildings->begin(); it != buildings->end(); ++it){
		if (it -> second -> getID() == targetId) {
			
			if (it -> second -> getFinished() == true) {
				return true;
			}
		}
	}

}

SceneNode* BuildingManager::getBuildingLayer() {
	return buildingLayer;
}

