#include "GameState.h"
#include "Game.h"

GameState::GameState() : State() {

    gamePaused = false;

    prevWindowWidth = 1280;
    prevWindowHeight = 720;
}

GameState::~GameState() {
    delete camera;
    delete hud;
    delete map;
    delete battleManager;
}

void GameState::init() {
    //ToDo: Quizas la luz, la camara, etc... deberian ir en una cpase Map
    light = new Light(Vector3<float>(8000, 4000, 8000), 10000);

    //Create map
    map = new Terrain("media/mapa3-256x256.bmp");
    //Set map texture
    map -> setTexture(new Texture("media/map-texture.jpg"), new Texture("media/map-detail-texture.jpg"));

    //Init camera controller
    camera = new CameraController(map);

    //Init battle manager
    battleManager = new BattleManager();

    //Init SoundSystem
    hud = new Hud();
    SoundSystem::Instance() -> initSystem();

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
    v.z = HUMAN_CITY_HALL_Z + 200;
    v.y = map -> getY(v.x, v.z);
    Human::getInstance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::Siderurgy, Enumeration::Team::Human);

    Enumeration::UnitType unitData = Enumeration::UnitType::StandardM;
    Human::getInstance() -> getUnitManager() -> createTroop(unitData);
    Game::Instance() -> getEvents() -> triggerEvent(Enumeration::DeployTroopsHuman);

    //Init HUD
    Window::Instance() -> setGUI();
    hud -> setHUDEvents();
}

void GameState::input() {
    //hud -> getHUDEvents();

    hud -> update();

    camera -> Move(Game::Instance() -> getCursor());
    camera -> RotateAndInclinate(Game::Instance() -> getCursor());
    camera -> Zoom(Game::Instance() -> getCursor());

    //Vector3<float> v = map -> getPointCollision(Game::Instance() -> getCursor());
    Human::getInstance() -> getBuildingManager() -> testRaycastCollisions();
    Human::getInstance() -> getUnitManager() -> testRaycastCollisions();

    IA::getInstance() -> getBuildingManager() -> testRaycastCollisions();
    IA::getInstance() -> getUnitManager() -> testRaycastCollisions();

    int onMap = true;

    //Interactions with our entities
    int idBuilding = Human::getInstance() -> getBuildingManager() -> getCollisionID();
    if (idBuilding != -1){
        if (!Human::getInstance() -> getUnitManager() -> isTroopSelected())
            Game::Instance() -> getCursor() -> changeIcon(CURSOR_HAND);
        
        if (Game::Instance() -> getCursor() -> leftMouseDown()) {
            // Comprobar que este terminado para enseñar el popup pero no va
            //if (Human::getInstance() -> getBuildingManager() -> checkFinished(idBuilding)) {
                std::cout << idBuilding << std::endl;
                
                hud -> showPopup(idBuilding);
            //}
        }
        
        onMap = false;
    }

    int idTroop = Human::getInstance() -> getUnitManager() -> getCollisionID();
    if (idTroop != -1){
        if (!Human::getInstance() -> getUnitManager() -> isTroopSelected())
            Game::Instance() -> getCursor() -> changeIcon(CURSOR_HAND);
        
        if (Game::Instance() -> getCursor() -> leftMousePressed())
            Human::getInstance() -> getUnitManager() -> selectTroop(idTroop);
        
        onMap = false;
    }

    //Interactions with IA's entities
    int idBuildingIA =  IA::getInstance() -> getBuildingManager() -> getCollisionID();
    if (idBuildingIA != -1 && Human::getInstance() -> getUnitManager() -> isTroopSelected()){
        Game::Instance() -> getCursor() -> changeIcon(CURSOR_IBEAM); //ToDo: fachada

        if (Game::Instance() -> getCursor() -> rightMousePressed()) //std::cout << "Edificio enemigo" << std::endl;
        
        onMap = false;
    }

    int idTroopIA = IA::getInstance() -> getUnitManager() -> getCollisionID();
    if (idTroopIA != -1 && Human::getInstance() -> getUnitManager() -> isTroopSelected()){
        Game::Instance() -> getCursor() -> changeIcon(CURSOR_IBEAM); //ToDo: fachada

        if (Game::Instance() -> getCursor() -> rightMousePressed()) //std::cout << "Tropa enemiga" << std::endl;
        
        onMap = false;
    }
    
    //If nothing happens
    if (onMap){
        if (Human::getInstance() -> getUnitManager() -> isTroopSelected())
            Game::Instance() -> getCursor() -> changeIcon(CURSOR_CROSSHAIR);
        else 
            Game::Instance() -> getCursor() -> changeIcon(CURSOR_NORMAL);
        
        if (Game::Instance() -> getCursor() -> leftMousePressed())
            Human::getInstance() -> getUnitManager() -> unSelectTroop();
    }
    onMap = false;

    if (Game::Instance() -> getKeyboard() -> keyPressed(GLFW_KEY_ESCAPE)) {
        Game::Instance() -> changeState(Enumeration::State::PauseState);
    }

    if (Game::Instance()-> getCursor() -> rightMousePressed()) {
        Human::getInstance() -> getUnitManager() -> moveOrder(map);
    }
/*
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

void GameState::update(){
    Game *g = Game::Instance();
    camera -> Update(g -> getWindow() -> getDeltaTime());

    Vector3<float> cam = camera -> getCamera() -> getCameraPosition();
    Vector3<float> tar = camera -> getCamera() -> getTargetPosition();

    Human::getInstance() -> getBuildingManager() -> drawBuilding(map);
    Human::getInstance() -> getUnitManager() -> deployTroop(map);

    //Human::getInstance() -> getUnitManager() -> updateUnitManager();

    Human::getInstance() -> update();
    IA::getInstance() -> update();

    //NEW SOUND SYSTEM
    SoundSystem::Instance() -> playMusicEvent("event:/Music/DroraniaMusic");
    SoundSystem::Instance() -> update();

    if (g -> getWindow() -> getRealWindowWidth() != prevWindowWidth || g -> getWindow() -> getRealWindowHeight() != prevWindowHeight) {
        hud -> updatePositions();
    }
}

void GameState::render() {

}

void GameState::cleanUp() {

}

Terrain* GameState::getMap() {
    return map;
}

Hud* GameState::getHud() {
    return hud;
}

BattleManager* GameState::getBattleManager() {
    return battleManager;
}