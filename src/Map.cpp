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
    delete skybox;
    delete terrain;
    delete camera;
}

void Map::Init() {
    loadProgress(0);

    ResourceJSON *r = (ResourceJSON*)IO::Instance() -> getResourceManager() -> getResource("media/maps/test_map/map.json", true);
    json j = *r -> getJSON();

    loadProgress(5);

    //Skybox
    skybox = new Skybox(j["map"]["skybox_textures"].get< std::vector<std::string> >());

    loadProgress(10);

    //Luz
    for (auto& element : j["lights"]) {
        Vector3<f32> lp;
        lp.x = element["position"]["x"].get<i32>();
        lp.y = element["position"]["y"].get<i32>();
        lp.z = element["position"]["z"].get<i32>();
        Light *light = new Light(lp, Color(element["color"]["r"].get<f32>(), element["color"]["g"].get<f32>(), element["color"]["b"].get<f32>()), element["intensity"].get<i32>());
    }

    loadProgress(15);

    //Create map
    terrain = new Terrain(j["map"]["heightmap"].get<std::string>().c_str());
    terrain -> setTexture(new Texture(j["map"]["texture"].get<std::string>().c_str()), new Texture(j["map"]["detail_texture"].get<std::string>().c_str()));
    terrain -> setSize(Vector3<f32>(j["map"]["scale"]["x"].get<int>(), j["map"]["scale"]["y"].get<int>(), j["map"]["scale"]["z"].get<int>()));
	mapMargins = new Margins();
	mapMargins->top = j["map"]["margins"]["top"].get<int>();
	mapMargins->right = j["map"]["margins"]["right"].get<int>();
	mapMargins->bottom = j["map"]["margins"]["bottom"].get<int>();
	mapMargins->left = j["map"]["margins"]["left"].get<int>();
    WorldGeometry::Instance() -> Init(cSize, i32(j["map"]["size"]["width"].get<int>()), i32(j["map"]["size"]["height"].get<int>()), cDepth);

    loadProgress(35);

    //Hud buttons
    for (auto& element : j["buildables"]) {
        Hud::Instance()->setButtonStatus(element["type"].get<std::string>(), element["isBuildable"].get<bool>());
    }
    Hud::Instance()->setButtonStatus("expandableTerrain", j["expandableTerrain"].get<bool>());
    
	loadProgress(40);

    //Game productivity
    metalProductivity = j["game"]["metal_productivity"].get<i32>();
    crystalProductivity = j["game"]["crystal_productivity"].get<i32>();
	influenceRangeIncrement = j["game"]["expansion_increment"].get<i32>();
	influenceRangeIncrementLimit = j["game"]["expansion_increment_times"].get<i32>();
	citizenIncrement = j["game"]["citizen_increment"].get<i32>();
	
	loadProgress(50);

    //Human
    Human::Instance() -> metalAmount = j["player"]["initial_metal"].get<i32>();
    Human::Instance() -> crystalAmount = j["player"]["initial_crystal"].get<i32>();
    Human::Instance() -> buildableRange = j["player"]["building_radius"].get<f32>();

    Vector2<f32> humanPosition(j["player"]["mainBuilding"]["position"]["x"], j["player"]["mainBuilding"]["position"]["z"]);
    Human::Instance() -> getBuildingManager() -> createBuilding(humanPosition, "MainBuilding", 0);
    Human::Instance() -> hallPosition = Vector3<f32>(humanPosition.x, terrain->getY(humanPosition.x, humanPosition.y), humanPosition.y);
    humanStartPos = humanPosition;

    for (auto& element : j["player"]["buildings"]) {
        Vector2<f32> v(element["position"]["x"], element["position"]["z"]);
        Human::Instance() -> getBuildingManager() -> createBuilding(v, element["type"].get<std::string>(), 0);
    }

    loadProgress(70);

    //IA
    IA::Instance() -> metalAmount = j["IA"]["initial_metal"].get<i32>();
    IA::Instance() -> crystalAmount = j["IA"]["initial_crystal"].get<i32>();
    IA::Instance() -> buildableRange = j["IA"]["building_radius"].get<f32>();

    Vector2<f32> iaPosition(j["IA"]["mainBuilding"]["position"]["x"], j["IA"]["mainBuilding"]["position"]["z"]);
    IA::Instance() -> getBuildingManager() -> createBuilding(iaPosition, "MainBuilding", 0);
    IA::Instance() -> hallPosition = Vector3<f32>(iaPosition.x, terrain->getY(iaPosition.x, iaPosition.y), iaPosition.y);
    iaStartPos = iaPosition;
    
    for (auto& element : j["IA"]["buildings"]) {
        Vector2<f32> iaPosition(element["position"]["x"], element["position"]["z"]);
        IA::Instance() -> getBuildingManager() -> createBuilding(iaPosition, element["type"].get<std::string>(), 0);
    }

    loadProgress(90);

    //Init camera controller
    camera = new CameraController();
	camera -> minZoom = j["camera"]["zoom"]["min"].get<int>();
	camera -> maxZoom = j["camera"]["zoom"]["max"].get<int>();
	camera -> zoomDistanceFromTarget = j["camera"]["zoom"]["initialDistanceFromTarget"].get<int>();
	camera -> minInclination = j["camera"]["rotation"]["min_inclination"].get<int>();
	camera -> maxInclination = j["camera"]["rotation"]["max_inclination"].get<int>();
	camera -> rotateDegrees = Vector2<f32>(j["camera"]["rotation"]["initialRotation"]["x"].get<int>(), j["camera"]["rotation"]["initialRotation"]["y"].get<int>());
    camera -> Init(Vector3<f32>(humanStartPos.x, terrain->getY(humanStartPos.x,humanStartPos.y), humanStartPos.y));

    loadProgress(100);
}

void Map::Input() {
    camera -> Move();
    camera -> RotateAndInclinate();
    camera -> Zoom();
    camera -> CenterCamera();

    collisionPoint = terrain->getPointCollision(IO::Instance()->getMouse()->getPosition());
}

void Map::Update() {
	
}

void Map::Render() {

}

void Map::CleanUp() {
    for (i32 i=0; i<lights.size(); i++) {
        delete lights[i];
    }
    lights.clear();
    delete terrain;
    delete camera;
    //delete skydome;
	delete skybox;
}

Vector2<f32> Map::getHumanStartPosition() {
    return humanStartPos;
}

Vector2<f32> Map::getIAStartPosition() {
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

Margins *Map::getMapMargins() {
	return mapMargins;
}

i32 Map::getMetalProductivity() {
	return metalProductivity;
}

i32 Map::getCrystalProductivity() {
	return crystalProductivity;
}

i32 Map::getCitizenIncrement() {
	return citizenIncrement;
}

i32 Map::getInfluenceRangeIncrement() {
	return influenceRangeIncrement;
}

i32 Map::getInfluenceRangeIncrementLimit() {
	return influenceRangeIncrementLimit;
}

void Map::loadProgress(i32 p) {
    std::cout << "Porcentaje de carga del mapa: " << p << "%" << std::endl;
}
