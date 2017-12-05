#include "GameState.h"
#include "Game.h"

GameState::GameState() : State() {
    camera = new CameraController();
    map = new Terrain("media/heightmap.bmp"); //ToDo: mover a map
    hud = new Hud();
}

GameState::~GameState() {
    
}

void GameState::Init(){
    map->setTexture(new Texture("media/map-texture.jpg"), new Texture("media/map-detail-texture.jpg")); //ToDo: mover a map
    //hud->drawCube(Game::Instance()->getIO(), cursor, map);
}

void GameState::Input(){
    camera->Move(Game::Instance()->getIO(), cursor);
    camera->RotateAndInclinate(Game::Instance()->getIO(), cursor);
    hud->showHud();
    hud->drawCube(Game::Instance()->getIO(), cursor, map);
    camera->Move(Game::Instance()->getIO(), cursor);
    camera->RotateAndInclinate(Game::Instance()->getIO(), cursor);
    //camera->Inclinate(Game::Instance()->getIO(), cursor);
    camera->Zoom(Game::Instance()->getIO());

    Vector3<float> v = map->getPointCollision(Game::Instance()->getCursor());
    //std::cout << v.x << " " << v.y << " " << v.z << std::endl;
}

void GameState::Update(){
    camera->Update(map, Game::Instance()->getWindow()->getDeltaTime());

    Vector3<float> cam = camera->getCamera()->getCameraPosition();
    Vector3<float> tar = camera->getCamera()->getTargetPosition();

    hud->drawCube(map);
}

void GameState::Render(){

}

void GameState::CleanUp(){

}