#include "GameState.h"
#include "Game.h"

GameState::GameState() : State() {
    gamePaused = false;

    prevWindowWidth = 1280;
    prevWindowHeight = 720;
}

GameState::~GameState() {
    delete camera;
    delete map;
    delete hud;
    delete battleManager;
}

void GameState::Init() {
    //ToDo: la luz, terreno, y quizas la camara deberian ir en una clase Map
    light = new Light(Vector3<float>(8000, 4000, 8000), 10000);

    //Create map
    map = new Terrain("media/mapa3-256x256.bmp");
    //Set map texture
    map -> setTexture(new Texture("media/map-texture.jpg"), new Texture("media/map-detail-texture.jpg"));

    //Init camera controller
    camera = new CameraController();

    //Init HUD
    hud = new Hud();
    hud -> setHUDEvents();
    Window::Instance() -> setGUI();

    //Init battle manager
    battleManager = new BattleManager();

    //Init SoundSystem
    SoundSystem::Instance() -> initSystem();

    // Build the main building of IA
    Vector3<float> v = IA::getInstance() -> determinatePositionBuilding();
    IA::getInstance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::MainBuilding, true);

    //Build the first siderurgy of IA
    v = IA::getInstance() -> determinatePositionBuilding();
    IA::getInstance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::Siderurgy, true);

    // Build the main building of Human
    v.x = Enumeration::HumanCityHall::human_x;
    v.z = Enumeration::HumanCityHall::human_z; 
    v.y = map -> getY(v.x, v.z);
    Human::getInstance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::MainBuilding, true);
    
    //Build the first siderurgy of Human
    v.x = Enumeration::HumanCityHall::human_x;
    v.z = Enumeration::HumanCityHall::human_z + 200;
    v.y = map -> getY(v.x, v.z);
    Human::getInstance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::Siderurgy, true);
}

void GameState::Input() {
    camera -> Move();
    camera -> RotateAndInclinate();
    camera -> Zoom();
    camera -> CenterCamera();

    //Vector3<float> v = map -> getPointCollision(Game::Instance() -> getMouse());
    Human::getInstance() -> getBuildingManager() -> testRaycastCollisions();
    Human::getInstance() -> getUnitManager() -> testRaycastCollisions();

    IA::getInstance() -> getBuildingManager() -> testRaycastCollisions();
    IA::getInstance() -> getUnitManager() -> testRaycastCollisions();

    int onMap = true;

    //Interactions with our entities
    int idBuilding = Human::getInstance() -> getBuildingManager() -> getCollisionID();
    if (idBuilding != -1){
        if (!Human::getInstance() -> getUnitManager() -> isTroopSelected())
            Game::Instance() -> getMouse() -> changeIcon(CURSOR_HAND);
        
        if (Game::Instance() -> getMouse() -> leftMousePressed()) {
            Building *b = Human::getInstance()->getBuildingManager()->getBuilding(idBuilding);
            if (b != NULL){
                // Comprobar que este terminado para enseñar el popup pero no va
                if (Human::getInstance() -> getBuildingManager() -> checkFinished(idBuilding)) {
                    hud -> showPopup(b->getType());
                }
            }
        }
        
        onMap = false;
    }

    int idTroop = Human::getInstance() -> getUnitManager() -> getCollisionID();
    if (idTroop != -1){
        if (!Human::getInstance() -> getUnitManager() -> isTroopSelected())
            Game::Instance() -> getMouse() -> changeIcon(CURSOR_HAND);
        
        if (Game::Instance() -> getMouse() -> leftMousePressed())
            Human::getInstance() -> getUnitManager() -> selectTroop(idTroop);
        
        onMap = false;
    }

    //Interactions with IA's entities
    int idBuildingIA =  IA::getInstance() -> getBuildingManager() -> getCollisionID();
    if (idBuildingIA != -1 && Human::getInstance() -> getUnitManager() -> isTroopSelected()){
        Game::Instance() -> getMouse() -> changeIcon(CURSOR_IBEAM);

        if (Game::Instance() -> getMouse() -> rightMousePressed())
        
        onMap = false;
    }

    int idTroopIA = IA::getInstance() -> getUnitManager() -> getCollisionID();
    if (idTroopIA != -1 && Human::getInstance() -> getUnitManager() -> isTroopSelected()){
        Game::Instance() -> getMouse() -> changeIcon(CURSOR_IBEAM);

        if (Game::Instance() -> getMouse() -> rightMousePressed())
        
        onMap = false;
    }
    
    //If nothing happens
    if (onMap){
        if (Human::getInstance() -> getUnitManager() -> isTroopSelected())
            Game::Instance() -> getMouse() -> changeIcon(CURSOR_CROSSHAIR);
        else 
            Game::Instance() -> getMouse() -> changeIcon(CURSOR_NORMAL);
        
        if (Game::Instance() -> getMouse() -> leftMousePressed())
            Human::getInstance() -> getUnitManager() -> unSelectTroop();
    }
    onMap = false;

    if (Game::Instance() -> getKeyboard() -> keyPressed(GLFW_KEY_ESCAPE)) {
        Game::Instance() -> changeState(Enumeration::State::PauseState);
    }

    if (Game::Instance()-> getMouse() -> rightMousePressed()) {
        Human::getInstance() -> getUnitManager() -> moveOrder();
    }
/*  //Hacks
    if (Game::Instance() -> getIO() -> keyPressed(KEY_KEY_1)) {
        Human::getInstance() -> receiveMetal();
    }

    if (Game::Instance() -> getIO() -> keyPressed(KEY_KEY_2)) {
        Human::getInstance() -> receiveCrystal();
    }

    if (Game::Instance() -> getIO() -> keyPressed(KEY_KEY_3)) {
        Human::getInstance() -> receiveCitizens();
    }*/   
}

void GameState::Update(){
    Game *g = Game::Instance();

    //Update camera
    camera -> Update(g -> getWindow() -> getDeltaTime());
    
    //Update HUD
    hud -> update();

    //NEW SOUND SYSTEM
    SoundSystem::Instance() -> playMusicEvent("event:/Music/DroraniaMusic");
    SoundSystem::Instance() -> update();
    
    //If human is building something
    Human::getInstance() -> getBuildingManager() -> drawBuilding();
    Human::getInstance() -> getUnitManager() -> deployTroop();
    //Human::getInstance() -> getUnitManager() -> updateUnitManager();

    //Update human and IA status
    Human::getInstance() -> update();
    IA::getInstance() -> update();

    //ToDo: glfw tiene un evento para si se redimensiona la pantalla
    if (g -> getWindow() -> getRealWindowWidth() != prevWindowWidth || g -> getWindow() -> getRealWindowHeight() != prevWindowHeight) {
        hud -> updatePositions();
    }
}

void GameState::Render() {

}

void GameState::CleanUp() {

}

Terrain* GameState::getTerrain() {
    return map;
}

Hud* GameState::getHud() {
    return hud;
}

BattleManager* GameState::getBattleManager() {
    return battleManager;
}