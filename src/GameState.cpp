#include "GameState.h"
#include "Game.h"

GameState::GameState() : State() {
    prevWindowWidth = 1280;
    prevWindowHeight = 720;
}

GameState::~GameState() {
}

void GameState::Init() {
    IA::Instance() -> Init();
    Human::Instance() -> Init();

    gamePaused = false;

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
    hud -> Init();

    //Init battle manager
    battleManager = new BattleManager();

    //Init SoundSystem
    SoundSystem::Instance() -> initSystem();

    // Build the main building of IA
    Vector3<float> v = IA::Instance() -> determinatePositionBuilding();
    IA::Instance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::MainBuilding, true);
    IA::Instance() -> setHallPosition(v);

    //Build the first siderurgy of IA
    v = IA::Instance() -> determinatePositionBuilding();
    IA::Instance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::Siderurgy, true);

    // Build the main building of Human
    v.x = Enumeration::HumanCityHall::human_x;
    v.z = Enumeration::HumanCityHall::human_z; 
    v.y = map -> getY(v.x, v.z);
    Human::Instance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::MainBuilding, true);
    Human::Instance() -> setHallPosition(v);
    
    //Build the first siderurgy of Human
    v.x = Enumeration::HumanCityHall::human_x;
    v.z = Enumeration::HumanCityHall::human_z + 200;
    v.y = map -> getY(v.x, v.z);
    Human::Instance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::Siderurgy, true);
}

void GameState::Input() {
    if(gamePaused ==  false){
        camera -> Move();
        camera -> RotateAndInclinate();
        camera -> Zoom();
        camera -> CenterCamera();

        if (!hud->getPopUpOpen()){
            Human::Instance() -> getBuildingManager() -> testRaycastCollisions();
            Human::Instance() -> getUnitManager() -> testRaycastCollisions();

            IA::Instance() -> getBuildingManager() -> testRaycastCollisions();
            IA::Instance() -> getUnitManager() -> testRaycastCollisions();

            Vector3<f32> mapCollision = map->getPointCollision(Game::Instance()->getMouse());

            i32 onMap = true;

            //Interactions with our entities
            i32 idBuilding = Human::Instance() -> getBuildingManager() -> getCollisionID();
            if (idBuilding != -1){
                if (!Human::Instance() -> getUnitManager() -> isTroopSelected())
                    Game::Instance() -> getMouse() -> changeIcon(CURSOR_HAND);
                
                if (Game::Instance() -> getMouse() -> leftMousePressed()) {
                    Building *b = Human::Instance()->getBuildingManager()->getBuilding(idBuilding);
                    if (b != NULL){
                        if (Human::Instance() -> getBuildingManager() -> checkFinished(idBuilding)) {
                            hud -> showPopup(b->getType());
                        }
                    }
                }
                
                onMap = false;
            }

            i32 idTroop = Human::Instance() -> getUnitManager() -> getCollisionID();
            if (idTroop != -1){
                if (!Human::Instance() -> getUnitManager() -> isTroopSelected())
                    Game::Instance() -> getMouse() -> changeIcon(CURSOR_HAND);
                
                if (Game::Instance() -> getMouse() -> leftMousePressed()){
                    Game::Instance() -> getMouse() -> changeIcon(CURSOR_CROSSHAIR);
                    Human::Instance() -> getUnitManager() -> selectTroop(idTroop);
                }
                
                onMap = false;
            }

            //Interactions with IA's entities
            i32 idBuildingIA =  IA::Instance() -> getBuildingManager() -> getCollisionID();
            if (idBuildingIA != -1 && Human::Instance() -> getUnitManager() -> isTroopSelected()){
                Game::Instance() -> getMouse() -> changeIcon(CURSOR_IBEAM);

                if (Game::Instance() -> getMouse() -> rightMousePressed()) {
                    //ToDo
                }
                
                onMap = false;
            }

            i32 idTroopIA = IA::Instance() -> getUnitManager() -> getCollisionID();
            if (idTroopIA != -1 && Human::Instance() -> getUnitManager() -> isTroopSelected()){
                Game::Instance() -> getMouse() -> changeIcon(CURSOR_IBEAM);

                if (Game::Instance() -> getMouse() -> rightMousePressed()){
                    //ToDo
                }
                
                onMap = false;
            }
            
            //If nothing happens
            if (onMap){
                if (Human::Instance() -> getUnitManager() -> isTroopSelected()){
                    Game::Instance() -> getMouse() -> changeIcon(CURSOR_CROSSHAIR);
                } else if (Human::Instance() -> getUnitManager() -> isDeployingTroop()){
                    Game::Instance() -> getMouse() -> changeIcon(CURSOR_CROSSHAIR);
                    i32 idTroop = Human::Instance() -> getUnitManager() -> getDeployingTroopID();
                    if (idTroop > 0){
                        if (Game::Instance() -> getMouse() -> rightMousePressed()){
                            Human::Instance() -> getUnitManager() -> deploySelectedTroop(mapCollision);
                            Human::Instance() -> getUnitManager() -> selectTroop(idTroop);
                        }
                    } else if (idTroop == 0) {
                        if (Game::Instance() -> getMouse() -> rightMousePressed()){
                            Human::Instance() -> getUnitManager() -> deployAllTroops(mapCollision);
                        }
                    } else {
                        std::cout << "Ninguna tropa seleccionada" << std::endl;
                    }
                } else 
                    Game::Instance() -> getMouse() -> changeIcon(CURSOR_NORMAL);

                if (Game::Instance() -> getMouse() -> leftMousePressed())
                    Human::Instance() -> getUnitManager() -> unSelectTroop();
            }
            onMap = false;

            if (Game::Instance() -> getKeyboard() -> keyPressed(GLFW_KEY_ESCAPE)) {
                pauseMenu = new PauseMenu();
                Window::Instance() -> setGUI();
                pauseMenu -> setHUDEvents();
                gamePaused = true;
            }

            if (Game::Instance()-> getMouse() -> rightMousePressed()) {
                Human::Instance() -> getUnitManager() -> moveOrder();
            }
        } else {
            Game::Instance() -> getMouse() -> changeIcon(CURSOR_NORMAL);
        }  
    } else {
        pauseMenu -> update();
    }
}

