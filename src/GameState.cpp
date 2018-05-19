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
    //Clean Up
} 

void GameState::Init() {
    IO::Instance() -> getResourceManager()->loadResource("media/map/map.json");
 
    //Init players
    human -> Init("Drorania"); 
    ia -> Init("Kaonov");

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
        Vector3<f32> p = ia -> hallPosition;
        p.x = p.x + 200; //ToDo: hacer bien
        ia -> getUnitManager() -> deployAllTroops(Vector2<f32>(p.x, p.z));
    });

    //Human events
    IO::Instance() -> getEventManager() -> addEvent(Enumeration::EventType::RetractTroopsHuman, [&]() {
        human -> getUnitManager() -> retractAllTroops();
    });
    IO::Instance() -> getEventManager() -> addEvent(Enumeration::EventType::DeployTroopsHuman, [&]() {
        Vector3<f32> p = human -> hallPosition;
        p.x = p.x + 200; //ToDo: hacer bien
        human -> getUnitManager() -> deployAllTroops(Vector2<f32>(p.x, p.z));
    });

    //Hud events
    IO::Instance() -> getEventManager() -> addEvent(Enumeration::EventType::showBuiltText, [&](){
        hud->addToastToQueue("Se ha construido un edificio");
    });
    IO::Instance() -> getEventManager() -> addEvent(Enumeration::EventType::showRecruitedText, [&](){
        hud->addToastToQueue("Se ha reclutado una tropa");
    });

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
            //Interactions with our buildings
            i32 idBuilding = human -> getBuildingManager() -> getCollisionID();
            if (idBuilding != -1){
                if (!human -> getUnitManager() -> isTroopSelected())
                    IO::Instance() -> getMouse() -> changeIcon(CURSOR_HAND);
                
                if (IO::Instance() -> getMouse() -> leftMousePressed()) {
                    Building *b = human->getBuildingManager()->getBuilding(idBuilding);
                    if (b != nullptr){
                        if (human -> getBuildingManager() -> checkFinished(idBuilding)) {
							//ShowPopup
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
							//Retract
                            human -> getUnitManager() -> getSelectedTroop() -> switchState(Enumeration::UnitState::Retract);
                            sentToMainHall = true;
                        }
                    }
                }

                onMap = false;
            }

            //Interactions with IA's buildings
            i32 idBuildingIA =  ia -> getBuildingManager() -> getCollisionID();
            if (idBuildingIA != -1 && human -> getUnitManager() -> isTroopSelected()){
                IO::Instance() -> getMouse() -> changeIcon(CURSOR_IBEAM);

                if (IO::Instance() -> getMouse() -> rightMousePressed()) {
                    //ToDo: atacar
                }
                
                onMap = false;
            }
            
			//Interactions with Human Units
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

			//Interactions with IA Units
            i32 idTroopIA = ia -> getUnitManager() -> getCollisionID();
            if (idTroopIA != -1 && human -> getUnitManager() -> isTroopSelected()){
                IO::Instance() -> getMouse() -> changeIcon(CURSOR_IBEAM);

                if (IO::Instance() -> getMouse() -> rightMousePressed()){
                    //ToDo: atacar
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
							Vector3<f32> p = map->getMouseCollitionPoint();
                            human -> getUnitManager() -> deploySelectedTroop(Vector2<f32>(p.x, p.z));
                            human -> getUnitManager() -> selectTroop(idTroop);
                        }
                    } else if (idTroop == 0) {
                        if (IO::Instance() -> getMouse() -> rightMousePressed()){
							Vector3<f32> p = map->getMouseCollitionPoint();
                            human -> getUnitManager() -> deployAllTroops(Vector2<f32>(p.x, p.z));
                        }
                    } else {
                        //Ninguna tropa seleccionada
                    }
                } else 
                    IO::Instance() -> getMouse() -> changeIcon(CURSOR_NORMAL);

                if (IO::Instance() -> getMouse() -> leftMousePressed())
                    human -> getUnitManager() -> unSelectTroop();
            }
            onMap = false;

            if (IO::Instance() -> getKeyboard() -> keyPressed(GLFW_KEY_ESCAPE)) { //ToDo: fachada
                // Si el popup esta abierto, cierralo
                if (hud -> getPopUpOpen())
                    hud -> hidePopup();
                // Si no, pausa el juego
                else {
                    pauseMenu = new PauseMenu();
                    Window::Instance() -> setGUI();
                    pauseMenu -> setHUDEvents();
                    gamePaused = true;
                }
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

        //ToDo: NEW SOUND SYSTEM
        //SoundSystem::Instance() -> playMusicEvent("event:/Music/DroraniaMusic");
        SoundSystem::Instance() -> update();
        
        //If human is building something
        human -> getBuildingManager() -> drawBuilding();

        //Update human and IA status
        human -> Update();
        ia -> Update();

		//Resize trigger
        Window::Instance()->setResizeCallback([&](i32 newWidth, i32 newHeight){
			std::cout << "Resized to (" << newWidth << "," << newHeight << ")" << std::endl;
		});

        //Win/Lose
        if (ia -> getBuildingManager() -> getAmount("MainBuilding") == 0) {
            g -> changeState(Enumeration::State::WinState);
        }
        if (human -> getBuildingManager() -> getAmount("MainBuilding") == 0) {
            g -> changeState(Enumeration::State::DefeatState);
        }
    }
    //fps count goes after game logic to see how long it took to go through the logic
    Window::Instance() -> calculateFramerate();
}

void GameState::Render() {

}

void GameState::CleanUp() {
    delete pauseMenu;

    human -> CleanUp();
    ia -> CleanUp();
    map -> CleanUp();
    hud -> CleanUp();
}

void GameState::cleanGamePaused() {
    gamePaused = false;
    delete pauseMenu;
}