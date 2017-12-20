#include "GameState.h"
#include "Game.h"
#include "Human.h"
#include "IA.h"

GameState::GameState() : State() {
    camera = new CameraController();
    map = new Terrain("media/mapa3-256x256.bmp"); //ToDo: mover a map
    hud = new Hud();

    //IL PICCOLO SPAGUETTIO
    iaUpdateTimer = 1;
    nodeRootIA = new RootNode();

    gamePaused = false;
}

GameState::~GameState() {
    delete nodeRootIA;
    delete camera;
    delete hud;
    delete map;
}

void GameState::Init(){
    map->setTexture(new Texture("media/map-texture.jpg"), new Texture("media/map-detail-texture.jpg")); //ToDo: mover a map
    
    // Build the main building of IA
    Vector3<float> *v = IA::getInstance() -> determinatePositionBuilding();
    IA::getInstance() -> getBuildings() -> buildBuilding(v, Enumeration::BuildingType::MainBuilding, Enumeration::Team::IA);

    //Build the first siderurgy of IA
    v = IA::getInstance() -> determinatePositionBuilding();
    IA::getInstance() -> getBuildings() -> buildBuilding(v, Enumeration::BuildingType::Siderurgy, Enumeration::Team::IA);
}

void GameState::Input(){
    //if (gamePaused) {
        hud->getHUDEvents();

        camera->Move(Game::Instance()->getIO(), Game::Instance()->getCursor());
        camera->RotateAndInclinate(Game::Instance()->getIO(), Game::Instance()->getCursor());
        camera->Zoom(Game::Instance()->getIO());

        Vector3<float> v = map->getPointCollision(Game::Instance()->getCursor());
        if (Game::Instance()->getIO()->leftMousePressed()){
            int id = Human::getInstance() -> getBuildings()->getHoverBuilding();
            if (id != -1){
            /* std::wstringstream o;
                o << "Has hecho click en: " << id;
                hud->getInfoButton()->setText(o.str().c_str());*/
                hud->showPopup(id);
            }
        }
    //}
}

void GameState::Update(){
    /*if (Game::Instance() -> getIO()->keyDown((char)27)) {
        // El getKeyDown es el unico que va y va a la virule
        //Escape is pressed
        gamePaused = !gamePaused;
    }
    if (gamePaused) {*/
        camera->Update(map, Game::Instance()->getWindow()->getDeltaTime());

        Vector3<float> cam = camera->getCamera()->getCameraPosition();
        Vector3<float> tar = camera->getCamera()->getTargetPosition();

        //buildingManager->drawCube(map);

        Human::getInstance() -> getBuildings() -> drawBuilding(map, Enumeration::BuildingType::House,  Enumeration::Team::Human);
        if(!unitDone){
            Vector3<float> *vectorData = new Vector3<float>(200, 200, 200);
            Enumeration::UnitType unitData;
            unitData.unitClass = Enumeration::UnitType::Class::Ranged;
            unitData.unitSubClass = Enumeration::UnitType::SubClass::StandardR;
            Human::getInstance()->getUnits()->createTroop(vectorData, unitData);
            this->unitDone = true;
        }
        Human::getInstance() -> update();
        IA::getInstance() -> update();
        
        // ESTO VA EN EL UPDATE DE LA IA, PERO SI ME PONGO A CAMBIARLO DA ERRORES DE LINKADO
        // ASI QUE LO VOY A DEJAR ASI QUE FUNCIONA Y YA SE VERA QUE PASA CON LA PICCOLA ITALIA
        // HOGAR DEL SPAGUETIO
        if (iaUpdateTimer <= 0) {
            nodeRootIA -> question();
            iaUpdateTimer = 1;
        } else {
            iaUpdateTimer -= Window::Instance() -> getDeltaTime();
        }
    //}
}

void GameState::Render(){

}

void GameState::CleanUp(){

}

Terrain* GameState::getMap() {
    return map;
}