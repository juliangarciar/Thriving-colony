#include "Map.h"
#include "Game.h"
#include <WorldEngine/WorldGeometry.h>
#include <OBDEngine/ResourceManager/ResourceJSON.h>
#include "Human.h"

#include "IA.h"
#include "IOEngine/IO.h"
#include "GraphicEngine/Window.h"

#include "Map.h"

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
    delete skydome; //Violacion del segmento al borrar.
    delete terrain;
    delete camera;
}

void Map::Init() {
    loadProgress(0);

    ResourceJSON *r = (ResourceJSON*)IO::Instance() -> getResourceManager() -> getResource("media/map/map.json");
    json j = *r -> getJSON();

    loadProgress(5);

    //Create map
    terrain = new Terrain(j["map"]["heightmap"].get<std::string>().c_str());
    //Set map texture
    terrain -> setTexture(new Texture(j["map"]["texture"].get<std::string>().c_str()), new Texture(j["map"]["detail_texture"].get<std::string>().c_str()));
    terrain -> setSize(Vector3<f32>(j["map"]["size"]["x"].get<int>(), j["map"]["size"]["y"].get<int>(), j["map"]["size"]["z"].get<int>()));
    
    loadProgress(20);

    //Luz
    for (auto& element : j["lights"]){
        Vector3<f32> lp;
        lp.x = element["position"]["x"].get<int>();
        lp.z = element["position"]["z"].get<int>();
        lp.y = terrain -> getY(lp.x, lp.z) + element["height"].get<int>();
        Light *light = new Light(lp, element["intensity"].get<int>()); 
        lights.push_back(light);
    }

    loadProgress(30);

    //Hud buttons
    for (auto& element : j["buildables"]){
        Hud::Instance()->setButtonStatus(element["type"].get<std::string>(), element["isBuildable"].get<bool>());
    }
    Hud::Instance()->setButtonStatus("expandableTerrain", j["expandableTerrain"].get<bool>());
    loadProgress(40);

    //ToDo: julian revisa esto, si no tiene nada que sacar del JSON llevatelo a GameState
    //WorldGeometry* newSystem = WorldGeometry::Instance();
    //cellSpace = new CellSpacePartition(10240, 10240, 128, 128, 4);

    //Skydome
    skydome = new SkyDome(new Texture(j["map"]["skybox_texture"].get<std::string>().c_str()));

    loadProgress(50);

    //Human
    Human::Instance()->setMetalAmount(j["player"]["initial_metal"].get<i32>());
    Human::Instance()->setCrystalAmount(j["player"]["initial_crystal"].get<i32>());
    Human::Instance()->setSiderurgyProductivity(j["player"]["siderurgy_productivity"].get<i32>());
    Human::Instance()->setQuarryProductivity(j["player"]["quarry_productivity"].get<i32>());
    Human::Instance()->setBuildingRadious(j["player"]["building_radious"].get<f32>());

    Vector2<f32> humanPosition(j["player"]["mainBuilding"]["position"]["x"], j["player"]["mainBuilding"]["position"]["z"]);
    Human::Instance() -> getBuildingManager() -> createBuilding(humanPosition, "MainBuilding", 0);
    Human::Instance() -> setHallPosition(Vector3<f32>(humanPosition.x, terrain->getY(humanPosition.x, humanPosition.y), humanPosition.y));
    humanStartPos = humanPosition;

    for (auto& element : j["player"]["buildings"]){
        Vector2<f32> v(element["position"]["x"], element["position"]["z"]);
        Human::Instance() -> getBuildingManager() -> createBuilding(v, element["type"].get<std::string>(), 0);
    }

    loadProgress(70);

    //IA
    IA::Instance()->setMetalAmount(j["IA"]["initial_metal"].get<i32>());
    IA::Instance()->setCrystalAmount(j["IA"]["initial_crystal"].get<i32>());
    IA::Instance()->setSiderurgyProductivity(j["IA"]["siderurgy_productivity"].get<i32>());
    IA::Instance()->setQuarryProductivity(j["IA"]["quarry_productivity"].get<i32>());
    IA::Instance()->setBuildingRadious(j["IA"]["building_radious"].get<f32>());

    Vector2<f32> iaPosition(j["IA"]["mainBuilding"]["position"]["x"], j["IA"]["mainBuilding"]["position"]["z"]);
    IA::Instance() -> getBuildingManager() -> createBuilding(iaPosition, "MainBuilding", 0);
    IA::Instance() -> setHallPosition(Vector3<f32>(iaPosition.x, terrain->getY(iaPosition.x, iaPosition.y), iaPosition.y));
    iaStartPos = iaPosition;
    
    for(auto& element : j["IA"]["buildings"]){
        Vector2<f32> iaPosition(element["position"]["x"], element["position"]["z"]);
        IA::Instance() -> getBuildingManager() -> createBuilding(iaPosition, element["type"].get<std::string>(), 0);
    }

    loadProgress(90);

    //Init camera controller
    camera = new CameraController();
    camera -> setZoomDistanceFromTarget(j["camera"]["zoomDistanceFromTarget"].get<int>());
    camera -> setRotateDegrees(j["camera"]["delta_x"].get<int>(), j["camera"]["delta_y"].get<int>());
    camera -> Init(Vector3<f32>(humanStartPos.x, terrain->getY(humanStartPos.x,humanStartPos.y), humanStartPos.y));

    loadProgress(100);
}

void Map::Input() {
    camera -> Move();
    camera -> RotateAndInclinate();
    camera -> Zoom();
    camera -> CenterCamera();

    collisionPoint = terrain->getPointCollision(IO::Instance()->getMouse());
}

void Map::Update(){
    //Update camera
    camera -> Update();
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
    //delete skydome; Violacion del segmento al borrar.
}

Vector2<f32> Map::getHumanStartPosition(){
    return humanStartPos;
}

Vector2<f32> Map::getIAStartPosition(){
    return iaStartPos;
}

Vector3<f32> Map::getMouseCollitionPoint() {
    return collisionPoint;
}

Terrain* Map::getTerrain() {
    return terrain;
}

CameraController* Map::getCamera() {
    return camera;
}

void Map::loadProgress(i32 p){
    std::cout << "Porcentaje de carga del mapa: " << p << "%" << std::endl;
}
