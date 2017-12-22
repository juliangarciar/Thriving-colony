#include "GameState.h"
#include "Game.h"
#include "Human.h"
#include "IA.h"

GameState::GameState() : State() {
    camera = new CameraController();
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
    map = new Terrain("media/mapa3-256x256.bmp"); //ToDo: mover a map
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
    Vector3<float> *v = IA::getInstance() -> determinatePositionBuilding();
    IA::getInstance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::MainBuilding, Enumeration::Team::IA);

    //Build the first siderurgy of IA
    v = IA::getInstance() -> determinatePositionBuilding();
    IA::getInstance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::Siderurgy, Enumeration::Team::IA);

    // Build the main building of Human

    /*
    float startingX = 4000;
    float startingZ = 4000;
    Vector3<float> *v2 = new Vector3<float>(startingX, 0, startingZ);
    v2 -> y = Game::Instance() -> getGameState() ->getMap() -> getY(v2 -> x, v2 -> z);*/
    Human::getInstance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::MainBuilding, Enumeration::Team::Human);

    //Build the first siderurgy of Human
    /*
    v = new Vector3<float>(startingX + 100, 0, startingZ);
    v -> y = Game::Instance() -> getGameState() ->getMap() -> getY(v -> x, v -> z);*/
    //Human::getInstance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::Siderurgy, Enumeration::Team::Human);
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
        camera->Update(map, Game::Instance()->getWindow()->getDeltaTime());

        Vector3<float> cam = camera->getCamera()->getCameraPosition();
        Vector3<float> tar = camera->getCamera()->getTargetPosition();

        Human::getInstance() -> getBuildingManager() -> drawBuilding(map);
        Human::getInstance() -> getUnitManager() -> deployTroop(map);

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