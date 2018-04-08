#include "GameState.h"
#include "Game.h"

GameState::GameState() : State() {
    human = Human::Instance();
    ia = IA::Instance();
    map = Map::Instance();
    hud = Hud::Instance();

    gamePaused = false;
}

GameState::~GameState() {
} 

void GameState::Init() {
    IO::Instance() -> getResourceManager()->loadResource("media/map/map.json");
 
    //Init players
    human -> Init(); 
    ia -> Init();

    //Init HUD
    hud -> Init();

    //Load map
    map -> Init();

    //Initialize the event system
    //IA Events
    IO::Instance() -> getEventManager() -> addEvent(Enumeration::EventType::RetractTroopsIA, [&]() {
        ia -> getUnitManager() -> retractAllTroops();
    });
    IO::Instance() -> getEventManager() -> addEvent(Enumeration::EventType::DeployTroopsIA, [&]() {
        Vector3<f32> p = ia -> getHallPosition();
        p.x = p.x + 200; //ToDo: hacer bien
        ia -> getUnitManager() -> deployAllTroops(p);
    });

    //Human events
    IO::Instance() -> getEventManager() -> addEvent(Enumeration::EventType::RetractTroopsHuman, [&]() {
        human -> getUnitManager() -> retractAllTroops();
    });
    IO::Instance() -> getEventManager() -> addEvent(Enumeration::EventType::DeployTroopsHuman, [&]() {
        Vector3<f32> p = human -> getHallPosition();
        p.x = p.x + 200; //ToDo: hacer bien
        human -> getUnitManager() -> deployAllTroops(p);
    });

    //Hud events
    IO::Instance() -> getEventManager() -> addEvent(Enumeration::EventType::showBuiltText, [&](){
        hud->showToast("Se ha construido un edificio");
    });
    IO::Instance() -> getEventManager() -> addEvent(Enumeration::EventType::showRecruitedText, [&](){
        hud->showToast("Se ha reclutado una tropa");
    });

    //Init battle manager
    battleManager = new BattleManager();

    //Init SoundSystem
    SoundSystem::Instance() -> initSystem();
}

