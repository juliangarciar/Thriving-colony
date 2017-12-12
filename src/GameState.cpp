#include "GameState.h"
#include "Game.h"

GameState::GameState() : State() {
    camera = new CameraController();
    map = new Terrain("media/heightmap.bmp"); //ToDo: mover a map
    hud = new Hud();
	buildingManager = new BuildingManager();
}

GameState::~GameState() {
    delete buildingManager;
    delete camera;
    delete hud;
}

    map->setTexture(new Texture("media/map-texture.jpg"), new Texture("media/map-detail-texture.jpg")); //ToDo: mover a map
    //hud->drawCube(Game::Instance()->getIO(), cursor, map);
}

void GameState::Input(){
    hud->getHUDEvents();

    camera->Move(Game::Instance()->getIO(), Game::Instance()->getCursor());
    camera->RotateAndInclinate(Game::Instance()->getIO(), Game::Instance()->getCursor());
    camera->Zoom(Game::Instance()->getIO());

    Vector3<float> v = map->getPointCollision(Game::Instance()->getCursor());
	buildingManager->getHoverBuilding();
    //std::cout << v.x << " " << v.y << " " << v.z << std::endl;
}

void GameState::Update(){
    camera->Update(map, Game::Instance()->getWindow()->getDeltaTime());

    Vector3<float> cam = camera->getCamera()->getCameraPosition();
    Vector3<float> tar = camera->getCamera()->getTargetPosition();

    //buildingManager->drawCube(map);
    buildingManager->buildBuilding(map, 200, new Vector3<float>(0, 0, 0), Enumeration::BuildingType::House, true);
}

void GameState::Render(){

}

void GameState::CleanUp(){

}

BuildingManager *GameState::getBuildingManager(){
	return buildingManager;
}