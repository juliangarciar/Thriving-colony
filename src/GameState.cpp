#include "GameState.h"
#include "Game.h"

GameState::GameState() : State() {
    map = Map::Instance();

    gamePaused = false;
}

GameState::~GameState() {
    //Clean Up
} 

void GameState::Init() {
    //Load map
    map -> Init();

    //Initialize the event system
    //IA Events
    IO::Instance() -> getEventManager() -> addEvent(Enumeration::EventType::RetractTroopsIA, [&]() {
        IA::Instance() -> getUnitManager() -> retractAllTroops();
    });
    IO::Instance() -> getEventManager() -> addEvent(Enumeration::EventType::DeployTroopsIA, [&]() {
        Vector3<f32> p = IA::Instance() -> hallPosition;
        p.x = p.x + 200; //ToDo: hacer bien
        IA::Instance() -> getUnitManager() -> deployAllTroops(Vector2<f32>(p.x, p.z));
    });

    //Human events
    IO::Instance() -> getEventManager() -> addEvent(Enumeration::EventType::RetractTroopsHuman, [&]() {
        Human::Instance() -> getUnitManager() -> retractAllTroops();
    });
    IO::Instance() -> getEventManager() -> addEvent(Enumeration::EventType::DeployTroopsHuman, [&]() {
        Vector3<f32> p = Human::Instance() -> hallPosition;
        p.x = p.x + 200; //ToDo: hacer bien
        Human::Instance() -> getUnitManager() -> deployAllTroops(Vector2<f32>(p.x, p.z));
    });

    //Hud events
    IO::Instance() -> getEventManager() -> addEvent(Enumeration::EventType::showBuiltText, [&]() {
        Hud::Instance() -> addToastToQueue("Se ha construido un edificio");
    });
    IO::Instance() -> getEventManager() -> addEvent(Enumeration::EventType::showRecruitedText, [&]() {
        Hud::Instance() -> addToastToQueue("Se ha reclutado una tropa");
    });

    //Init SoundSystem
    //SoundSystem::Instance() -> initSystem();
}

void GameState::Input() {
    if (gamePaused ==  false) {
        if (!Hud::Instance() -> getPopUpOpen()) {
            map -> Input();

            if (IO::Instance() -> getKeyboard() -> keyPressed(GLFW_KEY_ESCAPE)) { //ToDo: fachada
                // Si el popup esta abierto, cierralo (ToDo: no funca)
                if (Hud::Instance() -> getPopUpOpen())
                    Hud::Instance() -> hidePopup();
                // Si no, pausa el juego
                else {
                    IO::Instance() -> getMouse() -> changeCustomIcon(0);
                    pauseMenu = new PauseMenu();
                    Window::Instance() -> setGUI();
                    pauseMenu -> setHUDEvents();
                    gamePaused = true;
                }
            }
        } else {
            IO::Instance() -> getMouse() -> changeCustomIcon(0);
        }
    } else {
        pauseMenu -> update();
    }
}

void GameState::Update() {
    if (gamePaused == false) {
        //Update map
        map -> Update();

        //ToDo: NEW SOUND SYSTEM
        //SoundSystem::Instance() -> playMusicEvent("event:/Music/DroraniaMusic");
        //SoundSystem::Instance() -> update();

		//Resize trigger
        Window::Instance()->setResizeCallback([&](i32 newWidth, i32 newHeight) {
			std::cout << "Resized to (" << newWidth << "," << newHeight << ")" << std::endl;
		});
    }
    //fps count goes after game logic to see how long it took to go through the logic
    Window::Instance() -> calculateFramerate();
}

void GameState::Render() {

}

void GameState::CleanUp() {
    delete pauseMenu;

    Human::Instance() -> CleanUp();
    IA::Instance() -> CleanUp();
    map -> CleanUp();
    Hud::Instance() -> CleanUp();
}

void GameState::cleanGamePaused() {
    gamePaused = false;
    delete pauseMenu;
}
