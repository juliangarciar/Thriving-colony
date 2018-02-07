#include "BuildingManager.h"
#include "Game.h"
#include "Human.h"
#include "IA.h"

using namespace irr;

BuildingManager::BuildingManager(Enumeration::Team t, Enumeration::BreedType b) {
	team = t;
	breed = b;

	nextBuildingId = 0;
    gridAlignment = 50;
    buildingMode = false;

	buildingLayer = new SceneNode();
	currentCollision = NULL;
	buildings = new std::map<int, Building*>();
	tempBuilding = NULL;

	for (int i = 0; i < Enumeration::BuildingType::BuildingsSize; i++){
		buildingAmounts[i] = 0;
	}
}

BuildingManager::~BuildingManager() {
	delete tempBuilding;
	delete buildingLayer;
	for (std::map<int,Building*>::iterator it = buildings -> begin(); it != buildings -> end(); ++it) {
		delete it -> second;
    }
	buildings -> clear();
	delete buildings;
}

void BuildingManager::testRaycastCollisions() {
	if (!buildingMode) {
		currentCollision = buildingLayer -> getNodeCollision(Game::Instance() -> getMouse());
	}
}

void BuildingManager::setBuildingMode(Enumeration::BuildingType type) {
	if (checkCanPay(type)) {
		if (!buildingMode) {
			buildingMode = true;
			setTempBuildingModel(Vector3<float>(0, 0, 0), type);
			recalculateHitbox(); //ToDo: quizas algo guarro pero menos que lo otro
		}
	}
}

void BuildingManager::drawBuilding() {
    Game *g = Game::Instance();
    if (buildingMode && tempBuilding != NULL) {
        // Aqui tenemos que hacer que cuando se haya apretado el boton de nueva ventana,
        // tambien se cree una caja en las coordenadas actuales del cursor del raton.
		/*
		* Get position where the cursor is pointing to the terrain
		*/
        Vector3<float> xyzPointCollision = g -> getGameState() -> getTerrain() -> getPointCollision(g -> getMouse());

		Vector3<float> f = Box3D<float>(tempBuilding -> getModel() -> getModel() -> getTransformedBoundingBox()).getSize(); //ToDo: fachada

        float x = roundf(xyzPointCollision.x / gridAlignment) * gridAlignment;
        float y = (roundf(xyzPointCollision.y / gridAlignment) * gridAlignment) + (f.y/2);
        float z = roundf(xyzPointCollision.z / gridAlignment) * gridAlignment;

		tempBuilding -> setPosition (Vector3<float>(x, y, z));

		//Pressing the right mouse button cancels the building
		if (g -> getMouse() -> rightMouseDown()){
			buildingMode = false;

			delete tempBuilding;		

			tempBuilding = NULL;

			return;
		}

		/* 
		* Look if there is any other building built there
		*/
		bool collision = false;
		for (std::map<int,Building*>::iterator it = buildings -> begin(); it != buildings -> end() && !collision; ++it) {
			collision = it -> second -> getHitbox() -> intersects(*tempBuilding -> getHitbox());
		}
		if (collision) {
			tempBuilding->setColor(video::SColor(255,0,0,255)); //ToDo: reemplazar color por material
		} else {
			tempBuilding->setColor(tempBuilding -> getBaseColor()); //ToDo: reemplazar color por material

			/*
			* If there is no collision and the player press left button of the mouse,
			* build the building
			*/
			if (g -> getMouse() -> leftMouseDown()) {
				buildingMode = false;
				buildBuilding(Vector3<float>(x, y, z), tempBuilding -> getType());
			}
		}
    }
}

