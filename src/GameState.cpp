#include "GameState.h"
#include "GraphicEngine/Screen.h"

GameState::GameState() : State() {
    camera = new Camera(Screen::Instance()->getSceneManager());
    map = new Terrain("media/heightmap.bmp"); //ToDo: mover a map
}

GameState::~GameState() {
    
}

void GameState::Init(){
    camera->setPosition(Vector3<float>(500, 3000, 500));
    camera->setTargetPosition(Vector3<float>(500, 0, 500));

    map->setTexture(new Texture("media/map-texture.jpg"), new Texture("media/map-detail-texture.jpg")); //ToDo: mover a map
}

void GameState::Input(){

}

void GameState::Update(){
    camera->Move(Screen::Instance()->getIO(), map);
}

void GameState::Render(){

}

void GameState::CleanUp(){

}