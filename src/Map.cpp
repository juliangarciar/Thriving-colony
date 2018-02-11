#include "Map.h"
#include "Game.h"

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
    //Luz
    light = new Light(Vector3<float>(8000, 4000, 8000), 10000);

    //Create map
    terrain = new Terrain("media/mapa3-256x256.bmp");
    //Set map texture
    terrain -> setTexture(new Texture("media/map-texture.jpg"), new Texture("media/map-detail-texture.jpg"));

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