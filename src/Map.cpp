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
}

void Map::Init() {
    ResourceJSON *r = (ResourceJSON*)IO::Instance() -> getResourceManager() -> getResource("media/map/map.json");

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
        else if(element["type"].get<std::string>()=="Quarry"){
            Vector3<f32> v(element["position"]["x"], terrain -> getY(element["position"]["x"], element["position"]["z"]), element["position"]["z"]);
            Human::Instance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::Quarry, true);
        }
        else if(element["type"].get<std::string>()=="Barn"){
            Vector3<f32> v(element["position"]["x"], terrain -> getY(element["position"]["x"], element["position"]["z"]), element["position"]["z"]);
            Human::Instance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::Barn, true);
        }
        else if(element["type"].get<std::string>()=="Barrack"){
            Vector3<f32> v(element["position"]["x"], terrain -> getY(element["position"]["x"], element["position"]["z"]), element["position"]["z"]);
            Human::Instance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::Barrack, true);
        }
        else if(element["type"].get<std::string>()=="Hospital"){
            Vector3<f32> v(element["position"]["x"], terrain -> getY(element["position"]["x"], element["position"]["z"]), element["position"]["z"]);
            Human::Instance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::Hospital, true);
        }
        else if(element["type"].get<std::string>()=="Hospital"){
            Vector3<f32> v(element["position"]["x"], terrain -> getY(element["position"]["x"], element["position"]["z"]), element["position"]["z"]);
            Human::Instance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::Hospital, true);
        }
        else if(element["type"].get<std::string>()=="Market"){
            Vector3<f32> v(element["position"]["x"], terrain -> getY(element["position"]["x"], element["position"]["z"]), element["position"]["z"]);
            Human::Instance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::Market, true);
        }
        else if(element["type"].get<std::string>()=="School"){
            Vector3<f32> v(element["position"]["x"], terrain -> getY(element["position"]["x"], element["position"]["z"]), element["position"]["z"]);
            Human::Instance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::School, true);
        }
        else if(element["type"].get<std::string>()=="Tower"){
            Vector3<f32> v(element["position"]["x"], terrain -> getY(element["position"]["x"], element["position"]["z"]), element["position"]["z"]);
            Human::Instance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::Tower, true);
        }
        else if(element["type"].get<std::string>()=="Wall"){
            Vector3<f32> v(element["position"]["x"], terrain -> getY(element["position"]["x"], element["position"]["z"]), element["position"]["z"]);
            Human::Instance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::Wall, true);
        }
        else if(element["type"].get<std::string>()=="Workshop"){
            Vector3<f32> v(element["position"]["x"], terrain -> getY(element["position"]["x"], element["position"]["z"]), element["position"]["z"]);
            Human::Instance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::Workshop, true);
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
        else if(element["type"].get<std::string>()=="Quarry"){
            Vector3<f32> v(element["position"]["x"], terrain -> getY(element["position"]["x"], element["position"]["z"]), element["position"]["z"]);
            IA::Instance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::Quarry, true);
        }
        else if(element["type"].get<std::string>()=="Barn"){
            Vector3<f32> v(element["position"]["x"], terrain -> getY(element["position"]["x"], element["position"]["z"]), element["position"]["z"]);
            IA::Instance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::Barn, true);
        }
        else if(element["type"].get<std::string>()=="Barrack"){
            Vector3<f32> v(element["position"]["x"], terrain -> getY(element["position"]["x"], element["position"]["z"]), element["position"]["z"]);
            IA::Instance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::Barrack, true);
        }
        else if(element["type"].get<std::string>()=="Hospital"){
            Vector3<f32> v(element["position"]["x"], terrain -> getY(element["position"]["x"], element["position"]["z"]), element["position"]["z"]);
            IA::Instance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::Hospital, true);
        }
        else if(element["type"].get<std::string>()=="Hospital"){
            Vector3<f32> v(element["position"]["x"], terrain -> getY(element["position"]["x"], element["position"]["z"]), element["position"]["z"]);
            IA::Instance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::Hospital, true);
        }
        else if(element["type"].get<std::string>()=="Market"){
            Vector3<f32> v(element["position"]["x"], terrain -> getY(element["position"]["x"], element["position"]["z"]), element["position"]["z"]);
            IA::Instance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::Market, true);
        }
        else if(element["type"].get<std::string>()=="School"){
            Vector3<f32> v(element["position"]["x"], terrain -> getY(element["position"]["x"], element["position"]["z"]), element["position"]["z"]);
            IA::Instance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::School, true);
        }
        else if(element["type"].get<std::string>()=="Tower"){
            Vector3<f32> v(element["position"]["x"], terrain -> getY(element["position"]["x"], element["position"]["z"]), element["position"]["z"]);
            IA::Instance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::Tower, true);
        }
        else if(element["type"].get<std::string>()=="Wall"){
            Vector3<f32> v(element["position"]["x"], terrain -> getY(element["position"]["x"], element["position"]["z"]), element["position"]["z"]);
            IA::Instance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::Wall, true);
        }
        else if(element["type"].get<std::string>()=="Workshop"){
            Vector3<f32> v(element["position"]["x"], terrain -> getY(element["position"]["x"], element["position"]["z"]), element["position"]["z"]);
            IA::Instance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::Workshop, true);
        }
    }

    //Init camera controller
    camera = new CameraController();
    camera -> setZoomDistanceFromTarget(j["camera"]["zoomDistanceFromTarget"].get<int>());
    camera -> setRotateDegrees(j["camera"]["delta_x"].get<int>(), j["camera"]["delta_y"].get<int>());
    camera -> Init(Human::Instance() -> getHallPosition());
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
    camera -> Update(Window::Instance() -> getDeltaTime());
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

CameraController* Map::getCamera() {
    return camera;
}