void GameState::Input() {
    if(gamePaused ==  false){
        if (!hud->getPopUpOpen()){
            map -> Input();

            human -> getBuildingManager() -> testRaycastCollisions();
            human -> getUnitManager() -> testRaycastCollisions();

            ia -> getBuildingManager() -> testRaycastCollisions();
            ia -> getUnitManager() -> testRaycastCollisions();

            i32 onMap = true;
            bool sentToMainHall = false;
            //Interactions with our entities
            i32 idBuilding = human -> getBuildingManager() -> getCollisionID();
            if (idBuilding != -1){
                if (!human -> getUnitManager() -> isTroopSelected())
                    IO::Instance() -> getMouse() -> changeIcon(CURSOR_HAND);
                
                if (IO::Instance() -> getMouse() -> leftMousePressed()) {
                    Building *b = human->getBuildingManager()->getBuilding(idBuilding);
                    if (b != nullptr){
                        if (human -> getBuildingManager() -> checkFinished(idBuilding)) {
                            hud -> showPopup(b->getType());
                        }
                    }
                }
                // Right clicked
                if (IO::Instance() -> getMouse() -> rightMousePressed()) {
                    // Have a troop
                    if (human -> getUnitManager() -> isTroopSelected()) {
                        // Main hall
                        if (idBuilding == 0) {
                            human -> getUnitManager() -> getSelectedTroop() -> switchState(Enumeration::UnitState::Retract);
                            sentToMainHall = true;
                        }
                    }
                }

                onMap = false;
            }
            
            i32 idTroop = human -> getUnitManager() -> getCollisionID();
            if (idTroop != -1){
                if (!human -> getUnitManager() -> isTroopSelected())
                    IO::Instance() -> getMouse() -> changeIcon(CURSOR_HAND);
                
                if (IO::Instance() -> getMouse() -> leftMousePressed()){
                    IO::Instance() -> getMouse() -> changeIcon(CURSOR_CROSSHAIR);
                    human -> getUnitManager() -> selectTroop(idTroop);
                }
                
                onMap = false;
            }

            //Interactions with IA's entities
            i32 idBuildingIA =  ia -> getBuildingManager() -> getCollisionID();
            if (idBuildingIA != -1 && human -> getUnitManager() -> isTroopSelected()){
                IO::Instance() -> getMouse() -> changeIcon(CURSOR_IBEAM);

                if (IO::Instance() -> getMouse() -> rightMousePressed()) {
                    //ToDo
                }
                
                onMap = false;
            }

            i32 idTroopIA = ia -> getUnitManager() -> getCollisionID();
            if (idTroopIA != -1 && human -> getUnitManager() -> isTroopSelected()){
                IO::Instance() -> getMouse() -> changeIcon(CURSOR_IBEAM);

                if (IO::Instance() -> getMouse() -> rightMousePressed()){
                    //ToDo
                }
                
                onMap = false;
            }
            
            //If nothing happens
            if (onMap){
                if (human -> getUnitManager() -> isTroopSelected()){
                    IO::Instance() -> getMouse() -> changeIcon(CURSOR_CROSSHAIR);
                } else if (human -> getUnitManager() -> isDeployingTroop()){
                    IO::Instance() -> getMouse() -> changeIcon(CURSOR_CROSSHAIR);
                    i32 idTroop = human -> getUnitManager() -> getDeployingTroopID();
                    if (idTroop > 0){
                        if (IO::Instance() -> getMouse() -> rightMousePressed()){
                            human -> getUnitManager() -> deploySelectedTroop(map->getMouseCollitionPoint());
                            human -> getUnitManager() -> selectTroop(idTroop);
                        }
                    } else if (idTroop == 0) {
                        if (IO::Instance() -> getMouse() -> rightMousePressed()){
                            human -> getUnitManager() -> deployAllTroops(map->getMouseCollitionPoint());
                        }
                    } else {
                        std::cout << "Ninguna tropa seleccionada" << std::endl;
                    }
                } else 
                    IO::Instance() -> getMouse() -> changeIcon(CURSOR_NORMAL);

                if (IO::Instance() -> getMouse() -> leftMousePressed())
                    human -> getUnitManager() -> unSelectTroop();
            }
            onMap = false;

            if (IO::Instance() -> getKeyboard() -> keyPressed(GLFW_KEY_ESCAPE)) {
                pauseMenu = new PauseMenu();
                Window::Instance() -> setGUI();
                pauseMenu -> setHUDEvents();
                gamePaused = true;
            }

            if (IO::Instance()-> getMouse() -> rightMousePressed()) {
                human -> getUnitManager() -> moveOrder();
            }
        } else {
            IO::Instance() -> getMouse() -> changeIcon(CURSOR_NORMAL);
        }  
    } else {
        pauseMenu -> update();
    }
}

void GameState::Update(){
    if (gamePaused == false) {
        Game *g = Game::Instance();

        //Update map
        map -> Update();
        
        //Update HUD
        hud -> Update();

        //NEW SOUND SYSTEM
        SoundSystem::Instance() -> playMusicEvent("event:/Music/DroraniaMusic");
        SoundSystem::Instance() -> update();
        
        //If human is building something
        human -> getBuildingManager() -> drawBuilding();

        //Update human and IA status
        human -> Update();
        ia -> Update();

        //ToDo: glfw tiene un evento para si se redimensiona la pantalla
        /*if (g -> getWindow() -> getRealWindowWidth() != prevWindowWidth || g -> getWindow() -> getRealWindowHeight() != prevWindowHeight) {
            hud -> updatePositions();
        }*/

        //Win/Lose
        if (ia -> getBuildingManager() -> getAmount(Enumeration::BuildingType::MainBuilding) == 0) {
            g -> changeState(Enumeration::State::WinState);
        }
        if (human -> getBuildingManager() -> getAmount(Enumeration::BuildingType::MainBuilding) == 0) {
            g -> changeState(Enumeration::State::DefeatState);
        }
    }
}

void GameState::Render() {

}

void GameState::CleanUp() {
    delete battleManager;
    delete pauseMenu;

    human -> CleanUp();
    ia -> CleanUp();
    map -> CleanUp();
    hud -> CleanUp();
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
    if (g -> getIO() -> keyPressed(KEY_KEY_1)) {
        human -> receiveMetal();
    }

    if (g -> getIO() -> keyPressed(KEY_KEY_2)) {
        human -> receiveCrystal();
    }

    if (g -> getIO() -> keyPressed(KEY_KEY_3)) {
        human -> receiveCitizens();
    }
    Vector3<float> v = map -> getPointCollision(g -> getMouse());
    human -> getUnitManager() -> UpdateUnitManager();
*/