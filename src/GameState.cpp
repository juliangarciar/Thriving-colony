#include "GameState.h"
#include "Game.h"

GameState::GameState() : State() {
    map = new Terrain("media/mapa3-256x256.bmp"); //ToDo: mover a map
    camera = new CameraController(map);

    gamePaused = false;
    battleManager = new BattleManager();
    
    hud = new Hud();

    Window::Instance() -> setGUI();

    prevWindowWidth = 1280;
    prevWindowHeight = 720;
}

GameState::~GameState() {
    delete camera;
    delete hud;
    delete map;
    delete battleManager;
}

void GameState::Init() {
    //Set map texture
    map -> setTexture(new Texture("media/map-texture.jpg"), new Texture("media/map-detail-texture.jpg")); //ToDo: mover a map

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

    //Hud events
    Game::Instance() -> getEvents() -> addEvent(Enumeration::EventType::EnableText, Hud::drawWarning);
    Game::Instance() -> getEvents() -> addEvent(Enumeration::EventType::DisableText, Hud::deleteWarning);

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

    //SoundSystem init
    SoundSystem::Instance() -> initSystem();

    hud -> setHUDEvents();
}

void GameState::Input() {
    //if (gamePaused) {

        hud -> update();

        Game::Instance() -> getCursor();

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
                Game::Instance() -> getCursor() -> changeIcon(CURSOR_HAND); //ToDo: fachada
            
            if (Game::Instance() -> getCursor() -> leftMousePressed()) {
                // Comprobar que este terminado para enseñar el popup pero no va
                //if (Human::getInstance() -> getBuildingManager() -> checkFinished(idBuilding)) {
                    hud -> showPopup(idBuilding);
                //}
            }
            
            onMap = false;
        }

        int idTroop = Human::getInstance() -> getUnitManager() -> getCollisionID();
        if (idTroop != -1){
            if (!Human::getInstance() -> getUnitManager() -> isTroopSelected())
                Game::Instance() -> getCursor() -> changeIcon(CURSOR_HAND); //ToDo: fachada
            
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

        if (Game::Instance() -> getCursor() -> rightMousePressed()){
            Human::getInstance() -> getUnitManager() -> moveOrder(map);
        }

        if (Game::Instance() -> getKeyboard() -> keyPressed(GLFW_KEY_1)){ //ToDo: fachada
           // Human::getInstance() -> receiveMetal();
        }

        if (Game::Instance() -> getKeyboard() -> keyPressed(GLFW_KEY_2)){ //ToDo: fachada
            //Human::getInstance() -> receiveCrystal();
        }

        if (Game::Instance() -> getKeyboard() -> keyPressed(GLFW_KEY_3)){ //ToDo: fachada
            //Human::getInstance() -> receiveCitizens();
        }
}

void GameState::Update() {
    Game *g = Game::Instance();
    //if (Game::Instance() -> getCursor() -> keyDown((char)27)) {
        //Escape is pressed
        //gamePaused = !gamePaused;
    //}
    //if (gamePaused) {
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
    //}
}

void GameState::Render() {

}

void GameState::CleanUp() {

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