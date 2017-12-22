#include "GameState.h"
#include "Game.h"
#include "Human.h"
#include "IA.h"

GameState::GameState() : State() {
    map = new Terrain("media/mapa3-256x256.bmp"); //ToDo: mover a map
    camera = new CameraController(map);
    hud = new Hud();

    //IL PICCOLO SPAGUETTIO
    iaUpdateTimer = 1;

    gamePaused = false;
}

GameState::~GameState() {
    delete camera;
    delete hud;
    delete map;
}

void GameState::Init(){
    map->setTexture(new Texture("media/map-texture.jpg"), new Texture("media/map-detail-texture.jpg")); //ToDo: mover a map

    //Initialize the event system
    //IA Events
    Game::Instance() -> getEvents() -> addEvent(Enumeration::EventType::DeployTroopsIA, IA::deployTroops);
    Game::Instance() -> getEvents() -> addEvent(Enumeration::EventType::RetractTroopsIA, IA::retractTroops);
    Game::Instance() -> getEvents() -> addEvent(Enumeration::EventType::OpenDoorsIA, IA::openDoors);
    Game::Instance() -> getEvents() -> addEvent(Enumeration::EventType::CloseDoorsIA, IA::closeDoors);

    //Human events
    Game::Instance() -> getEvents() -> addEvent(Enumeration::EventType::DeployTroopsHuman, Human::deployTroops);
    Game::Instance() -> getEvents() -> addEvent(Enumeration::EventType::RetractTroopsHuman, Human::retractTroops);
    Game::Instance() -> getEvents() -> addEvent(Enumeration::EventType::OpenDoorsHuman, Human::openDoors);
    Game::Instance() -> getEvents() -> addEvent(Enumeration::EventType::CloseDoorsHuman, Human::closeDoors);

    // Build the main building of IA
    Vector3<float> v = IA::getInstance() -> determinatePositionBuilding();
    IA::getInstance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::MainBuilding, Enumeration::Team::IA);

    //Build the first siderurgy of IA
    v = IA::getInstance() -> determinatePositionBuilding();
    IA::getInstance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::Siderurgy, Enumeration::Team::IA);

    // Build the main building of Human

    v.x = HUMAN_CITY_HALL_X;
    v.z = HUMAN_CITY_HALL_Z; 
    v.y = map -> getY(v.x, v.z);
    Human::getInstance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::MainBuilding, Enumeration::Team::Human);

    //Build the first siderurgy of Human
    v.z = HUMAN_CITY_HALL_Z+100;
    v.y = map -> getY(v.x, v.z);
    Human::getInstance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::Siderurgy, Enumeration::Team::Human);
}

void GameState::Input(){
    //if (gamePaused) {
        hud->getHUDEvents();

        hud ->update();

        camera->Move(Game::Instance()->getIO(), Game::Instance()->getCursor());
        camera->RotateAndInclinate(Game::Instance()->getIO(), Game::Instance()->getCursor());
        camera->Zoom(Game::Instance()->getIO());

        Vector3<float> v = map->getPointCollision(Game::Instance()->getCursor());
        if (Game::Instance()->getIO()->leftMousePressed()){
            Human::getInstance() -> getBuildingManager()->testRaycastCollisions();
            int id = Human::getInstance() -> getBuildingManager() -> getCollisionID();
            if (id != -1){
                hud->showPopup(id);
                /*std::map<int,Building*> *b = Human::getInstance() -> getBuildingManager() -> getBuildings();
                std::map<int,Building*>::iterator it;
                it = b->find(id);
                if (it->second != NULL){
                    //int t = (int)it->second->getType();
                }*/
            }
        }
    //}
}

void GameState::Update(){
    //if (Game::Instance() -> getIO()->keyDown((char)27)) {
        //Escape is pressed
        //gamePaused = !gamePaused;
    //}
    //if (gamePaused) {
        camera->Update(Game::Instance()->getWindow()->getDeltaTime());

        Vector3<float> cam = camera->getCamera()->getCameraPosition();
        Vector3<float> tar = camera->getCamera()->getTargetPosition();

        Human::getInstance() -> getBuildingManager() -> drawBuilding(map);
        Human::getInstance() -> getUnitManager() -> deployTroop(map);

        Human::getInstance() -> getUnitManager() -> updateUnitManager();

        Human::getInstance() -> update();
        IA::getInstance() -> update();
    //}
}

void GameState::Render(){

}

void GameState::CleanUp(){

}

Terrain* GameState::getMap() {
    return map;
}

Hud* GameState::getHud() {
    return hud;
}