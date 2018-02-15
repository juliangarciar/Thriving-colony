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

    //Create map
    terrain = new Terrain(j["map"]["heightmap"].get<std::string>().c_str());
    //Set map texture
    terrain -> setTexture(new Texture(j["map"]["texture"].get<std::string>().c_str()), new Texture(j["map"]["detail_texture"].get<std::string>().c_str()));
    terrain -> setSize(Vector3<f32>(j["map"]["size"]["x"].get<int>(), j["map"]["size"]["y"].get<int>(), j["map"]["size"]["z"].get<int>()));
    
    //Luz
    for (auto& element : j["lights"]){
        Vector3<f32> lp;
        lp.x = element["position"]["x"].get<int>();
        lp.z = element["position"]["z"].get<int>();
        lp.y = terrain -> getY(lp.x, lp.z) + element["height"].get<int>();
        Light *light = new Light(lp, element["intensity"].get<int>()); 
        lights.push_back(light);
    }

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

    for (auto& element : j["player"]["buildings"]){
        if(element["type"].get<std::string>()=="MainBuilding"){
            Vector3<f32> v(element["position"]["x"], terrain -> getY(element["position"]["x"], element["position"]["z"]), element["position"]["z"]);
            Human::Instance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::MainBuilding, true);
            Human::Instance() -> setHallPosition(v);
            humanStartPos = v;
        }
        else if(element["type"].get<std::string>()=="Siderurgy"){
            Vector3<f32> v(element["position"]["x"], terrain -> getY(element["position"]["x"], element["position"]["z"]), element["position"]["z"]);
            Human::Instance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::Siderurgy, true);
        }
    }

    IA::Instance()->setMetalAmount(j["IA"]["initial_metal"].get<i32>());
    IA::Instance()->setCrystalAmount(j["IA"]["initial_crystal"].get<i32>());
    IA::Instance()->setSiderurgyProductivity(j["IA"]["siderurgy_productivity"].get<i32>());
    IA::Instance()->setQuarryProductivity(j["IA"]["quarry_productivity"].get<i32>());
    
    for(auto& element : j["IA"]["buildings"]){
        if(element["type"].get<std::string>()=="MainBuilding"){
            Vector3<f32> v(element["position"]["x"], terrain -> getY(element["position"]["x"], element["position"]["z"]), element["position"]["z"]);
            IA::Instance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::MainBuilding, true);
            IA::Instance() -> setHallPosition(v);
            iaStartPos = v;
        }
        else if(element["type"].get<std::string>()=="Siderurgy"){
            Vector3<f32> v(element["position"]["x"], terrain -> getY(element["position"]["x"], element["position"]["z"]), element["position"]["z"]);
            IA::Instance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::Siderurgy, true);
        }
    }
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
    for(int i=0; i<lights.size(); i++){
        delete lights[i];
    }
    lights.clear();
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