void GameState::Update(){
    if (gamePaused == false) {
        Game *g = Game::Instance();

    //Win/Lose
    if (IA::Instance() -> getBuildingManager() -> getAmount(Enumeration::BuildingType::MainBuilding) == 0) {
        Game::Instance() -> changeState(Enumeration::State::WinState);
    }
    if (Human::Instance() -> getBuildingManager() -> getAmount(Enumeration::BuildingType::MainBuilding) == 0) {
        Game::Instance() -> changeState(Enumeration::State::DefeatState);
    }

    //Update camera
    camera -> Update(g -> getWindow() -> getDeltaTime());
    
    //Update HUD
    hud -> Update();

        //NEW SOUND SYSTEM
    /* SoundSystem::Instance() -> playMusicEvent("event:/Music/DroraniaMusic");*/
        SoundSystem::Instance() -> update();
        
        //If human is building something
        Human::Instance() -> getBuildingManager() -> drawBuilding();

        //Update human and IA status
        Human::Instance() -> Update();
        IA::Instance() -> Update();

        //ToDo: glfw tiene un evento para si se redimensiona la pantalla
        if (g -> getWindow() -> getRealWindowWidth() != prevWindowWidth || g -> getWindow() -> getRealWindowHeight() != prevWindowHeight) {
            hud -> updatePositions();
        }
    }
}

void GameState::Render() {

}

void GameState::CleanUp() {
    delete light;
    delete camera;
    delete map;
    delete hud;
    delete battleManager;
    delete pauseMenu;
    IA::Instance() -> CleanUp();
    Human::Instance() -> CleanUp();
    //ToDo: Clean Map
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

void GameState::cleanGamePaused() {
    gamePaused = false;
    delete pauseMenu;
}


/*  
    //Hacks
    if (Game::Instance() -> getIO() -> keyPressed(KEY_KEY_1)) {
        Human::Instance() -> receiveMetal();
    }

    if (Game::Instance() -> getIO() -> keyPressed(KEY_KEY_2)) {
        Human::Instance() -> receiveCrystal();
    }

    if (Game::Instance() -> getIO() -> keyPressed(KEY_KEY_3)) {
        Human::Instance() -> receiveCitizens();
    }
    Vector3<float> v = map -> getPointCollision(Game::Instance() -> getMouse());
    Human::Instance() -> getUnitManager() -> UpdateUnitManager();
*/