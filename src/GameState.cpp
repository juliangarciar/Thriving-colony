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
    camera->Move(Game::Instance()->getIO(), cursor, map);
    camera->Rotate(Game::Instance()->getIO(), cursor);
    Vector3<float> v = map->getPointCollision(cursor);
    //std::cout << v.x << " " << v.y << " " << v.z << std::endl;
}

void GameState::Update(){

}

void GameState::Render(){

}

void GameState::CleanUp(){

}