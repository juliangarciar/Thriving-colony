#include "GameState.h"
#include "Game.h"
#include "Human.h"
#include "IA.h"

GameState::GameState() : State() {
    camera = new CameraController();
    map = new Terrain("media/heightmap.bmp"); //ToDo: mover a map
    hud = new Hud();
    nodeRootIA = new RootNode();
}

GameState::~GameState() {
    delete nodeRootIA;
    delete camera;
    delete hud;
    delete map;
}

void GameState::Init(){
    map->setTexture(new Texture("media/map-texture.jpg"), new Texture("media/map-detail-texture.jpg")); //ToDo: mover a map
}

void GameState::Input(){
    hud->getHUDEvents();

    camera->Move(Game::Instance()->getIO(), Game::Instance()->getCursor());
    camera->RotateAndInclinate(Game::Instance()->getIO(), Game::Instance()->getCursor());
    camera->Zoom(Game::Instance()->getIO());

    Vector3<float> v = map->getPointCollision(Game::Instance()->getCursor());
    if (Game::Instance()->getIO()->leftMousePressed()){
        int id = Human::getInstance() -> getBuildings()->getHoverBuilding();
        if (id != -1){
           /* std::wstringstream o;
            o << "Has hecho click en: " << id;
            hud->getInfoButton()->setText(o.str().c_str());*/
            hud->showPopup(id);
        }
	}
}

void GameState::Update(){
    camera->Update(map, Game::Instance()->getWindow()->getDeltaTime());

    Vector3<float> cam = camera->getCamera()->getCameraPosition();
    Vector3<float> tar = camera->getCamera()->getTargetPosition();

    //buildingManager->drawCube(map);
    Human::getInstance() -> getBuildings() -> drawBuilding(map, Enumeration::BuildingType::House,  Enumeration::Team::Human);
    if(!unitDone){
        Vector3<float> *vectorData = new Vector3<float>(200, 200, 200);
        Enumeration::UnitType unitData;
        unitData.unitClass = Enumeration::UnitType::Class::Ranged;
        unitData.unitSubClass = Enumeration::UnitType::SubClass::StandardR;
        Human::getInstance()->getUnits()->createTroop(vectorData, unitData);
        this->unitDone = true;
    }
    
    nodeRootIA -> question();
}

void GameState::Render(){

}

void GameState::CleanUp(){

}

Terrain* GameState::getMap() {
    return map;
}