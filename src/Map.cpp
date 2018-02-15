#include "Map.h"
#include "Game.h"

//Para cargar el json:
//desde aqui
#include <iostream>
#include <fstream>
#include <json/json.hpp>

using json = nlohmann::json;
//hasta aqui

Map* Map::pinstance = 0;

Map* Map::Instance() {
    if (pinstance == 0) {
        pinstance = new Map();
    }
    return pinstance;
}

Map::Map() {
}

Map::~Map() {
}

void Map::Init() {
    //Cargar json
    json j;

    try{
        std::ifstream i;
        i.open("media/map/map.json");
        i >> j;
        i.close();
    }
    catch(std::ifstream::failure e){
        std::cout<<"ACHO LA'S LIAO"<<std::endl;
        exit(0);
    }

    //Luz
    light = new Light(Vector3<float>(8000, 4000, 8000), 10000);

    //Create map
    terrain = new Terrain(j["map"]["heightmap"].get<std::string>().c_str());
    //Set map texture
    terrain -> setTexture(new Texture(j["map"]["texture"].get<std::string>().c_str()), new Texture(j["map"]["detail_texture"].get<std::string>().c_str()));

    //Init camera controller
    camera = new CameraController();

    // Added by Julian
    Graph::Instance();
    cellSpace = CellSpacePartition::Instance();
    //cellSpace = new CellSpacePartition(10240, 10240, 128, 128, 4);

    //ToDo: extraer de JSON
    humanStartPos.x = Enumeration::HumanCityHall::human_x;
    humanStartPos.z = Enumeration::HumanCityHall::human_z; 
    humanStartPos.y = terrain -> getY(humanStartPos.x, humanStartPos.z);
    
    iaStartPos.x = Enumeration::IACityHall::ia_x;
    iaStartPos.z = Enumeration::IACityHall::ia_z; 
    iaStartPos.y = terrain -> getY(iaStartPos.x, iaStartPos.z);
}

void Map::Input() {
    camera -> Move();
    camera -> RotateAndInclinate();
    camera -> Zoom();
    camera -> CenterCamera();

    collisionPoint = terrain->getPointCollision(Game::Instance()->getMouse());
}

void Map::Update(){
    //Update camera
    camera -> Update(Game::Instance() -> getWindow() -> getDeltaTime());
}

void Map::Render() {

}

void Map::CleanUp() {
    delete light;
    delete terrain;
    delete camera;
}

Vector3<f32> Map::getHumanStartPosition(){
    return humanStartPos;
}

Vector3<f32> Map::getIAStartPosition(){
    return iaStartPos;
}

Vector3<f32> Map::getMouseCollitionPoint() {
    return collisionPoint;
}

Terrain* Map::getTerrain() {
    return terrain;
}

CellSpacePartition *Map::getCellSpace(){
    return cellSpace;
}