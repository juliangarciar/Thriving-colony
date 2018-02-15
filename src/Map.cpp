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
    ResourceJSON *r = (ResourceJSON*)Game::Instance() -> getResourceManager() -> getResource("media/map/map.json");

    json j = *r -> getJSON();

    //Luz
    light = new Light(Vector3<float>(j["light"][0]["position"]["x"].get<int>(), j["light"][0]["position"]["y"].get<int>(), j["light"][0]["position"]["z"].get<int>()), j["light"][0]["intensity"].get<int>()); 

    //Create map
    terrain = new Terrain(j["map"]["heightmap"].get<std::string>().c_str());
    //Set map texture
    terrain -> setTexture(new Texture(j["map"]["texture"].get<std::string>().c_str()), new Texture(j["map"]["detail_texture"].get<std::string>().c_str()));
    terrain -> setSize(Vector3<f32>(j["map"]["size"]["x"].get<int>(), j["map"]["size"]["y"].get<int>(), j["map"]["size"]["z"].get<int>()));

    //Init camera controller
    camera = new CameraController();
    camera -> setZoomDistanceFromTarget(j["camera"]["zoomDistanceFromTarget"].get<int>());
    camera -> setRotateDegrees(j["camera"]["delta_x"].get<int>(), j["camera"]["delta_y"].get<int>());

    // Added by Julian
    Graph::Instance();
    cellSpace = CellSpacePartition::Instance();
    //cellSpace = new CellSpacePartition(10240, 10240, 128, 128, 4);

    //ToDo: extraer de JSON
    Human::Instance()->setMetalAmount(j["player"]["initial_metal"].get<i32>());
    Human::Instance()->setCrystalAmount(j["player"]["initial_crystal"].get<i32>());
    Human::Instance()->setSiderurgyProductivity(j["player"]["siderurgy_productivity"].get<i32>());
    Human::Instance()->setQuarryProductivity(j["player"]["quarry_productivity"].get<i32>());

    humanStartPos.x = Enumeration::HumanCityHall::human_x;
    humanStartPos.z = Enumeration::HumanCityHall::human_z; 
    humanStartPos.y = terrain -> getY(humanStartPos.x, humanStartPos.z);

    IA::Instance()->setMetalAmount(j["IA"]["initial_metal"].get<i32>());
    IA::Instance()->setCrystalAmount(j["IA"]["initial_crystal"].get<i32>());
    IA::Instance()->setSiderurgyProductivity(j["IA"]["siderurgy_productivity"].get<i32>());
    IA::Instance()->setQuarryProductivity(j["IA"]["quarry_productivity"].get<i32>());
    
    for(auto& element : j["IA"]["buildings"]){
        std::cout << element << '\n';
    }

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