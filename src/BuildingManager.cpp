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
	buildings = new std::vector<Building*>();
	cube = NULL;
}
 
BuildingManager::~BuildingManager(){
	delete cube;
	delete buildingLayer;
	delete buildings;
}

void BuildingManager::setBuildingMode(){
	if (!buildingMode){
		buildingMode = true;
		cube = new Model(buildingLayer, buildings->size());
	}
}

int BuildingManager::getHoverBuilding(){
	//Game *g = Game::Instance();
	if (!buildingMode) {
		SceneNode *collision = buildingLayer -> getNodeCollision(Game::Instance() -> getCursor());
		if (collision != NULL){
			return collision->getSceneNode()->getID();
		}
	}
	return -1;
}

void BuildingManager::drawBuilding(Terrain *terrain, Enumeration::BuildingType _type, Enumeration::Team _team){
    Game *g = Game::Instance();
    if (buildingMode && cube != NULL){
        // Aqui tenemos que hacer que cuando se haya apretado el boton de nueva ventana,
        // tambien se cree una caja en las coordenadas actuales del cursor del raton.
		/*
		* Get position where the cursor is pointing to the terrain
		*/
        Vector3<float> xyzPointCollision = terrain -> getPointCollision(g -> getCursor());
        float x = roundf(xyzPointCollision.x / gridAlignment) * gridAlignment;
        float y = roundf(xyzPointCollision.y / gridAlignment) * gridAlignment;
        float z = roundf(xyzPointCollision.z / gridAlignment) * gridAlignment;
        //ToDo: irr::core::aabbox3d< T >

		cube -> getModel() -> setMaterialFlag(video::EMF_LIGHTING, false);
		cube -> getModel() -> setPosition(core::vector3df(x,y,z));

		/*
		* Look if there is any other building built there
		*/
		bool collision = false;
		for (int i = 0; i < buildings -> size() && !collision; i++){
			Box3D<float> box = Box3D<float>(cube -> getModel() -> getTransformedBoundingBox()); //ToDo: esto en building
			collision = buildings -> at(i) -> getHitbox() -> intersects(box);
		}
		if (collision){
			g -> getWindow() -> getSceneManager() -> getMeshManipulator() -> setVertexColors(cube -> getModel() -> getMesh(), video::SColor(255,0,0,255));
		} else {
			g -> getWindow() -> getSceneManager() -> getMeshManipulator() -> setVertexColors(cube -> getModel() -> getMesh(), video::SColor(255,255,255,255));
			/*
			* If there is no collision and the player press left button of the mouse,
			* build the building
			*/
			if (g->getIO() -> leftMouseDown()){
				buildingMode = false;
				buildBuilding(new Vector3<float>(x, y, z), _type, _team);
			}
		}
    }
}

void BuildingManager::buildBuilding(Vector3<float>* pos, Enumeration::BuildingType _type, Enumeration::Team _team) {
	if(_type == Enumeration::BuildingType::Tower) {
			buildings->push_back(new Tower(pos, _team));
			return;
    }
	buildings->push_back(new Building(_type, pos, _team));
}

std::vector<Building*>* BuildingManager::getBuildings() {
	return buildings;
}

/*
void BuildingManager::drawCube(Terrain *terrain){
    Game *g = Game::Instance();
    if (buildingMode && cube != NULL){
        // Aqui tenemos que hacer que cuando se haya apretado el boton de nueva ventana,
        // tambien se cree una caja en las coordenadas actuales del cursor del raton.
        Vector3<float> xyzPointCollision = terrain -> getPointCollision(g -> getCursor());
        
        float x = roundf(xyzPointCollision.x / gridAlignment) * gridAlignment;
        float y = roundf(xyzPointCollision.y / gridAlignment) * gridAlignment;
        float z = roundf(xyzPointCollision.z / gridAlignment) * gridAlignment;
        //ToDo: irr::core::aabbox3d< T >
		cube -> getModel() -> setMaterialFlag(video::EMF_LIGHTING, false);
		cube -> getModel() -> setPosition(core::vector3df(x,y,z));
		bool collision = false;
		for (int i = 0; i < buildings -> size() && !collision; i++){
			Box3D<float> box = Box3D<float>(cube -> getModel() -> getTransformedBoundingBox());
			collision = buildings -> at(i).intersects(box);
		}
		if (collision){
			g -> getWindow() -> getSceneManager() -> getMeshManipulator() -> setVertexColors(cube -> getModel() -> getMesh(), video::SColor(255,0,0,255));
		} else {
			g->getWindow() -> getSceneManager() -> getMeshManipulator() -> setVertexColors(cube -> getModel() -> getMesh(), video::SColor(255,255,255,255));
			if (g->getIO() -> leftMouseDown()){
				buildingMode = false;
				buildings -> push_back(Box3D<float>(cube -> getModel() -> getTransformedBoundingBox()));Window::Instance()->getSceneManager()
			}
		}
    }
}*/