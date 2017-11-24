#include "GameState.h"
#include "GraphicEngine/Screen.h"

GameState::GameState() : State() {
    camera = new Camera(Screen::Instance()->getSceneManager());
    map = new Terrain("media/heightmap.bmp"); //ToDo: mover a map
    cursor = new Mouse();
}

GameState::~GameState() {
    
}

void GameState::Init(){
    camera->setPosition(Vector3<float>(500, 3000, 500));
    camera->setInclination(Vector2<float>(200, 200));
    camera->setShadowDistance(42000.f);

    map->setTexture(new Texture("media/map-texture.jpg"), new Texture("media/map-detail-texture.jpg")); //ToDo: mover a map
}

void GameState::Input(){

}

void GameState::Update(){
    camera->Move(Screen::Instance()->getIO(), cursor, map);
    Vector3<float> v = map->getPointCollision(cursor);
    std::cout << v.x << " " << v.y << " " << v.z << std::endl;
}

void GameState::Render(){

}

void GameState::CleanUp(){

}