void BuildingManager::buildBuilding(Vector3<float> pos, Enumeration::BuildingType _type, bool instabuild) {
	if (team == Enumeration::Team::IA || tempBuilding == NULL) {
		setTempBuildingModel(pos, _type);
		tempBuilding -> setPosition(pos);
	}

    //Establece la ID inicial del edificio
	tempBuilding -> setID(nextBuildingId);
    //Establece el color inicial del edificio
    tempBuilding -> setColor(video::SColor(255, 0, 0, 0)); //ToDo: reemplazar color por material

	tempBuilding -> setFinishedCallback([&](Building *b){
		//Tax the player when building is finished
		b->posTaxPlayer();
		b->setColor(b->getBaseColor()); //ToDo: cambiar por material

		buildingAmounts[(int)_type]++;

		//Cuando te ataquen y paren
		//returnToOriginalColor(); 
		
		if (team == Enumeration::Team::Human){
			if (buildingAmounts[(int)_type] == 1){
				switch (_type){
					case Enumeration::BuildingType::Barrack:
						Game::Instance() -> getGameState() -> getHud() -> enableTab(_type);
					break;
					case Enumeration::BuildingType::Barn:
						Game::Instance() -> getGameState() -> getHud() -> enableTab(_type);
					break;
					case Enumeration::BuildingType::Workshop:
						Game::Instance() -> getGameState() -> getHud() -> enableTab(_type);
					break;
					default: break;
				}
			}
            // Increase stuff when the human ends the building, but do so for the AI
            // when it places the building. is it fair? i dunno
			Game::Instance() -> getEvents() -> triggerEvent(Enumeration::EventType::EnableText);    
		}
	});

	buildings -> insert(std::pair<int,Building*>(nextBuildingId, tempBuilding));

	// Tax the player when placing the building
	tempBuilding -> preTaxPlayer();

	if (instabuild) tempBuilding -> triggerFinishedCallback();    

	tempBuilding = NULL;
	nextBuildingId++;
}

void BuildingManager::setTempBuildingModel(Vector3<float> pos, Enumeration::BuildingType _type) {
	switch (_type){
		case Enumeration::BuildingType::Barn:
			tempBuilding = new Building(buildingLayer, 0, L"media/buildingModels/establo.obj", team, breed, _type, pos);
			tempBuilding -> getModel() -> setScale(Vector3<float>(25,25,25));
		break;
		case Enumeration::BuildingType::Barrack:
			tempBuilding = new Building(buildingLayer, 0, L"media/buildingModels/barraca.obj", team, breed, _type, pos);
			tempBuilding -> getModel() -> setScale(Vector3<float>(25,25,25));
		break;
		case Enumeration::BuildingType::Hospital:
			tempBuilding = new Building(buildingLayer, 0, L"media/buildingModels/hospital.obj", team, breed, _type, pos);
			tempBuilding -> getModel() -> setScale(Vector3<float>(25,25,25));
		break;
		case Enumeration::BuildingType::House:
			tempBuilding = new Building(buildingLayer, 0, L"media/buildingModels/vivienda.obj", team, breed, _type, pos);
			tempBuilding -> getModel() -> setScale(Vector3<float>(25,25,25));
		break;
		case Enumeration::BuildingType::MainBuilding:
			tempBuilding = new Building(buildingLayer, 0, L"media/buildingModels/centro_de_mando.obj", team, breed, _type, pos);
			tempBuilding -> getModel() -> setScale(Vector3<float>(25,25,25));
		break;
		case Enumeration::BuildingType::Market:
			tempBuilding = new Building(buildingLayer, 0, L"media/buildingModels/mercado.obj", team, breed, _type, pos);
			tempBuilding -> getModel() -> setScale(Vector3<float>(25,25,25));
		break;
		case Enumeration::BuildingType::Quarry:
			tempBuilding = new Building(buildingLayer, 0, L"media/buildingModels/cantera.obj", team, breed, _type, pos);
			tempBuilding -> getModel() -> setScale(Vector3<float>(25,25,25));
		break;
		case Enumeration::BuildingType::School:
			tempBuilding = new Building(buildingLayer, 0, L"media/buildingModels/escuela.obj", team, breed, _type, pos);
			tempBuilding -> getModel() -> setScale(Vector3<float>(25,25,25));
		break;
		case Enumeration::BuildingType::Siderurgy:
			tempBuilding = new Building(buildingLayer, 0, L"media/buildingModels/siderurgia.obj", team, breed, _type, pos);
			tempBuilding -> getModel() -> setScale(Vector3<float>(25,25,25));
		break;
		case Enumeration::BuildingType::Tower:
			tempBuilding = new Building(buildingLayer, 0, L"media/buildingModels/torre_vigilancia.obj", team, breed, _type, pos);
			tempBuilding -> getModel() -> setScale(Vector3<float>(25,25,25));
		break;
		case Enumeration::BuildingType::Wall:
			tempBuilding = new Building(buildingLayer, 0, L"media/buildingModels/muralla.obj", team, breed, _type, pos);
			tempBuilding -> getModel() -> setScale(Vector3<float>(25,25,25));
		break;
		case Enumeration::BuildingType::Workshop:
			tempBuilding = new Building(buildingLayer, 0, L"media/buildingModels/taller_maquinas_de_asedio.obj", team, breed, _type, pos);
			tempBuilding -> getModel() -> setScale(Vector3<float>(25,25,25));
		break;
		default: break;
	}
}

