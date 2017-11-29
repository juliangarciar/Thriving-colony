#include "GameState.h"
#include "Game.h"

GameState::GameState() : State() {
    camera = new CameraController();
    cursor = new Mouse();
    map = new Terrain("media/heightmap.bmp"); //ToDo: mover a map
}

GameState::~GameState() {
    
}

void GameState::Init(){
    map->setTexture(new Texture("media/map-texture.jpg"), new Texture("media/map-detail-texture.jpg")); //ToDo: mover a map
}

void GameState::Input(){
    camera->Move(Game::Instance()->getIO(), cursor);
    camera->Rotate(Game::Instance()->getIO(), cursor);
    camera->Inclinate(Game::Instance()->getIO(), cursor);
    camera->Zoom(Game::Instance()->getIO());

    Vector3<float> v = map->getPointCollision(cursor);
    //std::cout << v.x << " " << v.y << " " << v.z << std::endl;
}

void GameState::Update(){
    camera->Update(map, Game::Instance()->getWindow()->getDeltaTime());

    Vector3<float> cam = camera->getCamera()->getCameraPosition();
    std::cout << "cam " << cam.x << " " << cam.y << " " << cam.z << std::endl;
    Vector3<float> tar = camera->getCamera()->getTargetPosition();
    std::cout << "tar " << tar.x << " " << tar.y << " " << tar.z << std::endl;
}

void GameState::Render(){

}

void GameState::CleanUp(){

}