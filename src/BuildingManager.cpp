#include "BuildingManager.h"
#include "Game.h"

using namespace irr;

BuildingManager::BuildingManager(){
    buildingMode = false;
    gridAlignment = 50;
	cube = NULL;
	buildingLayer = new SceneNode();
	buildings = new std::vector<Building*>();
}
 
BuildingManager::~BuildingManager(){
	delete cube;
	delete buildingLayer;
	delete buildings;
}

void BuildingManager::setBuildingMode(bool mode){
	buildingMode = mode;
	cube = new Model(buildingLayer);
}

void BuildingManager::getHoverBuilding(){
	SceneNode collision = buildingLayer -> getNodeCollision(Game::Instance() -> getCursor());
}

void BuildingManager::buildBuilding(Terrain *terrain, int hitPoints, Vector3<float>* pos, Enumeration::BuildingType _type, bool _team){
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
		* Look if there is any other building built
		*/
		bool collision = false;
		for (int i = 0; i < buildings -> size() && !collision; i++){
			Box3D<float> box = Box3D<float>(cube -> getModel() -> getTransformedBoundingBox());
			collision = buildings -> at(i) -> getHitbox() -> intersects(box);
		}
		if (collision){
			g -> getWindow() -> getSceneManager() -> getMeshManipulator() -> setVertexColors(cube -> getModel() -> getMesh(), video::SColor(255,0,0,255));
		} else {
			g->getWindow() -> getSceneManager() -> getMeshManipulator() -> setVertexColors(cube -> getModel() -> getMesh(), video::SColor(255,255,255,255));
			/*
			* If there is no collision and the player press left button of the mouse,
			* build the building
			*/
			if (g->getIO() -> leftMouseDown()){
				buildingMode = false;
				buildings -> push_back(new Building(hitPoints, pos, _type, _team, new Box3D<float>(cube -> getModel() -> getTransformedBoundingBox()), cube));
			}
		}
    }
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
				buildings -> push_back(Box3D<float>(cube -> getModel() -> getTransformedBoundingBox()));
			}
		}
    }
}*/