/**
 * Checks if the player, either the human or the AI can afford to build a specific building 
 */
bool BuildingManager::isSolvent(int metalCost, int crystalCost) {
	int metalAmt = 0;
	int crystalAmt = 0;
	if (team == Enumeration::Team::Human) {
		metalAmt = Human::getInstance() -> getMetalAmount();
		crystalAmt = Human::getInstance() -> getCrystalAmount();
	} else {
		metalAmt = IA::getInstance() -> getMetalAmount();
		crystalAmt = IA::getInstance() -> getCrystalAmount();
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
	switch(type) {
        case Enumeration::BuildingType::School:
			canPay = isSolvent(Enumeration::BuildingCost::SchoolMetalCost, Enumeration::BuildingCost::SchoolCrystalCost);
        break;
        case Enumeration::BuildingType::Market:
			canPay = isSolvent(Enumeration::BuildingCost::MarketMetalCost, Enumeration::BuildingCost::MarketCrystalCost);
        break;
        case Enumeration::BuildingType::Hospital:
			canPay = isSolvent(Enumeration::BuildingCost::HospitalMetalCost, Enumeration::BuildingCost::HospitalCrystalCost);
        break;
        case Enumeration::BuildingType::Siderurgy:
			canPay = isSolvent(Enumeration::BuildingCost::SiderurgyMetalCost, Enumeration::BuildingCost::SiderurgyCrystalCost);
        break;
        case Enumeration::BuildingType::Quarry:
			canPay = isSolvent(Enumeration::BuildingCost::QuarryMetalCost, Enumeration::BuildingCost::QuarryCrystalCost);
        break;
        case Enumeration::BuildingType::House:
			canPay = isSolvent(Enumeration::BuildingCost::HomeMetalCost, Enumeration::BuildingCost::HomeCrystalCost);
        break;
        case Enumeration::BuildingType::Barrack:
			canPay = isSolvent(Enumeration::BuildingCost::BarrackMetalCost, Enumeration::BuildingCost::BarrackCrystalCost);
        break;
        case Enumeration::BuildingType::Barn:
			canPay = isSolvent(Enumeration::BuildingCost::BarnMetalCost, Enumeration::BuildingCost::BarnCrystalCost);
        break;
        case Enumeration::BuildingType::Workshop:
			canPay = isSolvent(Enumeration::BuildingCost::WorkshopMetalCost, Enumeration::BuildingCost::WorkshopCrystalCost);
        break;
        case Enumeration::BuildingType::Wall:
			canPay = isSolvent(Enumeration::BuildingCost::WallMetalCost, Enumeration::BuildingCost::WallCrystalCost);
        break;
        case Enumeration::BuildingType::Tower:
			canPay = isSolvent(Enumeration::BuildingCost::TowerMetalCost, Enumeration::BuildingCost::TowerCrystalCost);
        break;
		default: break;
	}
	return canPay;
}

void BuildingManager::recalculateHitbox(){
	for (std::map<int,Building*>::iterator it = buildings -> begin(); it != buildings -> end(); ++it) {
		it -> second -> refreshHitbox();
	}
}

void BuildingManager::updateBuildingManager() {
	for (std::map<int,Building*>::iterator it = buildings -> begin(); it != buildings -> end(); ++it) {
		it -> second -> update();
	}
}

bool BuildingManager::checkFinished(int _id) {	
	return (buildings -> find(_id) -> second -> getFinished());	
}

int BuildingManager::getAmount(Enumeration::BuildingType t){
	return buildingAmounts[(int)t];
}

int BuildingManager::getCollisionID() {
	if (currentCollision != NULL && currentCollision -> getSceneNode() != NULL) {
		return currentCollision -> getSceneNode() -> getID();
	}
	return -1;
}

std::string BuildingManager::getCollisionName() {
	if (currentCollision != NULL && currentCollision -> getSceneNode() != NULL) {
		return currentCollision -> getSceneNode() -> getName();
	}
	return NULL;
}

std::map<int, Building*>* BuildingManager::getBuildings() {
	return buildings;
}

SceneNode* BuildingManager::getBuildingLayer() {
	return buildingLayer;
}

Building *BuildingManager::getBuilding(int id){
  	std::map<int,Building*>::iterator it;
	it = buildings->find(id);
  	if (it != buildings->end())
		return it->second;
	else 
		return NULL;
}